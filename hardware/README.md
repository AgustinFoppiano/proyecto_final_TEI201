# Hardware de la alarma

El ESP32 coordina la pantalla, el sonido, la vibración y los controles. La pantalla entrega información visual; los dos motores proporcionan el aviso por vibración, y el buzzer permite agregar sonido cuando se selecciona ese modo.

## Componentes

| Componente | Cantidad | Función |
| --- | ---: | --- |
| ESP32 DevKit V1 | 1 | Control del sistema y red Wi-Fi local. |
| Pantalla OLED I²C de 1,3 pulgadas | 1 | Muestra la hora y las animaciones. |
| Buzzer pasivo | 1 | Reproduce las melodías. |
| Módulo de relé de un canal | 1 | Controla la alimentación de los motores. |
| Motores vibratorios | 2 | Generan el aviso por vibración. |
| Pulsadores azul y blanco | 2 | Detención de la alarma y control del módulo de alimentación, respectivamente. |
| Módulo portabaterías y celdas | 1 módulo y 2 celdas | Alimentación portátil. |
| Protoboard, cables y conectores | Según montaje | Unión y organización del circuito. |

Se contempla la utilización de dos protoboards compactas de 400 puntos en la distribución del encapsulado. Las fotografías muestran el montaje de pruebas con una protoboard grande.

## Documentación

- [Catálogo de componentes](componentes.md): identificación y función de cada pieza.
- [BOM y presupuesto](bom/README.md): cantidades, referencias comerciales y estimación de costos.
- [Conexiones configuradas](esquemas/README.md): pines utilizados por el firmware.
- [Fotografías del montaje](fotos/README.md): vistas reales del circuito desde distintos ángulos.
- [Diseño 3D](../diseno_3d/README.md): modelo, vistas y planos del encapsulado.

El ESP32 facilita la configuración desde el teléfono mediante su propia red Wi-Fi. La OLED utiliza comunicación I²C y el relé permite controlar la alimentación de los motores. La [guía de software](../software/README.md) explica la configuración de las señales y la secuencia de funcionamiento.
