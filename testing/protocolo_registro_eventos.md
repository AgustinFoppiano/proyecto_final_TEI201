# Protocolo de verificación del registro de eventos

## Objetivo

Comprobar que la alarma programada desde la red Wi-Fi creada por el ESP32 **registra las activaciones**, identifica su modo, almacena el evento en memoria local, muestra la información en el panel de historial y permite exportar un CSV; al detenerla, verificar la fecha, duración y origen del cierre.

## Evidencia existente

- [Historial real del 22/11/2026](datos/historial_alarmas_2026-11-22.csv): 32 activaciones, 29 detenciones registradas y 3 sin cierre registrado.
- [Análisis reproducible del historial](datos/analisis_historial_2026-11-22.md).
- [Ficha de las diez pruebas funcionales del 21/11/2026](datos/Ficha_pruebas_alarma.pdf): evidencia distinta de sonido, vibración y animaciones.
- [Videos del prototipo](evidencias/README.md).

## Condiciones y variables

**Montaje:** ESP32, dos motores de vibración con relé, buzzer, pantalla OLED, botón físico, alimentación USB o módulo de baterías según la prueba. **Reloj:** sincronizado desde el teléfono al abrir la interfaz. **Modos:** sonido; vibración; sonido + vibración. **Formas de detener:** botón físico o botón web. **Variables del CSV:** ID, activación, hora programada, melodía, modo, detención, duración, origen y estado.

El CSV suministrado no contiene una columna con lugar, estado de la alimentación ni nombre del operador; por ello no se atribuyen entornos, responsables ni condiciones concretas a cada fila.

## Procedimiento propuesto para repetir y verificar

1. Encender la alarma, conectar el teléfono a su red Wi-Fi y sincronizar la hora.
2. Comprobar el contador actual en **Historial de alarmas** y conservar una captura inicial.
3. Programar una alarma próxima; anotar hora, modo y melodía elegidos.
4. Verificar por observación si se activa el comportamiento esperado (sonido, vibración y OLED).
5. Detener mediante el **botón físico** y consultar en el historial el registro de inicio, cierre, origen y duración.
6. Repetir una prueba equivalente con el **botón de la página web**.
7. Repetir los tres modos y exportar CSV; comparar el archivo con la tabla.
8. Reiniciar el ESP32 de forma controlada, volver a sincronizar hora y comprobar si se conservan los registros anteriores.
9. En una prueba **separada y controlada**, interrumpir la alimentación mientras la alarma está activa. Registrar **manualmente** esa intervención y observar si, tras reiniciar, se conserva un inicio sin cierre.
10. Registrar cualquier error de guardado, anomalía, tiempo y evidencia fotográfica o de pantalla.

**Precaución:** la prueba 9 debe hacerse sin manipular terminales de las baterías de litio ni provocar cortocircuitos. Si un portabaterías se calienta, suspender su uso hasta verificar su seguridad.

## Criterios de aceptación propuestos

- Cada activación observada crea un registro nuevo con modo y hora correctos.
- Al detener con alimentación estable, el mismo registro obtiene fecha de detención y origen correcto.
- El CSV exportado coincide con el panel y los registros sobreviven al reinicio normal.
- La ausencia de cierre tras un corte eléctrico se documenta como **limitación del sistema de registro**, no como una medición de la causa del corte.

Estos criterios **son un protocolo propuesto**, no deben confundirse con resultados ya ejecutados. La evidencia del 22/11/2026 prueba que existe un histórico real, pero no valida por sí sola todos los pasos de este procedimiento.

## Análisis de fallas y mejora

**Falla o limitación observada en los datos:** tres registros carecen de cierre. **Contexto reportado:** en ciertas pruebas se desconectaba la alimentación del ESP32. **Causa por confirmar:** interrupción antes de que la ESP32 pudiera registrar un cierre. **Mejora posible:** continuidad eléctrica más confiable, prueba de recuperación tras reinicio y anotación externa de cortes de energía.

**Conexión con el problema original:** la alarmas para personas sordas o con dificultades auditivas debe poder activarse en el modo configurado y detenerse de forma accesible. Un historial trazable ayuda a comprobar activaciones, detectar registros incompletos y decidir dónde mejorar confiabilidad y controles.
