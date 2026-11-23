# Protocolo de verificación del historial

## Objetivo

Revisar el registro de activaciones y detenciones, su visualización en la página y la exportación a CSV de la versión 4.1 revisiones.

## Procedimiento para repetir la prueba

1. Encender la alarma, conectar el teléfono a su red y abrir la interfaz para sincronizar la hora.
2. Abrir **Historial de alarmas** y observar las entradas existentes.
3. Programar una alarma próxima y anotar la hora, melodía y modo seleccionados.
4. Observar la respuesta de la alarma y detenerla con el pulsador azul.
5. Comparar los datos de la nueva entrada con la configuración utilizada y revisar el origen y el tiempo hasta la detención.
6. Repetir una prueba deteniendo la alarma desde la página web y revisar el origen registrado.
7. Descargar el CSV y compararlo con la tabla del historial.
8. Reiniciar el ESP32 de forma controlada, abrir la página y revisar la conservación de las entradas.

**Criterios de revisión:** cada activación observada debe tener su entrada con la hora y modo correspondientes; al detenerla, la entrada debe mostrar el origen. El CSV debe reflejar los datos de la tabla y el historial debe conservarse después de un reinicio normal.

## Evidencia registrada

El [CSV del 22 de noviembre de 2026](datos/historial_alarmas_2026-11-22.csv) contiene 32 activaciones y 29 detenciones. El [análisis](datos/analisis_historial_2026-11-22.md) presenta la distribución por modo y los tres registros sin cierre.

Las [pruebas funcionales](protocolo_pruebas.md) documentan la observación del sonido, la vibración y la pantalla. Los [videos](evidencias/README.md) muestran el funcionamiento y las revisiones del montaje.
