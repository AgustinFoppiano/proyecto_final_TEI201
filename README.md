# Alarma accesible con vibración y sonido

Proyecto de TEI201 para personas sordas o con dificultades auditivas. La alarma se configura desde un teléfono y entrega avisos mediante vibración, sonido o ambos. Una pantalla OLED muestra la hora y animaciones asociadas a las melodías.

**Integrantes:** Benjamín Barrionuevo, Francisca Borne, Agustín Foppiano, Isidora Herrera y Luciano Vera.  
**ODS:** 10, reducción de las desigualdades.

## Funcionamiento

El ESP32 crea una red Wi-Fi local para acceder a la página de la alarma. En ella se pueden crear, editar, activar y desactivar hasta diez alarmas, elegir su modo, melodía y repetición. Al sonar una alarma, se puede detener con el pulsador azul o desde la página. La configuración queda guardada en la memoria del dispositivo.

La versión **4.1 revisiones** incorpora un historial de activaciones y detenciones, una tabla, un gráfico por modo y la descarga de los registros en CSV. El historial conserva las 32 activaciones más recientes y se consulta desde la misma página.

## Componentes principales

ESP32 DevKit, pantalla OLED I²C de 1,3 pulgadas, buzzer pasivo, módulo de relé de un canal, dos motores vibratorios, pulsadores, módulo de alimentación, baterías y cables de conexión. El [catálogo de componentes](hardware/componentes.md) describe su función y la [BOM](hardware/bom/README.md) reúne las cantidades y el presupuesto de referencia.

## Código y configuración

- **Versión con historial:** [`prototipo_4_1_revisiones.ino`](software/src/prototipo_4_1_revisiones/prototipo_4_1_revisiones.ino).
- **Versión 4.1 anterior:** [`alarma_final.ino`](software/src/alarma_final/alarma_final.ino).
- **Versiones de desarrollo:** [`software/versiones_anteriores/`](software/versiones_anteriores/README.md).

El proyecto utiliza Arduino IDE 2.3.11, la placa **ESP32 Dev Module**, el paquete ESP32 de Espressif 3.3.12 y la partición **Huge APP (3 MB No OTA / 1 MB SPIFFS)**. Las librerías instaladas son AsyncTCP 3.6.1, ESP Async WebServer 3.12.1 y U8g2 2.36.19.

1. Descargar o clonar el repositorio y abrir el archivo de la versión con historial desde su carpeta en Arduino IDE.
2. Instalar las dependencias, seleccionar la placa, el puerto y la partición indicados.
3. Compilar y cargar el programa al ESP32.
4. En el teléfono, conectarse a la red **Alarma para sordos** con la contraseña `porfavor`. Seleccionar «Iniciar sesión» para abrir el portal o ingresar a **http://4.3.2.1** en el navegador.
5. Al abrir la página se sincroniza la hora del ESP32. Configurar una alarma y abrir **Historial de alarmas** para consultar la tabla y el gráfico.

La [guía de software](software/README.md) explica la instalación y el uso paso a paso. Después de reiniciar el ESP32, se debe abrir la página para volver a sincronizar la hora.

## Pruebas y resultados

El 21 de noviembre se realizaron diez pruebas funcionales: tres en vibración, tres en sonido y cuatro en modo combinado. En ellas se observó el modo elegido, la animación y la detención mediante el pulsador. Además, aproximadamente nueve personas percibieron la vibración al sostener los motores.

El [historial del 22 de noviembre](testing/datos/historial_alarmas_2026-11-22.csv) contiene 32 activaciones: 29 con detención registrada y 3 sin registro de cierre. El [análisis](testing/datos/analisis_historial_2026-11-22.md) explica los resultados y cómo interpretarlos.

## Contenido del repositorio

| Carpeta | Contenido |
| --- | --- |
| [software](software/README.md) | Firmware, versiones, librerías e instrucciones. |
| [hardware](hardware/README.md) | Componentes, conexiones programadas, presupuesto y fotografías. |
| [diseno_3d](diseno_3d/README.md) | Archivo Fusion 360, vistas y planos. |
| [testing](testing/README.md) | Protocolos, pruebas, historial, análisis y videos. |
| [iteraciones](iteraciones/README.md) | Evolución del diseño y decisiones tomadas. |
| [documentacion](documentacion/README.md) | Resumen del proyecto y presentación. |
| [FUENTES.md](FUENTES.md) | Librerías, recursos y herramientas utilizadas. |

La [presentación en Canva](https://canva.link/9vdbaq7cbvbrvrb) acompaña el repositorio para la exposición del proyecto.
