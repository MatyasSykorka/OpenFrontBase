"""
OpenFrontBase Telemetry Plugin for Hermes Agent (Nous Research)
Exposes real-time agent lifecycle state, tool calls, token generation speed,
memory usage, and context window size to OpenFrontBase hardware display.
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
from pathlib import Path
from typing import Any, Dict, Optional

logger = logging.getLogger("hermes.plugins.openfront")

try:
    import psutil
except ImportError:
    psutil = None

# Cesty pro předávání stavu C# aplikaci
STATUS_FILES = [
    os.path.join(tempfile.gettempdir(), "hermes_status.json"),
    os.path.expanduser("~/.hermes/status.json")
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


def _get_process_memory_mb() -> int:
    """Vrací RSS paměť procesu v MB."""
    if psutil is not None:
        try:
            return int(psutil.Process().memory_info().rss / (1024 * 1024))
        except Exception:
            pass
    # Fallback pro Linux bez psutil
    if sys.platform.startswith("linux"):
        try:
            with open("/proc/self/statm", "r") as f:
                pages = int(f.read().split()[1])
                return int((pages * os.sysconf("SC_PAGE_SIZE")) / (1024 * 1024))
        except Exception:
            pass
    return 0


def _emit_state() -> None:
    """Odešle aktuální stav do souborů i přes lokální HTTP API."""
    with _lock:
        _state["mem_mb"] = _get_process_memory_mb()
        payload = dict(_state)

    raw_json = json.dumps(payload)

    # 1. Zápis do sdílených souborů
    for sfile in STATUS_FILES:
        try:
            os.makedirs(os.path.dirname(sfile), exist_ok=True)
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
    """Periodický daemon na pozadí udržující paměť a heartbeat."""
    while True:
        try:
            time.sleep(1.0)
            _emit_state()
        except Exception:
            time.sleep(2.0)


def _format_context(approx_tokens: int, max_tokens: int = 0) -> str:
    """Formátuje zobrazení kontextu (např. 10.3K / 256K)."""
    def _fmt(val: int) -> str:
        if val >= 1_000_000:
            return f"{val / 1_000_000:.1f}M"
        if val >= 1_000:
            return f"{val / 1_000:.1f}K"
        return str(val)

    if approx_tokens <= 0:
        return "-"
    if max_tokens > 0:
        return f"{_fmt(approx_tokens)} / {_fmt(max_tokens)}"
    return f"{_fmt(approx_tokens)} tok"


# --- Hook callbacks pro Hermes Agent ---

def _on_session_start(*args: Any, **kwargs: Any) -> None:
    with _lock:
        model = kwargs.get("model")
        if model:
            _state["name"] = str(model).split("/")[-1].removesuffix(".gguf")
        _state["status"] = "Session started"
        _state["tool"] = "-"
    _emit_state()


def _on_pre_llm_call(*args: Any, **kwargs: Any) -> None:
    global _stream_start_time, _stream_tokens_count
    _stream_start_time = time.time()
    _stream_tokens_count = 0

    with _lock:
        model = kwargs.get("model")
        if model:
            _state["name"] = str(model).split("/")[-1].removesuffix(".gguf")
        _state["status"] = "Thinking"
        _state["tool"] = "-"

        # Odhad velikosti kontextu z historie zpráv
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
            approx_tok = int(total_chars / 3.8)
            _state["ctx"] = _format_context(approx_tok)

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

    # Omezíme frekvenci odesílání přes síť na max každých 250 ms
    if now - _last_stream_emit >= 0.25:
        _last_stream_emit = now
        elapsed = now - _stream_start_time
        if elapsed > 0.1:
            tok_s = round(_stream_tokens_count / elapsed, 1)
            with _lock:
                _state["status"] = "Generating"
                _state["tok_s"] = tok_s
            _emit_state()


def _on_stream_end(*args: Any, **kwargs: Any) -> None:
    global _stream_tokens_count
    now = time.time()
    elapsed = now - _stream_start_time
    with _lock:
        if elapsed > 0.1 and _stream_tokens_count > 0:
            _state["tok_s"] = round(_stream_tokens_count / elapsed, 1)
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
    tname = tool_name or kwargs.get("tool_name") or "-"
    with _lock:
        _state["status"] = "Calling tool"
        _state["tool"] = str(tname)
    _emit_state()


def _on_post_tool_call(tool_name: str = "", **kwargs: Any) -> None:
    tname = tool_name or kwargs.get("tool_name") or "-"
    with _lock:
        _state["status"] = "Tool executed"
        _state["tool"] = str(tname)
    _emit_state()


def _on_session_end(*args: Any, **kwargs: Any) -> None:
    with _lock:
        _state["status"] = "Idle"
        _state["tool"] = "-"
    _emit_state()


def register(ctx: Any) -> None:
    """Registrační vstupní bod pluginu volaný systémem Hermes Agent."""
    global _bg_thread_started

    # Registrace jednotlivých lifecycle hooků bez dekorátoru
    ctx.register_hook("on_session_start", _on_session_start)
    ctx.register_hook("pre_llm_call", _on_pre_llm_call)
    ctx.register_hook("post_llm_call", _on_post_llm_call)
    ctx.register_hook("pre_tool_call", _on_pre_tool_call)
    ctx.register_hook("post_tool_call", _on_post_tool_call)
    ctx.register_hook("on_stream_start", _on_stream_start)
    ctx.register_hook("on_stream_delta", _on_stream_delta)
    ctx.register_hook("on_stream_end", _on_stream_end)
    ctx.register_hook("on_session_end", _on_session_end)

    # Spuštění daemon vlákna na pozadí pro periodický heartbeat a paměť
    if not _bg_thread_started:
        _bg_thread_started = True
        t = threading.Thread(target=_bg_loop, daemon=True, name="OpenFront-Telemetry")
        t.start()

    # Okamžité počáteční odeslání stavu
    _emit_state()
    logger.info("OpenFrontBase Telemetry Plugin successfully registered.")
