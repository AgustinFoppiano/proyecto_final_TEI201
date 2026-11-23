# Datos de las pruebas

## Registro automatizado del 22 de noviembre de 2026

- [Historial CSV original de 32 activaciones](historial_alarmas_2026-11-22.csv).
- [Análisis de modos, detenciones, tiempos y tres registros sin cierre](analisis_historial_2026-11-22.md).
- [Script para reproducir el cálculo del resumen](resumir_historial.py).


**Este registro se generó desde el firmware de revisión y se analiza por separado de las diez pruebas funcionales del 21/11 descritas a continuación.**


El 21 de noviembre de 2026 se realizaron diez pruebas de funcionamiento de la alarma con la versión 4.1 del código. Las pruebas fueron realizadas por Isidora Herrera.

| Modo seleccionado | Pruebas | Resultado |
|---|---:|---|
| Solo vibración | 3 | En las tres pruebas, la alarma vibró y no emitió sonido. |
| Solo sonido | 3 | En las tres pruebas, la alarma emitió sonido y no vibró. |
| Sonido y vibración | 4 | En las cuatro pruebas, la alarma emitió sonido y vibró. |

En las diez pruebas se mostró una animación en la pantalla y la alarma se detuvo al presionar el botón de apagado.

También se revisaron funciones de la página, como la conexión a la red, la configuración de alarmas y su apagado desde la interfaz.

Los resultados completos, con los horarios y melodías utilizados, están en la [ficha de pruebas](Ficha_pruebas_alarma.pdf).

## Percepción de la vibración

Además, aproximadamente nueve personas sostuvieron los motores con las manos para comprobar si podían sentir la vibración sin depender del sonido. Todas indicaron que la sintieron y que les pareció fuerte. Durante la prueba podía haber ruido de fondo.

## Limitaciones de las pruebas

No se contó con instrumentos para medir la intensidad de la vibración ni con un voltímetro para comprobar el voltaje del montaje. El dato de referencia de 6 V para el motor corresponde al voltaje y no indica por sí solo cuánta vibración produce.

La prueba de percepción se realizó sosteniendo los motores con las manos. No se realizaron pruebas para comprobar si la alarma logra despertar a una persona mientras duerme.
