# Funcionamiento del software

La versión final reúne la interfaz, la lógica de alarmas y el control de las salidas en [`alarma_final.ino`](../src/alarma_final/alarma_final.ino).

## Organización general

1. Al iniciar, el ESP32 configura las salidas, recupera las alarmas guardadas y crea su red Wi-Fi.
2. El servidor HTTP entrega al teléfono una página con la interfaz para configurar y consultar las alarmas.
3. Al abrir la página, el teléfono envía la hora local al ESP32.
4. Las alarmas creadas o modificadas se guardan con `Preferences`.
5. El programa comprueba las alarmas activas y, cuando corresponde, inicia el sonido, la vibración o ambos, junto con la animación asociada.
6. La alarma en curso puede detenerse desde la página o desde el pulsador definido en el programa.

## Módulos principales

| Función o grupo | Responsabilidad |
| --- | --- |
| `crearRedWifi()` | Configura la red Wi-Fi local del ESP32. |
| `configurarServidor()` | Define las rutas que recibe la interfaz y las respuestas del servidor. |
| `guardarAlarmasEnMemoria()` y `cargarAlarmasDeMemoria()` | Guardan y recuperan la configuración de las alarmas mediante `Preferences`. |
| `obtenerHoraLocal()` y `comprobarAlarmas()` | Calculan la hora desde la sincronización y revisan si una alarma debe activarse. |
| `iniciarAlarma()` y `detenerAlarmaActual()` | Inician y detienen la alarma en curso. |
| `actualizarMusica()` y `actualizarReleRitmico()` | Actualizan la reproducción de tonos y el control de vibración. |
| `actualizarBotonDetener()` | Lee el pulsador configurado para detener la alarma y filtra rebotes. |
| `iniciarPruebaOLED()` y `actualizarPruebaOLED()` | Preparan la pantalla y actualizan la animación de la alarma. |

## Comunicación con la interfaz web

El teléfono se conecta a la red del ESP32 y utiliza la dirección local `http://4.3.2.1`. El portal cautivo intenta abrir la página automáticamente; también se puede ingresar la dirección en el navegador.

| Ruta | Método | Función |
| --- | --- | --- |
| `/api/sync-time` | POST | Envía la hora y el desfase horario del teléfono. |
| `/api/alarms` | GET | Entrega las alarmas configuradas. |
| `/api/save` | POST | Crea o modifica una alarma. |
| `/api/toggle` | POST | Activa o desactiva una alarma. |
| `/api/delete` | POST | Elimina una alarma. |
| `/api/stop` | POST | Detiene la alarma en curso. |
| `/api/status` | GET | Entrega el estado de sincronización, la hora y el estado de la alarma. |

La página consulta el estado periódicamente y muestra información como la hora sincronizada y el último evento. La memoria persistente conserva la configuración de las alarmas; en el código final no se implementa un registro histórico de mediciones ambientales.

## Pantalla y salidas

La pantalla está configurada por I²C en los pines D21 y D22. Durante una alarma, el programa selecciona una animación según la melodía; en Quantum Bell representa la hora configurada para esa alarma.

El buzzer se controla desde D18 y la señal del relé desde D15. El programa limita la frecuencia de conmutación del relé y permite interrumpir la salida al detener la alarma. El pulsador definido en D27 se lee con `INPUT_PULLUP` y un filtro de rebote de 35 ms.

La instalación y el uso desde el teléfono se explican en [Software](../README.md). Las versiones de las dependencias están en [Librerías](../librerias/README.md).
