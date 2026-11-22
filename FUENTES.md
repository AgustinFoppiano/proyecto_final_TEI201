# Fuentes y herramientas utilizadas

## Entorno de desarrollo

- **Programa:** Arduino IDE 2.3.11.
- **Placa seleccionada:** ESP32 Dev Module.
- **Paquete de placas:** ESP32 by Espressif Systems, versión 3.3.12.
- **Partition Scheme:** Huge APP (3 MB No OTA / 1 MB SPIFFS).
- **Documentación:** [Arduino para ESP32](https://github.com/espressif/arduino-esp32).

## Librerías y dependencias utilizadas

Para desarrollar el software de la alarma se utilizaron las siguientes librerías:

### Librerías instaladas

**Async TCP**

- **Versión:** 3.6.1.
- **Desarrollador:** ESP32Async.
- **Uso en el proyecto:** permite la comunicación de red que utiliza el servidor web del ESP32 para intercambiar información con el teléfono.
- **Fuente:** [Repositorio de AsyncTCP](https://github.com/ESP32Async/AsyncTCP).

**ESP Async WebServer**

- **Versión:** 3.12.1.
- **Desarrollador:** ESP32Async.
- **Uso en el proyecto:** permite crear el servidor web alojado en el ESP32. A través de este servidor se muestra la interfaz desde la cual se configuran y controlan las alarmas.
- **Fuente:** [Repositorio de ESPAsyncWebServer](https://github.com/ESP32Async/ESPAsyncWebServer).

**U8g2**

- **Versión:** 2.36.19.
- **Desarrollador:** Oliver Kraus.
- **Uso en el proyecto:** permite controlar la pantalla OLED y mostrar las animaciones asociadas a las melodías de la alarma.
- **Fuente:** [Repositorio de U8g2](https://github.com/olikraus/u8g2).

### Funciones incluidas en la plataforma ESP32 y el entorno de compilación

El código también utiliza los siguientes archivos de la plataforma ESP32 o del entorno de programación:

- **Arduino.h:** proporciona funciones básicas para trabajar con el ESP32, como la configuración y el control de pines.
- **WiFi.h:** permite crear la red Wi-Fi a la que se conecta el teléfono.
- **DNSServer.h:** se utiliza para dirigir la conexión hacia la interfaz de la alarma mediante un portal cautivo.
- **Preferences.h:** permite guardar las alarmas configuradas en la memoria del ESP32.
- **Wire.h:** permite la comunicación con la pantalla OLED mediante I²C.
- **esp_wifi.h:** se utiliza para realizar configuraciones de la red Wi-Fi del ESP32.
- **FreeRTOS.h y semphr.h:** proporcionan mecanismos de sincronización que ayudan a coordinar el control de las salidas de sonido y vibración.
- **math.h:** proporciona funciones matemáticas utilizadas en las animaciones.

**Documentación:** [Arduino para ESP32](https://github.com/espressif/arduino-esp32).

## Código y recursos externos

### Melodías para buzzer: Take On Me y Never Gonna Give You Up

Se adaptaron fragmentos de las secuencias de notas del repositorio `arduino-songs` para reproducir ambas melodías mediante el buzzer del ESP32.

- **Take On Me:** [Código original](https://github.com/robsoncouto/arduino-songs/blob/master/takeonme/takeonme.ino).
- **Never Gonna Give You Up:** [Código original](https://github.com/robsoncouto/arduino-songs/blob/master/nevergonnagiveyouup/nevergonnagiveyouup.ino).

### Melodía para buzzer: Bad Apple

La melodía se adaptó para su reproducción mediante un solo buzzer en el sistema de alarma.

- **Fuentes:** [ESP32 Bad Apple Player](https://github.com/LiZhiY0u/esp32-bad-apple-player) y [badderapple](https://github.com/cnlohr/badderapple).

### BadCodec

Se utilizó BadCodec durante el proceso de conversión de algunos videos en animaciones para la pantalla OLED.

- **Autor:** ghostinkoma.
- **Repositorio:** [BadCodec](https://github.com/ghostinkoma/BadCodec).
- **Licencia:** [BadCodec Non-Commercial License](https://github.com/ghostinkoma/BadCodec/blob/main/LICENSE.md).

## Videos y animaciones para la pantalla OLED

Se recortaron y adaptaron fragmentos de video para reproducirlos en la pantalla OLED de la alarma.

### Take On Me

Se utilizó un fragmento del video musical de *Take On Me*, de a-ha.

- **Video:** [Take On Me](https://youtu.be/djV11Xbc914).

### Never Gonna Give You Up

Se utilizó un fragmento del video de *Never Gonna Give You Up*, asociado a la animación de Rickroll.

- **Video:** [Rickroll](https://youtu.be/QDia3e12czc).

### Sans

Se utilizó un fragmento de una animación de Sans para acompañar la melodía de *Megalovania*.

- **Video:** [Animación de Sans en TikTok](https://vt.tiktok.com/ZSseR6KsY/).

### Presidente de Monstruos vs. Aliens

Se utilizó un recorte del video del presidente tocando el piano. Este fragmento se incorporó a la animación asociada a *Take On Me*.

- **Referencia del clip:** fragmento de *Monstruos vs. Aliens* con marca de agua de TikTok `@emperordarthkermit`.

### Bad Apple

Se adaptó un fragmento del video *Bad Apple* para reproducirlo en la pantalla OLED.

- **Video de referencia:** [Bad Apple!! PV](https://www.youtube.com/watch?v=FtutLA63Cp8).

## Uso de inteligencia artificial

### ChatGPT

- **Herramienta:** ChatGPT, de OpenAI.
- **Uso en el desarrollo:** se utilizó para generar y modificar gran parte del código del prototipo a partir de las ideas, fotografías, diseños y descripciones del proyecto.
- **Funciones del código:** el programa desarrollado incluye la interfaz web, la configuración de alarmas y el control del buzzer, la vibración y la pantalla OLED.
- **Supervisión y correcciones:** se supervisó el desarrollo del código, se revisaron las versiones entregadas y se solicitaron ajustes o correcciones cuando se identificaron errores.
- **Animación de reloj y tocadiscos:** se creó una animación de un reloj y un tocadiscos para acompañar las melodías *Homecoming* y *Space Bell*.
- **Animación de Quantum Bell:** se creó y adaptó una animación que muestra la hora programada de la alarma, acompañada de ondas y destellos.
- **Indicación utilizada:** se solicitó que la animación de *Quantum Bell* mostrara la hora elegida para cada alarma, en lugar de una hora fija.
- **Adaptación al proyecto:** las animaciones se integraron al programa del ESP32 y se asociaron a las melodías seleccionadas desde la interfaz de la alarma.


## Documentación asistida por IA — catálogo de hardware (22 de noviembre de 2026)

- **Herramienta:** ChatGPT (OpenAI).
- **Uso:** estructuración y redacción del [catálogo técnico de componentes](hardware/componentes.md) usando las fotografías y descripciones aportadas por el equipo, y revisión de su ubicación respecto de la pauta TEI201 Avance #3.
- **Control de exactitud:** características visuales corroboradas se distinguen de datos publicados por proveedores y de especificaciones pendientes de verificación. El equipo debe cotejar modelos, dimensiones, cableado, consumos y costos antes de presentar el prototipo como definitivo.

## Referencias comerciales fotográficas (22 de noviembre de 2026)

La documentación de hardware muestra fotografías reales de productos similares mediante enlaces externos, con atribución a las publicaciones correspondientes. El material se utiliza únicamente como referencia visual: **no implica que el equipo haya comprado esas marcas o modelos exactos**. Las fotografías y sus respectivas páginas se enumeran en [hardware/imagenes_componentes/README.md](hardware/imagenes_componentes/README.md).
