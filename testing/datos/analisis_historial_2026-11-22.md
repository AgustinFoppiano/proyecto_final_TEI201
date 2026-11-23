# Análisis del historial de alarmas — 22 de noviembre de 2026

## Evidencia y alcance

Fuente primaria: [historial exportado por el dispositivo](historial_alarmas_2026-11-22.csv), obtenido de la interfaz web de la versión **4.1 revisiones** del firmware. Es un registro de **eventos de activación**, no un muestreo ambiental continuo ni una encuesta a usuarios. La fecha y las horas son las que declara la interfaz, que sincroniza el reloj del ESP32 desde el teléfono.

Se analizan **32 activaciones**, registradas entre **14:56:00 y 17:00:00** del 22/11/2026. Los identificadores van del 1 al 32. Los registros están en orden descendente de ID en el CSV.

## Resultados cuantitativos

| Indicador | Resultado |
| --- | ---: |
| Activaciones en el historial | **32** |
| Activaciones con detención registrada | **29** |
| Activaciones sin detención registrada | **3** |
| Proporción con detención registrada | **90,6 %** (29/32) |
| Detenciones mediante botón físico | **19** |
| Detenciones desde la página web | **10** |
| Tiempo medio de activación a detención, entre registros cerrados | **9,1 s** |
| Mediana del tiempo de activación a detención | **7 s** |
| Tiempo mínimo / máximo, entre registros cerrados | **1 s / 42 s** |

### Activaciones por modo

| Modo | Activaciones | Con detención registrada | Sin detención registrada |
| --- | ---: | ---: | ---: |
| Sonido + vibración | 14 | 13 | 1 |
| Solo vibración | 10 | 8 | 2 |
| Solo sonido | 8 | 8 | 0 |
| **Total** | **32** | **29** | **3** |

### Medio de detención de las 29 activaciones cerradas

- Botón físico: **19** (65,5 % de las detenciones registradas).
- Página web: **10** (34,5 % de las detenciones registradas).

### Casos que requieren explicación

| ID | Activación | Modo | Evidencia |
| --- | --- | --- | --- |
| 9 | 22/11/2026 15:04 | Vibración | Sin detención registrada |
| 10 | 22/11/2026 15:05 | Sonido + vibración | Sin detención registrada |
| 12 | 22/11/2026 15:07 | Vibración | Sin detención registrada |

**Interpretación:** el historial demuestra que se registraron activaciones en los tres modos y que se puede distinguir el medio de detención cuando el evento de cierre se guardó. No demuestra por sí mismo que el sonido y la vibración se hayan ejecutado correctamente en cada una de las 32 activaciones; para ello se utiliza también la [ficha de pruebas funcionales del 21/11](Ficha_pruebas_alarma.pdf).

La integrante que realizó el registro informa que en las pruebas con corte de alimentación —por desconexión del ordenador o de las baterías— el dispositivo dejó de funcionar, pero **no pudo guardar la forma de detención**. Los tres registros sin cierre son **compatibles** con esa situación. El archivo no permite confirmar la causa individual de cada caso: podrían intervenir pérdida de energía u otros problemas de registro. No deben clasificarse automáticamente como tres alarmas que no se detuvieron, ni como tres desconexiones eléctricas demostradas.

**Importante:** los 9,1 segundos miden el intervalo entre activación y detención registrada; no son latencia de activación, precisión del reloj, tiempo real de despertar ni un indicador de eficacia para personas con discapacidad auditiva.

## Qué información aporta al problema del proyecto

- **Verifica trazabilidad de activaciones:** permite revisar a qué hora se activó una alarma y bajo qué modo.
- **Permite investigar interrupciones:** los registros abiertos señalan sesiones que necesitan revisión.
- **Permite observar el uso de controles:** diferencia el botón físico del apagado por la página web.
- **Apoya decisiones de mejora:** justificar pruebas de continuidad de alimentación, retención tras reinicio, integridad de conexiones y reducción de registros incompletos.

## Funcionamiento del registro en el firmware

El archivo de revisiones implementa un historial local en la memoria no volátil del ESP32 (NVS, mediante `Preferences`, espacio `hist_alarma`): hasta **32 registros**, conservando los más recientes cuando se ocupa el límite. Se registra un evento de inicio y, cuando existe, otro de detención con el origen y la duración. Las escrituras se procesan mediante una cola para reducir interferencias con sonido y vibración; también se verifican lecturas y escrituras con un checksum. El endpoint `GET /api/historial` devuelve JSON a la página web, donde el panel muestra tabla y barras por modo, con recarga aproximada cada 4 segundos mientras está abierto. El botón **Descargar CSV** exporta la tabla.

No se guarda telemetría sobre el motivo físico de un corte de energía: si el ESP32 se queda sin alimentación antes de escribir el evento de cierre, este puede faltar.

## Limitaciones y siguiente prueba recomendada

1. **Misma fecha, sesión concentrada:** no constituye validación de autonomía durante varias noches.
2. **Sin identificación de lugar por fila:** aunque se hayan ensayado entornos diferentes, el CSV no permite contrastarlos.
3. **Sin medida de respuesta del usuario dormido:** se puede comprobar funcionamiento técnico, no eficacia clínica o de despertar.
4. **Sin causalidad para registros incompletos:** repetir ensayos de corte de energía y de reinicio y anotar externamente el motivo real.
5. **Capacidad local limitada:** con más de 32 activaciones, las antiguas se reemplazan; exportar periódicamente.
6. **Prueba de persistencia pendiente de documentar:** comparar el historial antes y después de un reinicio controlado y verificar que los IDs esperados siguen presentes.
7. **El registro es por eventos:** para cumplir de forma convincente el requisito de captura continua de la pauta, justificar formalmente que el fenómeno medido son las activaciones y su cierre; no describirlo como medición de un sensor ambiental.

Este análisis se calculó exclusivamente a partir del CSV facilitado. No se inventaron lecturas, mediciones instrumentales ni resultados de usuarios.
