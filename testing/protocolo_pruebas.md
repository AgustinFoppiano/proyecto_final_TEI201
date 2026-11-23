# Protocolo de pruebas funcionales

## Objetivo

Comprobar la respuesta de la alarma en los tres modos, la visualización de las animaciones y la detención mediante el pulsador azul.

## Condiciones

Las pruebas se realizaron el **21 de noviembre de 2026** con la versión 4.1. Isidora Herrera configuró las alarmas desde un teléfono conectado a la red del ESP32. Para cada ensayo se eligió una hora, una melodía y un modo.

## Procedimiento

1. Encender el dispositivo y conectar el teléfono a su red Wi-Fi.
2. Abrir la página, sincronizar la hora y programar una alarma próxima.
3. Seleccionar la melodía y uno de los tres modos de aviso.
4. Al activarse, observar el sonido, la vibración y la animación de la pantalla.
5. Presionar el botón azul para detener la alarma y registrar el resultado.
6. Repetir con otras melodías y modos.

**Criterio de funcionamiento:** las salidas deben corresponder al modo elegido, la pantalla debe mostrar una animación y el pulsador debe detener la alarma activa.

## Resultados

| Modo | Cantidad | Resultado observado |
| --- | ---: | --- |
| Solo vibración | 3 | Vibración sin sonido en las tres pruebas. |
| Solo sonido | 3 | Sonido sin vibración en las tres pruebas. |
| Sonido y vibración | 4 | Sonido y vibración en las cuatro pruebas. |

En las diez pruebas se mostró la animación y la alarma se detuvo al presionar el botón. La [ficha de pruebas](datos/Ficha_pruebas_alarma.pdf) incluye horarios y melodías.

## Percepción de la vibración

Aproximadamente nueve personas sostuvieron los motores con las manos; todas indicaron que percibían la vibración y que les parecía fuerte. Durante la observación podía haber ruido de fondo. Esta prueba describe la percepción al sostener los motores y complementa las pruebas funcionales.

## Registro de eventos

La revisión 4.1 añadió un historial de activaciones y detenciones. El [CSV del 22 de noviembre](datos/historial_alarmas_2026-11-22.csv) contiene 32 activaciones y el [análisis](datos/analisis_historial_2026-11-22.md) resume los modos y las detenciones registradas. El [protocolo del historial](protocolo_registro_eventos.md) describe cómo repetir su revisión.

Los resultados y las dificultades de conexiones y alimentación se reúnen en el [reporte de pruebas](reportes/README.md).
