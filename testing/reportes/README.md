# Pruebas y dificultades del prototipo

## Evidencia posterior: historial de la versión con registro

El 22 de noviembre de 2026 el software exportó un [historial de 32 activaciones](../datos/historial_alarmas_2026-11-22.csv). De ellas, 29 presentan evento de cierre y 3 permanecen sin detención registrada. La persona responsable de la captura señaló que durante ciertas pruebas se interrumpía la alimentación del ESP32; sin embargo, el CSV no contiene una medición independiente para confirmar la causa de cada caso. El análisis numérico y los límites de interpretación se explican en el [análisis del historial](../datos/analisis_historial_2026-11-22.md).


## Pruebas de funcionamiento

El 21 de noviembre de 2026 se realizaron diez pruebas con la versión 4.1 del código. Se utilizaron distintas melodías y los tres modos de funcionamiento: solo vibración, solo sonido, y sonido con vibración.

En los diez intentos se observó la respuesta correspondiente al modo seleccionado, se mostró una animación en la pantalla y la alarma se detuvo al presionar el botón de apagado. Los horarios, melodías y resultados están registrados en la [ficha de pruebas](../datos/Ficha_pruebas_alarma.pdf).

Además, aproximadamente nueve personas sostuvieron los motores con las manos para comprobar si podían sentir la vibración. Todas indicaron que la percibieron y que les pareció fuerte. Esta prueba fue perceptiva y no incluyó una medición con instrumentos.

## Dificultades con las conexiones

Durante las primeras etapas, los componentes se probaron en una protoboard y algunas conexiones no estaban soldadas. Esto dificultaba mantener un contacto estable entre los cables, la pantalla OLED y el ESP32.

En ocasiones, la pantalla solo mostraba la animación después de acomodar sus conexiones. Para revisarla se utilizó la versión 3.7 del programa, que reproducía una animación en bucle. También se consultaron los mensajes del Monitor serie y se reinició el ESP32 para comprobar si la pantalla era detectada.

Los cables de los motores también podían soltarse por el movimiento producido al vibrar. Durante las pruebas fue necesario sujetarlos o volver a conectarlos para continuar.

En la versión final, los motores quedaron soldados y mantienen su conexión al vibrar. La pantalla también permanece funcionando al moverla. Los motores aún se desplazan por la vibración, por lo que se contempla sujetarlos dentro del encapsulado.

## Falla del portapilas

Durante una prueba, un cable se soltó de su soldadura. Al volver a conectarlo, se produjo una falla en el portapilas y se observó calentamiento. Se revisaron las conexiones y la soldadura, pero el portapilas volvió a calentarse al insertar las pilas, incluso estando desconectado del resto del circuito.

El proyecto funcionó en las pruebas realizadas y el calentamiento se presentó en el portapilas. Se consideró que podía tratarse de un cortocircuito en ese componente y, como solución, se decidió reemplazarlo. Se grabaron videos durante la revisión del portapilas.

## Alcance

Las pruebas permitieron revisar las funciones de la alarma y comprobar que la vibración podía percibirse al sostener los motores. No se midió la intensidad de la vibración y no se realizó una prueba para comprobar si la alarma logra despertar a una persona dormida.
