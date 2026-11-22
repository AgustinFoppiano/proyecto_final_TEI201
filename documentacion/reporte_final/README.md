# Resumen del proyecto

## Problema y objetivo

Las alarmas convencionales dependen principalmente del sonido, lo que puede dificultar su uso para personas con discapacidad auditiva. El proyecto consiste en una alarma que utiliza vibración como aviso y también puede emitir sonido para una persona acompañante. Se relaciona con el ODS 10: Reducción de las desigualdades.

**Integrantes:** Benjamín Barrionuevo, Francisca Borne, Agustín Foppiano, Isidora Herrera y Luciano Vera.

## Funcionamiento

La alarma utiliza un ESP32, una pantalla OLED, dos motores vibratorios, un buzzer, un relé y botones físicos. Desde un teléfono conectado a la red Wi-Fi creada por el ESP32 se puede configurar la hora, la melodía, la repetición y el modo de aviso: vibración, sonido o ambos.

Cuando se activa la alarma, la pantalla muestra una animación asociada a la melodía elegida. La alarma se puede detener con el botón físico o desde la página. Las configuraciones se guardan en la memoria del ESP32; después de reiniciarlo, se vuelve a sincronizar la hora al abrir la página desde el teléfono.

El código principal es la [versión 4.1](../../software/src/alarma_final/alarma_final.ino). Las instrucciones de instalación y uso están en la [carpeta de software](../../software/README.md).

## Desarrollo y dificultades

En las primeras pruebas, las conexiones realizadas en protoboard podían soltarse. La pantalla OLED a veces requería acomodar los cables para mostrar una animación y los cables de los motores podían desconectarse al vibrar. En el montaje posterior se soldaron las conexiones; la pantalla y los motores mantienen su funcionamiento al moverlos. Se consideró que el encapsulado debe ayudar a mantener los motores estables.

Durante otra prueba, el portapilas se calentó incluso estando desconectado del resto del circuito. Ante la posibilidad de un cortocircuito en el portapilas, se decidió reemplazarlo. Las dificultades y sus evidencias se encuentran en el [reporte de pruebas](../../testing/reportes/README.md).

## Pruebas y resultados

El 21 de noviembre de 2026 se realizaron diez pruebas: tres en modo solo vibración, tres en modo solo sonido y cuatro con sonido y vibración. En cada caso se observó la respuesta correspondiente al modo elegido, se mostró la animación y la alarma se detuvo al presionar el botón.

Además, aproximadamente nueve personas sostuvieron los motores con las manos. Todas indicaron que percibían la vibración y que les parecía fuerte. No se midió la intensidad con instrumentos ni se realizó una prueba para determinar si la alarma despierta a una persona dormida.

Los horarios, melodías y funciones revisadas están en la [ficha de pruebas](../../testing/datos/Ficha_pruebas_alarma.pdf). Los videos se encuentran en [evidencias](../../testing/evidencias/README.md).

## Diseño 3D

El repositorio contiene un [archivo de Fusion 360](../../diseno_3d/fusion360/), [dos renders](../../diseno_3d/renders/) y un [plano de conjunto](../../diseno_3d/planos/plano_conjunto_v1.pdf) correspondientes al diseño disponible.

## Fuentes

Las librerías, herramientas y recursos utilizados se detallan en [FUENTES.md](../../FUENTES.md).
