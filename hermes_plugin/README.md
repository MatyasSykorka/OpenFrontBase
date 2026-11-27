# OpenFrontBase Hermes Agent Plugin

Tento plugin integruje **Hermes Agent** (od [Nous Research](https://hermes-agent.nousresearch.com)) s hardwarovým panelem **OpenFrontBase**.

## Co plugin dělá
Automaticky odchytává životní cyklus agenta a v reálném čase exportuje stav na obrazovku **Agent status**:
1. **LLM name:** Název aktivního modelu (např. `Hermes-3-Llama-3.1-8B`)
2. **Status:** Aktuální stav (`Thinking...`, `Calling tool`, `Processing output`, `Idle`)
3. **Tool calling:** Název právě volaného nástroje (`terminal_exec`, `web_search`, atd.)
4. **Tokens per second:** Rychlost generování (tok/s)
5. **Memory usage:** Reálné využití RAM procesem agenta
6. **Context window:** Velikost kontextu konverzace v tokenech

## Instalace do Hermes Agenta

### Linux
Zkopírujte složku `hermes_plugin` do složky pluginů Hermese:
```bash
mkdir -p ~/.hermes/plugins/openfront
cp hermes_plugin/plugin.yaml ~/.hermes/plugins/openfront/
cp hermes_plugin/__init__.py ~/.hermes/plugins/openfront/
```

### Windows
Zkopírujte soubory do uživatelského profilu:
```powershell
New-Item -ItemType Directory -Force -Path "$HOME\.hermes\plugins\openfront"
Copy-Item hermes_plugin\plugin.yaml "$HOME\.hermes\plugins\openfront\"
Copy-Item hermes_plugin\__init__.py "$HOME\.hermes\plugins\openfront\"
```

Plugin se aktivuje při spuštění příkazu `hermes plugins enable openfront`.
