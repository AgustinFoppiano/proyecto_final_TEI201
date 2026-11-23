# Firmware 4.1 revisiones — historial persistente

Esta carpeta respalda la revisión entregada por el equipo como **`prototipo_4_1_revisiones(1).ino`**. A diferencia del archivo base `alarma_final.ino`, incorpora una función de historial local de activaciones y detenciones.

## Archivos

- [`cambios_historial.json`](cambios_historial.json): diferencias exactas respecto de [`alarma_final.ino`](../alarma_final/alarma_final.ino), verificadas al comparar los dos archivos.
- [`generar_ino.py`](generar_ino.py): aplica las diferencias al código base y **verifica el SHA-256** del resultado antes de escribir el archivo completo.

El archivo de código completo es demasiado grande para la operación de subida de esta integración; se guarda la diferencia reproducible, de manera que **no se modifica el archivo base**. El código fuente Arduino original del equipo se conserva íntegramente al reconstruirlo, sin generar ni simular partes nuevas.

## Generar el archivo listo para Arduino IDE

Desde la carpeta raíz del repositorio clonado, ejecutar una sola vez:

```bash
python software/src/prototipo_4_1_revisiones/generar_ino.py
```

El script crea `software/src/prototipo_4_1_revisiones/prototipo_4_1_revisiones.ino`. Luego puede abrirse directamente desde Arduino IDE. Si el archivo base cambia o hay un error de integridad, **se cancela la generación**.

**SHA-256 de la revisión aportada por el equipo:** `208315bc108a2254ccd5680eb2847651c3794a65b03475199f48c6160c0e1201`.

## Funciones documentadas

- Memoria persistente NVS mediante `Preferences`, con máximo de **32 activaciones** y sustitución de la más antigua cuando está lleno.
- Almacenamiento de fecha/hora de inicio, alarma programada, modo, melodía, fecha/hora de detención, origen y duración, cuando se registra el cierre.
- Consulta web `GET /api/historial`, visualización básica con barras por modo y descarga CSV.
- Cuando la alimentación se corta abruptamente, un evento de cierre puede no guardarse.

**Evidencia real:** [registro del 22/11/2026](../../../testing/datos/historial_alarmas_2026-11-22.csv) y [análisis cuantitativo](../../../testing/datos/analisis_historial_2026-11-22.md).

No se ha verificado la compilación y ejecución del archivo reconstruido en un ESP32 desde esta actualización de GitHub; se verificó que las diferencias reproducen exactamente el contenido aportado.
