# Funcionamiento del software

El programa de la [versión 4.1 revisiones](../src/prototipo_4_1_revisiones/prototipo_4_1_revisiones.ino) reúne la interfaz web, la lógica de alarmas, las animaciones y el registro de eventos.

## Secuencia de funcionamiento

1. El ESP32 inicia las salidas, recupera las alarmas guardadas y crea su red Wi-Fi.
2. Un teléfono conectado abre la página y sincroniza la hora del dispositivo.
3. La persona configura una alarma, seleccionando hora, melodía, modo y repetición.
4. El programa guarda la configuración y comprueba cuándo corresponde activar la alarma.
5. La alarma activa el modo seleccionado y su animación. El pulsador azul o la página permiten detenerla.
6. El historial guarda la activación y su detención y los presenta en la página.

## Funciones principales

| Función o grupo | Responsabilidad |
| --- | --- |
| `crearRedWifi()` | Configura la red Wi-Fi local del ESP32. |
| `configurarServidor()` | Define las rutas que usa la interfaz. |
| `guardarAlarmasEnMemoria()` y `cargarAlarmasDeMemoria()` | Guardan y recuperan la configuración de alarmas con `Preferences`. |
| `obtenerHoraLocal()` y `comprobarAlarmas()` | Calculan la hora sincronizada y revisan las alarmas. |
| `iniciarAlarma()` y `detenerAlarmaActual()` | Inician y detienen la alarma activa. |
| `actualizarMusica()` y `actualizarReleRitmico()` | Controlan la reproducción y la salida del relé. |
| `actualizarBotonDetener()` | Lee el pulsador y filtra rebotes. |
| `histNotificarInicio()` y `histNotificarFin()` | Preparan los eventos del historial. |
| `histProcesarEvento()` | Actualiza y guarda los registros de inicio y detención. |

## Interfaz e historial

La página se abre en `http://4.3.2.1` mientras el teléfono está conectado a la red del ESP32. Las rutas `/api/alarms`, `/api/save`, `/api/toggle`, `/api/delete`, `/api/stop` y `/api/status` permiten consultar y controlar las alarmas; `/api/sync-time` sincroniza la hora. La ruta `GET /api/historial` entrega los eventos al panel.

El historial conserva hasta 32 activaciones en una zona de memoria separada de las configuraciones. La interfaz presenta la tabla, el estado de la alarma y un gráfico por modo; también permite descargar un CSV. El registro describe eventos y tiempos hasta la detención de la alarma.

Los pines se detallan en [conexiones configuradas](../../hardware/esquemas/README.md), y la instalación en la [guía de software](../README.md).
