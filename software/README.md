# Software de la alarma

El software se ejecuta en un ESP32 y permite configurar alarmas desde un teléfono conectado a la red Wi-Fi del dispositivo. Según el modo seleccionado, la alarma utiliza sonido, vibración o ambos. También controla una pantalla OLED con animaciones asociadas a las melodías.

## Archivos de esta carpeta

| Ruta | Contenido |
| --- | --- |
| [`src/alarma_final/alarma_final.ino`](src/alarma_final/alarma_final.ino) | Código principal de la alarma, identificado en el archivo como versión 4.1. |
| [`src/README.md`](src/README.md) | Ubicación y organización del código fuente. |
| [`versiones_anteriores/`](versiones_anteriores/) | Códigos utilizados en etapas anteriores y prueba del motor. |
| [`librerias/README.md`](librerias/README.md) | Dependencias y versiones utilizadas. |
| [`docs/README.md`](docs/README.md) | Funcionamiento interno y comunicación entre la interfaz y el ESP32. |

Las fuentes de librerías, recursos y herramientas se encuentran en [`FUENTES.md`](../FUENTES.md).

## Entorno utilizado

| Elemento | Configuración |
| --- | --- |
| Entorno | Arduino IDE 2.3.11 |
| Placa seleccionada | ESP32 Dev Module |
| Paquete de placas | esp32 by Espressif Systems 3.3.12 |
| Esquema de partición | Huge APP (3 MB No OTA / 1 MB SPIFFS) |
| AsyncTCP | 3.6.1, de ESP32Async |
| ESP Async WebServer | 3.12.1, de ESP32Async |
| U8g2 | 2.36.19, de Oliver Kraus |

El programa está escrito en C/C++ para Arduino. La interfaz utiliza HTML, CSS y JavaScript incorporados en el mismo archivo `.ino`.

## Instalación y carga del código

### 1. Preparar Arduino IDE y el ESP32

1. Instalar [Arduino IDE](https://www.arduino.cc/en/software/).
2. En **File → Preferences**, agregar la siguiente dirección en el campo de URLs adicionales del gestor de placas, si aún no está agregada:

   ```text
   https://espressif.github.io/arduino-esp32/package_esp32_index.json
   ```

3. Abrir **Tools → Board → Boards Manager**, buscar `esp32` e instalar **esp32 by Espressif Systems**, versión **3.3.12**.
4. Desde el gestor de librerías, instalar **Async TCP 3.6.1**, **ESP Async WebServer 3.12.1** y **U8g2 2.36.19**. Sus funciones y enlaces están en [Librerías](librerias/README.md).
5. Conectar el ESP32 al computador con un cable USB que permita transferir datos.
6. En **Tools → Board**, seleccionar **ESP32 Dev Module**. En **Tools → Port**, seleccionar el puerto del dispositivo.
7. En **Tools → Partition Scheme**, seleccionar **Huge APP (3 MB No OTA / 1 MB SPIFFS)**.

### 2. Abrir y cargar la versión final

1. Descargar el repositorio o clonarlo en el computador.
2. Abrir en Arduino IDE el archivo [`alarma_final.ino`](src/alarma_final/alarma_final.ino), dentro de la carpeta `software/src/alarma_final/`.
3. Presionar **Verify** para compilar el programa.
4. Si la compilación termina correctamente, presionar **Upload** para cargarlo en el ESP32.
5. Esperar el mensaje de carga terminada. El monitor serie puede abrirse a **115200 baudios** para revisar los mensajes de inicio y detección de la pantalla.

La carpeta y el archivo principal comparten el nombre `alarma_final`, de acuerdo con la organización de proyectos de Arduino IDE.

## Conexión desde el teléfono

1. Encender el ESP32 con el código cargado.
2. En el teléfono, buscar y seleccionar la red **Alarma para sordos**.
3. Ingresar la contraseña configurada en el código: `porfavor`.
4. Si el portal no se abre automáticamente, abrir el navegador e ingresar a **http://4.3.2.1**.
5. Al iniciar la página, el teléfono envía su hora y zona horaria al ESP32. La interfaz muestra el estado de sincronización.
6. Crear una alarma, elegir la hora, la melodía, el modo de aviso y la repetición, y guardar los cambios.

La interfaz se encuentra alojada en el ESP32 y se utiliza mediante su red local. El teléfono se conecta directamente al dispositivo para configurarlo.

## Funciones implementadas en el código final

- Crear, editar, eliminar, activar y desactivar hasta **10 alarmas**.
- Configurar una alarma para una sola vez, todos los días, días elegidos o una fecha específica.
- Seleccionar **sonido**, **vibración** o **sonido y vibración**.
- Elegir entre siete melodías y mostrar su animación correspondiente en la pantalla OLED.
- Detener la alarma activa desde la interfaz web o mediante el pulsador configurado en el código.
- Guardar la configuración de las alarmas en la memoria del ESP32 mediante `Preferences`.

### Melodías y animaciones

| Melodía | Animación configurada |
| --- | --- |
| Homecoming | Reloj y tocadiscos. |
| Quantum Bell | Hora de la alarma acompañada de ondas y destellos. |
| Space Bell | Reloj y tocadiscos. |
| Megalovania | Animación de Sans. |
| Never Gonna Give You Up | Rickroll. |
| Take On Me | Alterna el clip del presidente tocando el piano y el video de Take On Me. |
| Bad Apple | Animación de Bad Apple. |

## Configuración de pines en el código

| Función | Pin configurado | Uso en el programa |
| --- | --- | --- |
| Buzzer | GPIO18 / D18 | Generación de tonos. |
| Control de vibración | GPIO15 / D15 | Señal de control del relé. |
| Pulsador para detener | GPIO27 / D27 | Entrada con resistencia interna `INPUT_PULLUP`; el código considera un pulsador entre el pin y GND. |
| OLED: SDA | GPIO21 / D21 | Datos de la comunicación I²C. |
| OLED: SCL | GPIO22 / D22 | Reloj de la comunicación I²C. |

Para la pantalla se utiliza en el programa la configuración `U8G2_SH1106_128X64_NONAME_1_HW_I2C`. El programa busca la pantalla en las direcciones I²C `0x3C` y `0x3D`.

El código agrupa notas y limita los tiempos de conmutación del relé; por ello, la vibración se relaciona con la melodía, pero el relé no cambia necesariamente de estado en cada nota o pausa. Las conexiones y la alimentación del montaje se documentan en [hardware](../hardware/README.md).

## Hora y almacenamiento

Al abrir la interfaz, el teléfono envía la hora local al ESP32. A partir de esa sincronización, el programa calcula el tiempo transcurrido mediante `millis()`. Tras reiniciar el ESP32 es necesario abrir la interfaz nuevamente para sincronizar la hora antes de que se comprueben las alarmas.

La configuración de las alarmas se guarda en la memoria no volátil con `Preferences`. La interfaz muestra la hora sincronizada, las alarmas configuradas y el estado de la alarma. Este archivo de código guarda configuraciones de alarmas; no implementa un historial de mediciones ambientales ni gráficas históricas.

## Si la interfaz o la alarma no responde

- Revisar que el teléfono esté conectado a **Alarma para sordos** y abrir `http://4.3.2.1` manualmente.
- Comprobar en la página que la hora esté sincronizada y que la alarma se encuentre activada.
- Si la pantalla no muestra la animación, revisar las conexiones I²C y los mensajes del monitor serie a 115200 baudios.
- Si Arduino IDE informa un error de compilación, revisar la placa, las versiones de las librerías y el esquema de partición indicados arriba.

Para la explicación del programa y de sus rutas web, consultar [Documentación de software](docs/README.md).
