# Firmware 4.1 revisiones — historial de alarmas

Esta es la versión de la alarma que incorpora el registro de activaciones y detenciones, junto con su visualización y descarga desde la página web.

## Abrir el código

1. Descargar o clonar el repositorio.
2. Abrir [`prototipo_4_1_revisiones.ino`](prototipo_4_1_revisiones.ino) desde esta carpeta en Arduino IDE.
3. Seleccionar **ESP32 Dev Module**, el puerto correspondiente y **Huge APP (3 MB No OTA / 1 MB SPIFFS)**.
4. Instalar las librerías indicadas en la [guía de software](../../README.md), compilar y cargar el programa.

El archivo y su carpeta comparten el mismo nombre, como requiere la organización de proyectos de Arduino IDE. La [versión 4.1 anterior](../alarma_final/alarma_final.ino) se conserva por separado.

## Historial

- Guarda hasta **32 activaciones** en la memoria local del ESP32; al llegar al límite conserva las más recientes.
- Registra la hora programada, la activación, el modo y la melodía. Para los eventos cerrados agrega la detención, su origen y el tiempo transcurrido.
- El panel **Historial de alarmas** muestra una tabla y un gráfico de activaciones por modo, y permite descargar un CSV.
- La página obtiene los registros mediante la ruta `GET /api/historial` y actualiza el panel aproximadamente cada cuatro segundos mientras está abierto.
- Las configuraciones de las alarmas y el historial se guardan por separado con `Preferences`.

El [registro del 22/11/2026](../../../testing/datos/historial_alarmas_2026-11-22.csv) y su [análisis](../../../testing/datos/analisis_historial_2026-11-22.md) documentan el uso de esta revisión.

## Respaldo reproducible

También se conservan [`cambios_historial.json`](cambios_historial.json) y [`generar_ino.py`](generar_ino.py). El script permite reconstruir la revisión desde la versión 4.1 y comprueba la integridad de los archivos:

```bash
python software/src/prototipo_4_1_revisiones/generar_ino.py
```

SHA-256 del archivo de revisión: `208315bc108a2254ccd5680eb2847651c3794a65b03475199f48c6160c0e1201`.
