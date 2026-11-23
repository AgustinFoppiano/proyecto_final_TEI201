# Resumen del proyecto

## Problema y objetivo

Las alarmas convencionales dependen principalmente del sonido, lo que puede dificultar su uso para personas con discapacidad auditiva. El proyecto consiste en una alarma que utiliza vibración como aviso y también puede emitir sonido para una persona acompañante. Se relaciona con el ODS 10: reducción de las desigualdades.

**Integrantes:** Benjamín Barrionuevo, Francisca Borne, Agustín Foppiano, Isidora Herrera y Luciano Vera.

## Funcionamiento

La alarma utiliza un ESP32, una pantalla OLED, dos motores vibratorios, un buzzer, un relé y botones físicos. Desde un teléfono conectado a la red Wi-Fi creada por el ESP32 se configura la hora, la melodía, la repetición y el modo de aviso: vibración, sonido o ambos.

La pantalla muestra una animación asociada a la melodía. La alarma se detiene con el botón físico o desde la página. Las configuraciones se guardan en la memoria del ESP32; después de reiniciarlo, la hora se sincroniza al abrir la página desde el teléfono.

La [versión 4.1 revisiones](../../software/src/prototipo_4_1_revisiones/prototipo_4_1_revisiones.ino) agrega un historial local, tabla, gráfico por modo y exportación CSV. Las instrucciones se encuentran en la [guía de software](../../software/README.md).

## Desarrollo y dificultades

Durante las primeras pruebas se montaron los componentes en protoboard. Al moverse el montaje, algunas conexiones podían soltarse. Se utilizó la versión 3.7 para reproducir una animación en bucle y revisar el contacto de la pantalla. En el montaje posterior se soldaron conexiones de la pantalla y de los motores; el encapsulado considera la sujeción de los motores para mantenerlos estables.

Durante otra prueba se observó calentamiento en el portapilas, incluso desconectado del resto del circuito. Ante la posibilidad de un cortocircuito en ese componente se decidió reemplazarlo. Las dificultades y sus evidencias se detallan en el [reporte de pruebas](../../testing/reportes/README.md).

## Pruebas y resultados

El 21 de noviembre de 2026 se realizaron diez pruebas: tres en modo vibración, tres en sonido y cuatro en modo combinado. En cada caso se observó la respuesta correspondiente al modo elegido, se mostró la animación y la alarma se detuvo al presionar el botón. Los horarios y melodías están en la [ficha de pruebas](../../testing/datos/Ficha_pruebas_alarma.pdf).

Aproximadamente nueve personas sostuvieron los motores con las manos. Todas indicaron que percibían la vibración y que les parecía fuerte.

El [historial del 22 de noviembre](../../testing/datos/historial_alarmas_2026-11-22.csv) reúne 32 activaciones: 14 en modo combinado, 10 en vibración y 8 en sonido. Hay 29 detenciones registradas y 3 entradas sin registro de cierre. El tiempo medio hasta la detención en los 29 registros cerrados fue de 9,1 segundos. El [análisis](../../testing/datos/analisis_historial_2026-11-22.md) explica estos resultados y el alcance de las mediciones.

## Diseño y costos

El repositorio contiene un [archivo de Fusion 360](../../diseno_3d/fusion360/README.md), [vistas del diseño](../../diseno_3d/renders/README.md) y [planos](../../diseno_3d/planos/README.md). La [BOM](../../hardware/bom/README.md) presenta cantidades y una estimación de costo basada en referencias comerciales.

## Fuentes

Las librerías, herramientas y recursos utilizados se detallan en [FUENTES.md](../../FUENTES.md).
