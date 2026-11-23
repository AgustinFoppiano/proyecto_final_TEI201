# Librerías y dependencias

El código final utiliza el paquete de placas ESP32 y tres librerías instaladas desde el gestor de Arduino IDE. Las versiones corresponden al entorno utilizado durante el desarrollo.

## Entorno y librerías instaladas

| Paquete o librería | Versión | Función en el proyecto | Documentación |
| --- | --- | --- | --- |
| esp32 by Espressif Systems | 3.3.12 | Permite compilar y cargar el programa en la placa ESP32. Incluye soporte para Wi-Fi, memoria y otras funciones de la placa. | [Arduino para ESP32](https://github.com/espressif/arduino-esp32) |
| Async TCP by ESP32Async | 3.6.1 | Proporciona la comunicación TCP asíncrona utilizada por el servidor web. | [AsyncTCP](https://github.com/ESP32Async/AsyncTCP) |
| ESP Async WebServer by ESP32Async | 3.12.1 | Permite que el ESP32 entregue la interfaz web y atienda las solicitudes del teléfono. | [ESPAsyncWebServer](https://github.com/ESP32Async/ESPAsyncWebServer) |
| U8g2 by Oliver Kraus | 2.36.19 | Controla la pantalla OLED y permite dibujar las animaciones. | [U8g2](https://github.com/olikraus/u8g2) |

### Instalación

1. En Arduino IDE, instalar **esp32 by Espressif Systems 3.3.12** desde **Tools → Board → Boards Manager**.
2. Abrir el gestor de librerías y buscar cada una de las tres librerías de la tabla.
3. Seleccionar las versiones indicadas e instalarlas.
4. Seleccionar **ESP32 Dev Module** y **Huge APP (3 MB No OTA / 1 MB SPIFFS)** en el menú **Tools**.

La [guía de instalación](../README.md#instalación-y-carga-del-código) explica la configuración completa del entorno.

## Archivos incluidos por la plataforma o el entorno

Estos archivos se incluyen en el código final y se utilizan con el paquete ESP32 y el entorno de compilación:

| Archivo | Función en el programa |
| --- | --- |
| `Arduino.h` | Funciones básicas de Arduino y manejo de pines y tiempo. |
| `WiFi.h` | Creación de la red Wi-Fi del ESP32. |
| `DNSServer.h` | Redirección DNS utilizada por el portal cautivo. |
| `esp_wifi.h` | Configuración de la conexión Wi-Fi del ESP32. |
| `Preferences.h` | Almacenamiento de la configuración de las alarmas y del historial de eventos en memoria no volátil. |
| `Wire.h` | Comunicación I²C con la pantalla OLED. |
| `freertos/FreeRTOS.h` y `freertos/semphr.h` | Mecanismos de sincronización utilizados para controlar las salidas. |
| `math.h` | Funciones matemáticas utilizadas en la animación Quantum Bell. |

La declaración de fuentes y recursos utilizados se encuentra en [`FUENTES.md`](../../FUENTES.md).
