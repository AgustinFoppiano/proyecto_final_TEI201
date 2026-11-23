# Presentación del proyecto

La [presentación en Canva](https://canva.link/9vdbaq7cbvbrvrb) acompaña la exposición y la demostración de la alarma.

## Recorrido del proyecto

1. **Problema:** las alarmas basadas en sonido pueden ser difíciles de utilizar para personas sordas o con dificultades auditivas.
2. **Solución:** alarma configurable desde el teléfono con vibración, sonido, pantalla OLED y pulsador físico.
3. **Hardware:** ESP32, pantalla, buzzer, relé, motores y alimentación. Ver [componentes](../../hardware/componentes.md) y [fotografías](../../hardware/fotos/README.md).
4. **Software:** red Wi-Fi local, configuración de alarmas y registro de eventos. Ver [guía de software](../../software/README.md).
5. **Diseño 3D:** carcasa, modelo, vistas y planos en [diseño 3D](../../diseno_3d/README.md).
6. **Pruebas:** diez pruebas funcionales el 21/11 y 32 activaciones en el historial del 22/11. Ver [pruebas](../../testing/README.md) y [análisis del historial](../../testing/datos/analisis_historial_2026-11-22.md).

## Demostración de la alarma

1. Conectar el teléfono a la red **Alarma para sordos** y abrir la interfaz.
2. Configurar una alarma próxima y seleccionar el modo y la melodía.
3. Mostrar la activación, la animación y la detención con el pulsador azul o desde la página.
4. Abrir **Historial de alarmas**, revisar la nueva entrada y el gráfico de modos, y mostrar la descarga CSV.

El historial registra las activaciones y detenciones de la alarma. Los resultados de percepción de vibración corresponden a personas que sostuvieron los motores con las manos; el tiempo hasta detener la alarma es el intervalo entre activación y detención registrada.

## Recursos

- [Repositorio del proyecto](../../README.md).
- [Ficha de pruebas funcionales](../../testing/datos/Ficha_pruebas_alarma.pdf).
- [Gráfico de activaciones por modo](../../testing/graficos/activaciones_por_modo_2026-11-22.svg).
- [Videos de funcionamiento](../../testing/evidencias/README.md).
- [Fuentes, librerías e inteligencia artificial](../../FUENTES.md).
