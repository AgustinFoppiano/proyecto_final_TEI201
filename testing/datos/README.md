# Datos de las pruebas

## Pruebas funcionales del 21 de noviembre de 2026

Isidora Herrera realizó diez pruebas de la alarma con la versión 4.1. Para cada una se seleccionó una melodía, una hora y un modo de aviso.

| Modo seleccionado | Pruebas | Resultado observado |
| --- | ---: | --- |
| Solo vibración | 3 | Vibró sin emitir sonido. |
| Solo sonido | 3 | Emitió sonido sin vibrar. |
| Sonido y vibración | 4 | Emitió sonido y vibró. |

En las diez pruebas la pantalla mostró una animación y el pulsador azul detuvo la alarma. Los horarios y melodías están en la [ficha de pruebas](Ficha_pruebas_alarma.pdf); el procedimiento y criterio de funcionamiento están en el [protocolo](../protocolo_pruebas.md).

## Percepción de la vibración

Aproximadamente nueve personas sostuvieron los motores con las manos. Todas indicaron que sentían la vibración y que les parecía fuerte. Durante la prueba podía haber ruido de fondo.

## Registro de eventos del 22 de noviembre de 2026

La revisión con historial generó un CSV con **32 activaciones**. En 29 de ellas figura una detención y 3 quedaron sin registro de cierre.

- [Historial CSV](historial_alarmas_2026-11-22.csv).
- [Análisis de modos, detenciones y tiempos](analisis_historial_2026-11-22.md).
- [Script para reproducir el resumen](resumir_historial.py).

La ficha funcional y el historial corresponden a dos registros diferentes: la primera reúne la observación de sonido, vibración y pantalla; el segundo registra las activaciones y detenciones de la alarma.
