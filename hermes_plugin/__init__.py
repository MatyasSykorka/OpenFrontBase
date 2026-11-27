"""
OpenFrontBase Telemetry Plugin for Hermes Agent (Nous Research)
Exposes real-time agent lifecycle state, tool calls, token generation speed,
memory usage (including local LLM process/VRAM memory), and context window (used / max).
"""

from __future__ import annotations

import json
import logging
import os
import sys
import tempfile
import threading
import time
import urllib.request
from typing import Any, Dict, Optional, Tuple

logger = logging.getLogger("hermes.plugins.openfront")

try:
    import psutil
except ImportError:
    psutil = None

STATUS_FILES = [
    os.path.join(tempfile.gettempdir(), "hermes_status.json"),
    os.path.expanduser("~/.hermes/status.json"),
    "/tmp/hermes_status.json"
]
HTTP_ENDPOINT = "http://127.0.0.1:28888/"

_lock = threading.Lock()
_state: dict[str, Any] = {
    "active": True,
    "name": "Hermes Agent",
    "status": "Idle",
    "tool": "-",
    "tok_s": 0.0,
    "mem_mb": 0,
    "ctx": "-"
}

_stream_start_time: float = 0.0
_stream_tokens_count: int = 0
_last_stream_emit: float = 0.0
_bg_thread_started: bool = False

_cached_max_context: int = 256000
_cached_used_tokens: int = 0
_discovered_llm_mem_mb: int = 0


def _format_context_window(used_tokens: int, max_tokens: int) -> str:
    """Formátuje zobrazení kontextového okna vždy jako: využitý / maximální."""
    def _fmt(v: int) -> str:
        if v >= 1_000_000:
            val = v / 1_000_000
            return f"{val:.1f}M" if val % 1 != 0 else f"{int(val)}M"
        if v >= 1_000:
            val = v / 1_000
            return f"{val:.1f}K" if val % 1 != 0 else f"{int(val)}K"
        return str(v)

    if max_tokens > 0:
        used_str = _fmt(used_tokens) if used_tokens > 0 else "0"
        return f"{used_str} / {_fmt(max_tokens)}"
    elif used_tokens > 0:
        return f"{_fmt(used_tokens)} tok"
    return "-"


def _detect_local_llm(preferred_model: Optional[str] = None) -> Tuple[int, Optional[str], Optional[int]]:
    """
    Zjišťuje využití paměti a parametry lokálního LLM (Ollama API a procesy llama-server/ollama).
    Vrací: (memory_mb, model_name, max_context_length).
    """
    global _discovered_llm_mem_mb, _cached_max_context
    ollama_mem_mb = 0
    model_name: Optional[str] = None
    ctx_len: Optional[int] = None

    # 1. Kontrola aktivních modelů v paměti Ollama (/api/ps)
    for endpoint in ["http://127.0.0.1:11434/api/ps", "http://localhost:11434/api/ps"]:
        try:
            req = urllib.request.Request(endpoint, headers={"User-Agent": "OpenFront/1.0"})
            with urllib.request.urlopen(req, timeout=0.3) as resp:
                data = json.loads(resp.read().decode("utf-8"))
                models = data.get("models", [])
                if models:
                    m = models[0]
                    model_name = m.get("name")
                    ctx_len = m.get("context_length")
                    size_bytes = m.get("size", 0)
                    if size_bytes > 0:
                        ollama_mem_mb = int(size_bytes / (1024 * 1024))
                    break
        except Exception:
            pass

    # 2. Inspekce paměti procesů lokálního runneru (llama-server, ollama, vLLM)
    proc_mem_bytes = 0
    if psutil is not None:
        try:
            keywords = ("llama-server", "ollama", "vllm", "llama.cpp")
            for p in psutil.process_iter(["name", "cmdline", "memory_info"]):
                try:
                    pname = (p.info.get("name") or "").lower()
                    cmd = " ".join(p.info.get("cmdline") or []).lower()
                    if any(k in pname or k in cmd for k in keywords):
                        if "python" in pname and "ollama" not in cmd:
                            continue
                        mem_info = p.info.get("memory_info")
                        if mem_info:
                            proc_mem_bytes += mem_info.rss
                except (psutil.NoSuchProcess, psutil.AccessDenied):
                    pass
        except Exception:
            pass

    proc_mem_mb = int(proc_mem_bytes / (1024 * 1024))

    # 3. Zjištění velikosti a kontextu z Ollama (/api/tags)
    model_size_mb = 0
    target_model = preferred_model or model_name
    if target_model and target_model != "Hermes Agent" and target_model != "-":
        for endpoint in ["http://127.0.0.1:11434/api/tags", "http://localhost:11434/api/tags"]:
            try:
                req = urllib.request.Request(endpoint, headers={"User-Agent": "OpenFront/1.0"})
                with urllib.request.urlopen(req, timeout=0.3) as resp:
                    data = json.loads(resp.read().decode("utf-8"))
                    base_prefix = target_model.split(":")[0]
                    for m in data.get("models", []):
                        m_name = m.get("name", "")
                        if m_name == target_model or m_name.startswith(base_prefix):
                            size_b = m.get("size", 0)
                            if size_b > 0:
                                model_size_mb = int(size_b / (1024 * 1024))
                                if not ctx_len:
                                    ctx_len = m.get("details", {}).get("context_length")
                            break
                if model_size_mb > 0:
                    break
            except Exception:
                pass

    total_llm_mem = max(ollama_mem_mb, proc_mem_mb, model_size_mb)

    # Ukládáme nalezenou paměť do trvalé mezipaměti, aby nikdy nespadla na 0
    if total_llm_mem > 0:
        _discovered_llm_mem_mb = total_llm_mem
    elif _discovered_llm_mem_mb > 0:
        total_llm_mem = _discovered_llm_mem_mb

    if ctx_len and ctx_len > 0:
        _cached_max_context = ctx_len

    return total_llm_mem, model_name, ctx_len


def _get_agent_process_memory_mb() -> int:
    """Vrací RSS paměť samotného procesu agenta v MB."""
    if psutil is not None:
        try:
            return int(psutil.Process().memory_info().rss / (1024 * 1024))
        except Exception:
            pass
    if sys.platform.startswith("linux"):
        try:
            with open("/proc/self/statm", "r") as f:
                pages = int(f.read().split()[1])
                return int((pages * os.sysconf("SC_PAGE_SIZE")) / (1024 * 1024))
        except Exception:
            pass
    return 0


def _emit_state() -> None:
    """Odešle aktuální stav do sdílených souborů i přes HTTP API."""
    global _discovered_llm_mem_mb, _cached_max_context, _cached_used_tokens

    with _lock:
        current_name = _state.get("name")
        current_mem = _state.get("mem_mb", 0)

    agent_mem = _get_agent_process_memory_mb()
    llm_mem = _discovered_llm_mem_mb

    with _lock:
        # Celková paměť = Python CLI agent (~270 MB) + model LLM (~7600 MB)
        total_mem = agent_mem + llm_mem
        if total_mem > 0:
            # Ochrana: nikdy nesnížíme paměť z > 1024 MB zpět na ~270 MB
            if total_mem >= current_mem or current_mem < 1024:
                _state["mem_mb"] = total_mem

        # Aktualizace zobrazení kontextového okna (využitý / maximální)
        _state["ctx"] = _format_context_window(_cached_used_tokens, _cached_max_context)

        payload = dict(_state)

    raw_json = json.dumps(payload)

    # 1. Zápis do sdílených souborů
    for sfile in STATUS_FILES:
        try:
            parent = os.path.dirname(sfile)
            if parent:
                os.makedirs(parent, exist_ok=True)
            tmp_path = sfile + ".tmp"
            with open(tmp_path, "w", encoding="utf-8") as f:
                f.write(raw_json)
            os.replace(tmp_path, sfile)
        except Exception:
            pass

    # 2. HTTP POST do C# OpenFrontBase.Agent
    try:
        req = urllib.request.Request(
            HTTP_ENDPOINT,
            data=raw_json.encode("utf-8"),
            headers={"Content-Type": "application/json"},
            method="POST"
        )
        with urllib.request.urlopen(req, timeout=0.08) as resp:
            pass
    except Exception:
        pass


def _bg_loop() -> None:
    """Periodický daemon na pozadí zjišťující stav modelu a paměti bez blokování tokenů."""
    while True:
        try:
            with _lock:
                cname = _state.get("name")
            _detect_local_llm(preferred_model=cname)
            _emit_state()
            time.sleep(1.5)
        except Exception:
            time.sleep(2.0)


# --- Hook callbacks pro Hermes Agent ---

def _on_session_start(*args: Any, **kwargs: Any) -> None:
    with _lock:
        model = kwargs.get("model")
        if model:
            _state["name"] = str(model).split("/")[-1].removesuffix(".gguf")
        _state["status"] = "Session started"
    _emit_state()


def _on_pre_llm_call(*args: Any, **kwargs: Any) -> None:
    global _stream_start_time, _stream_tokens_count, _cached_used_tokens
    _stream_start_time = time.time()
    _stream_tokens_count = 0

    with _lock:
        model = kwargs.get("model")
        if model:
            _state["name"] = str(model).split("/")[-1].removesuffix(".gguf")
        _state["status"] = "Thinking"

        # Přibližný výpočet vstupních tokenů před spuštěním inference
        history = kwargs.get("conversation_history")
        user_msg = kwargs.get("user_message")
        total_chars = 0
        if isinstance(history, list):
            for m in history:
                if isinstance(m, dict):
                    total_chars += len(str(m.get("content", "")))
        if user_msg:
            total_chars += len(str(user_msg))
        if total_chars > 0:
            _cached_used_tokens = int(total_chars / 3.8)

    _emit_state()


def _on_pre_api_request(*args: Any, **kwargs: Any) -> None:
    global _cached_used_tokens
    tok = kwargs.get("approx_input_tokens")
    if tok and isinstance(tok, (int, float)) and tok > 0:
        _cached_used_tokens = int(tok)
    model = kwargs.get("model")
    if model:
        with _lock:
            _state["name"] = str(model).split("/")[-1].removesuffix(".gguf")
    _emit_state()


def _on_post_api_request(*args: Any, **kwargs: Any) -> None:
    global _cached_used_tokens, _cached_max_context
    usage = kwargs.get("usage")
    if isinstance(usage, dict):
        tot = usage.get("total_tokens") or usage.get("prompt_tokens")
        if tot and isinstance(tot, (int, float)) and tot > 0:
            _cached_used_tokens = int(tot)

    ctx_l = kwargs.get("context_length")
    if ctx_l and isinstance(ctx_l, (int, float)) and ctx_l > 0:
        _cached_max_context = int(ctx_l)

    _emit_state()


def _on_stream_start(*args: Any, **kwargs: Any) -> None:
    global _stream_start_time, _stream_tokens_count
    _stream_start_time = time.time()
    _stream_tokens_count = 0
    with _lock:
        model = kwargs.get("model")
        if model:
            _state["name"] = str(model).split("/")[-1].removesuffix(".gguf")
        _state["status"] = "Generating"
    _emit_state()


def _on_stream_delta(*args: Any, **kwargs: Any) -> None:
    global _stream_tokens_count, _last_stream_emit
    _stream_tokens_count += 1
    now = time.time()

    if now - _last_stream_emit >= 0.25:
        _last_stream_emit = now
        elapsed = now - _stream_start_time
        if elapsed > 0.1:
            tok_s = round(_stream_tokens_count / elapsed, 1)
            with _lock:
                _state["status"] = "Generating"
                if tok_s > 0.05:
                    _state["tok_s"] = tok_s
            _emit_state()


def _on_stream_end(*args: Any, **kwargs: Any) -> None:
    global _stream_tokens_count
    now = time.time()
    elapsed = now - _stream_start_time
    with _lock:
        if elapsed > 0.1 and _stream_tokens_count > 0:
            tok_s = round(_stream_tokens_count / elapsed, 1)
            if tok_s > 0.05:
                _state["tok_s"] = tok_s
        _state["status"] = "Idle"
    _emit_state()


def _on_post_llm_call(*args: Any, **kwargs: Any) -> None:
    with _lock:
        model = kwargs.get("model")
        if model:
            _state["name"] = str(model).split("/")[-1].removesuffix(".gguf")
        _state["status"] = "Idle"
    _emit_state()


def _on_pre_tool_call(tool_name: str = "", args: Optional[dict[str, Any]] = None, **kwargs: Any) -> None:
    tname = tool_name or kwargs.get("tool_name") or ""
    with _lock:
        _state["status"] = "Calling tool"
        if tname and tname != "-":
            _state["tool"] = str(tname)
    _emit_state()


def _on_post_tool_call(tool_name: str = "", **kwargs: Any) -> None:
    tname = tool_name or kwargs.get("tool_name") or ""
    with _lock:
        _state["status"] = "Tool executed"
        if tname and tname != "-":
            _state["tool"] = str(tname)
    _emit_state()


def _on_session_end(*args: Any, **kwargs: Any) -> None:
    with _lock:
        _state["status"] = "Idle"
    _emit_state()


def register(ctx: Any) -> None:
    """Registrační vstupní bod pluginu volaný systémem Hermes Agent."""
    global _bg_thread_started

    ctx.register_hook("on_session_start", _on_session_start)
    ctx.register_hook("pre_llm_call", _on_pre_llm_call)
    ctx.register_hook("post_llm_call", _on_post_llm_call)
    ctx.register_hook("pre_api_request", _on_pre_api_request)
    ctx.register_hook("post_api_request", _on_post_api_request)
    ctx.register_hook("pre_tool_call", _on_pre_tool_call)
    ctx.register_hook("post_tool_call", _on_post_tool_call)
    ctx.register_hook("on_stream_start", _on_stream_start)
    ctx.register_hook("on_stream_delta", _on_stream_delta)
    ctx.register_hook("on_stream_end", _on_stream_end)
    ctx.register_hook("on_session_end", _on_session_end)

    # Počáteční zjištění lokálního modelu a jeho paměti
    _detect_local_llm()

    if not _bg_thread_started:
        _bg_thread_started = True
        t = threading.Thread(target=_bg_loop, daemon=True, name="OpenFront-Telemetry")
        t.start()

    _emit_state()
    logger.info("OpenFrontBase Telemetry Plugin successfully registered.")
