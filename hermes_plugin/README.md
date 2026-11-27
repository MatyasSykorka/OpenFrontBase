# OpenFrontBase Hermes Agent Plugin

[English](#english) | [Čeština](#čeština)

---

<a name="english"></a>
## English

This plugin integrates **Hermes Agent** (by [Nous Research](https://hermes-agent.nousresearch.com)) with the **OpenFrontBase** dual 5.25" PC telemetry hardware panel.

### Overview & Capabilities
The plugin captures real-time agent lifecycle events and metrics and streams them to the **Agent status** display:
1. **LLM name:** Name of the currently active model (e.g., `spark-x2.5-4b-q8_0:latest`, `Hermes-3-Llama-3.1-8B`).
2. **Status:** Real-time state (`Session started`, `Thinking`, `Generating`, `Calling tool`, `Tool executed`, `Idle`).
3. **Tool calling:** Name of the tool currently being executed (e.g., `run_command`, `web_search`). Retains the last executed tool when idle.
4. **Tokens per second:** Real-time token generation speed (`tok/s`), preserved after generation completes.
5. **Memory usage:** Combined memory footprint of the agent process + local LLM runner (Ollama / llama-server / vLLM), formatted automatically in MB or GB (e.g., `7.85 GB`).
6. **Context window:** Displayed in `used / max` format (e.g., `10.3K / 256K`).

### How It Works
* **Zero Overhead / Non-blocking:** Streaming tokens and status events are dispatched without blocking the token generation path.
* **Dual-channel Telemetry Delivery:**
  * **HTTP POST:** Real-time low-latency push to `http://127.0.0.1:28888/` (hosted by `OpenFrontBase.Agent`).
  * **Shared File Fallback:** Synchronous atomic JSON write to `~/.hermes/status.json` and `%TEMP%/hermes_status.json`.
* **State Preservation (No Flashing / Blanking):** Previous valid values are latched so idle transitions or unload events never overwrite valid telemetry with empty strings or zeros.

### Installation

#### Linux
Copy the plugin files into the user's Hermes plugins directory:
```bash
mkdir -p ~/.hermes/plugins/openfront
cp hermes_plugin/* ~/.hermes/plugins/openfront/
```

#### Windows
Copy the plugin files into `%USERPROFILE%\.hermes\plugins\openfront`:
```powershell
New-Item -ItemType Directory -Force -Path "$HOME\.hermes\plugins\openfront"
Copy-Item hermes_plugin\* "$HOME\.hermes\plugins\openfront\"
```

### Enabling & Verification
1. Verify the plugin with the Hermes plugin doctor:
   ```bash
   hermes plugins doctor openfront
   ```
2. Enable the plugin if not automatically enabled:
   ```bash
   hermes plugins enable openfront
   ```
3. Start or restart Hermes:
   ```bash
   hermes
   ```

---

<a name="čeština"></a>
## Čeština

Tento plugin integruje **Hermes Agent** (od [Nous Research](https://hermes-agent.nousresearch.com)) s hardwarovým telemetrickým panelem **OpenFrontBase** do dvou 5,25" pozic PC skříně.

### Přehled a funkce
Plugin zachytává v reálném čase události životního cyklu agenta a předává je na obrazovku **Agent status**:
1. **LLM name:** Název aktivního modelu (např. `spark-x2.5-4b-q8_0:latest`, `Hermes-3-Llama-3.1-8B`).
2. **Status:** Aktuální stav (`Session started`, `Thinking`, `Generating`, `Calling tool`, `Tool executed`, `Idle`).
3. **Tool calling:** Název právě volaného nástroje (`run_command`, `web_search` atd.). Poslední volaný nástroj zůstává zobrazen i po dokončení.
4. **Tokens per second:** Rychlost generování tokenů (`tok/s`), uchovaná i po dokončení odpovědi.
5. **Memory usage:** Sloučená paměťová stopa procesu agenta + lokálního LLM (Ollama / llama-server / vLLM), automaticky formátovaná v MB nebo GB (např. `7.85 GB`).
6. **Context window:** Zobrazení ve formátu `využitý / maximální` (např. `10.3K / 256K`).

### Princip fungování
* **Nenulový dopad na výkon:** Token stream hooky běží asynchronně mimo hlavní vlákno inference.
* **Dvoukanálový přenos dat:**
  * **HTTP POST:** Okamžité odesílání na `http://127.0.0.1:28888/` (obsluhováno C# aplikací `OpenFrontBase.Agent`).
  * **Sdílený soubor:** Atomický zápis JSON do `~/.hermes/status.json` a `%TEMP%/hermes_status.json`.
* **Ochrana proti probliknutí:** Poslední známé platné hodnoty jsou uzamčeny a nejsou přemazávány prázdnými řetězci nebo nulami při přechodu do klidového stavu.

### Instalace

#### Linux
Zkopírujte soubory pluginu do adresáře pluginů Hermese:
```bash
mkdir -p ~/.hermes/plugins/openfront
cp hermes_plugin/* ~/.hermes/plugins/openfront/
```

#### Windows
Zkopírujte soubory do uživatelského profilu:
```powershell
New-Item -ItemType Directory -Force -Path "$HOME\.hermes\plugins\openfront"
Copy-Item hermes_plugin\* "$HOME\.hermes\plugins\openfront\"
```

### Aktivace a kontrola
1. Ověření funkčnosti pomocí nástroje Hermes doctor:
   ```bash
   hermes plugins doctor openfront
   ```
2. Povolení pluginu:
   ```bash
   hermes plugins enable openfront
   ```
3. Spuštění nebo restart Hermese:
   ```bash
   hermes
   ```
