# Iteración 3 — Integración y registro de la alarma

**Etapa:** preparación del Avance #3 de TEI201.  
**Firmware documentado:** versión 4.1 y archivo **4.1 revisiones** con historial.  
**Evidencia fechada:** 21 y 22 de noviembre de 2026.

## Objetivo de la etapa

Integrar el control mediante Wi-Fi local, las modalidades de vibración y sonido, pantalla OLED, apagado físico o desde la interfaz, y una forma de conservar evidencia de las activaciones del dispositivo.

## Hardware y montaje

El proyecto emplea ESP32, pantalla OLED, buzzer, módulo relé, dos motores vibratorios, botones y alimentación mediante portabaterías. Se documentaron fotografías reales desde diferentes ángulos en [hardware/fotos](../../hardware/fotos/README.md). La [lista de componentes](../../hardware/componentes.md) y la [BOM](../../hardware/bom/README.md) describen el conjunto.

**Mejora respecto a etapas anteriores:** integración de controles de detención y sustitución del sistema vibratorio inicialmente considerado débil. La seguridad del nuevo sistema de alimentación y la fijación final deben verificarse en el montaje físico; no se afirma que estén validadas solo por existir el diseño.

## Evolución del firmware

El archivo principal conservado en el repositorio corresponde a [alarma_final.ino](../../software/src/alarma_final/alarma_final.ino). El equipo entregó posteriormente un archivo denominado **prototipo_4_1_revisiones.ino** que, además de las funciones de alarma, introduce:

- Registro de los eventos de **inicio** y **detención** de cada alarma.
- Distinción entre detención por **botón físico** y **página web**.
- Almacenamiento local mediante `Preferences` en la memoria no volátil del ESP32, con un máximo de **32 activaciones**.
- Consulta en `/api/historial`, panel web con tabla y barras por modo, y exportación CSV.
- Gestión de eventos con cola y verificaciones de integridad en la persistencia.

La revisión del firmware se encuentra en [prototipo_4_1_revisiones.ino](../../software/src/prototipo_4_1_revisiones/prototipo_4_1_revisiones.ino), junto con su [guía y respaldo reproducible](../../software/src/prototipo_4_1_revisiones/README.md).

## Pruebas y resultados

**21/11/2026 — funcionamiento:** se documentaron **10 pruebas** con tres modos y diferentes melodías, con resultados registrados en [Ficha_pruebas_alarma.pdf](../../testing/datos/Ficha_pruebas_alarma.pdf). También se documentó la percepción de vibración al sostener los motores con las manos.

**22/11/2026 — registro histórico:** el CSV contiene **32 activaciones**: 14 en sonido + vibración, 10 en vibración y 8 en sonido. Se registraron **29 detenciones** (19 por botón físico, 10 por web); **3 entradas** carecen de detención registrada. El tiempo medio hasta la detención registrada, solo entre los 29 casos cerrados, fue **9,1 s**. Ver [análisis de resultados](../../testing/datos/analisis_historial_2026-11-22.md).

El equipo informó interrupciones de energía durante algunas pruebas. Sin alimentación, la ESP32 no puede registrar un evento final. **El CSV no permite asignar una causa definitiva a cada entrada incompleta**, por lo que no se presenta esto como una falla confirmada de vibración ni como un apagado detectado automáticamente.

## Documentos vinculados

- [Código y reconstrucción del firmware con historial](../../software/src/prototipo_4_1_revisiones/README.md).
- [Datos originales y análisis del 22/11](../../testing/datos/analisis_historial_2026-11-22.md).
- [Protocolo de registro propuesto](../../testing/protocolo_registro_eventos.md).
- [Resultados previos y reporte de dificultades](../../testing/reportes/README.md).
- [Modelo y planos existentes](../../diseno_3d/README.md).
