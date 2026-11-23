# Código fuente

El código principal del proyecto es **[alarma_final/alarma_final.ino](alarma_final/alarma_final.ino)**. El encabezado del archivo lo identifica como `PRUEBA PROTOTIPO 4_1`.

Para abrirlo en Arduino IDE, descargar el repositorio y abrir `alarma_final.ino` desde la carpeta `software/src/alarma_final/`. El archivo y su carpeta tienen el mismo nombre para mantener la estructura de un proyecto Arduino.

El programa reúne en un solo archivo la interfaz web, la configuración de alarmas, el control del buzzer y del relé, y los datos de las animaciones de la pantalla OLED.

En `setup()` se preparan las salidas, la memoria, la red, el servidor y la pantalla. En `loop()` se atienden las solicitudes DNS, se comprueban las alarmas y se actualizan el pulsador, las salidas y la pantalla.

Para compilarlo se utilizan **ESP32 Dev Module**, el esquema de partición **Huge APP (3 MB No OTA / 1 MB SPIFFS)** y las dependencias indicadas en [Librerías](../librerias/README.md). Las instrucciones completas están en [Software](../README.md).

Las versiones previas están en [`versiones_anteriores/`](../versiones_anteriores/). También está documentada la [revisión 4.1 con historial y exportación CSV](prototipo_4_1_revisiones/README.md), reconstruible mediante una diferencia verificada sobre el archivo base. El monitor serie se configura a **115200 baudios**.
