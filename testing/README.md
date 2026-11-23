# Pruebas de la alarma

El 21 de noviembre de 2026, Isidora Herrera realizó diez pruebas con la versión 4.1 del código para revisar los modos de aviso, las animaciones y el botón de apagado.

## Procedimiento

1. Conectar el teléfono a la red de la alarma y abrir la página de configuración.
2. Configurar una alarma, seleccionando una hora, una melodía y un modo de aviso.
3. Cuando se active, observar si suena, vibra y muestra la animación correspondiente.
4. Detener la alarma con el botón de apagado y registrar lo observado.
5. Repetir la prueba con los distintos modos y melodías.

Para considerar correcta cada prueba, el sonido y la vibración deben corresponder al modo elegido, la pantalla debe mostrar la animación y la alarma debe detenerse al presionar el botón.

## Resultados

| Modo | Pruebas | Resultado observado |
| --- | --- | --- |
| Solo vibración | 3 | En las tres pruebas vibró y no sonó. |
| Solo sonido | 3 | En las tres pruebas sonó y no vibró. |
| Sonido y vibración | 4 | En las cuatro pruebas sonó y vibró. |

En las diez pruebas se mostró la animación y la alarma se detuvo al presionar el botón. También se comprobaron funciones de la página, la memoria de las alarmas y su activación con el teléfono desconectado. Los horarios y melodías están en la [ficha de pruebas](datos/Ficha_pruebas_alarma.pdf).

## Percepción de la vibración

Aproximadamente nueve personas sostuvieron los motores con las manos. Todas indicaron que sentían la vibración y que les parecía fuerte. Esta prueba fue perceptiva y no se midió la intensidad con instrumentos.

Las pruebas muestran que la vibración puede percibirse al sostener los motores, pero no comprueban si la alarma logra despertar a una persona dormida.

## Registro histórico de la revisión 4.1 (22/11/2026)

El historial exportado por el ESP32 reúne **32 activaciones**, **29 con detención registrada** (19 por botón físico y 10 por web) y **3 sin registro de cierre**. Este conjunto es distinto de las diez pruebas funcionales descritas antes; no debe sumarse como si todos los eventos representaran ensayos de eficacia para despertar.

- [CSV original de activaciones](datos/historial_alarmas_2026-11-22.csv).
- [Análisis cuantitativo, interpretación y limitaciones](datos/analisis_historial_2026-11-22.md).
- [Protocolo propuesto para repetir y validar el registro](protocolo_registro_eventos.md).

## Archivos de esta carpeta

- [Datos y resultados](datos/README.md): resumen de las pruebas y sus límites.
- [Ficha de pruebas](datos/Ficha_pruebas_alarma.pdf): horarios, melodías y comprobaciones de la interfaz.
- [Reporte de pruebas y dificultades](reportes/README.md): resultados, conexiones y falla del portapilas.
- [Evidencias](evidencias/README.md): videos de las pruebas y enlaces de descarga.
