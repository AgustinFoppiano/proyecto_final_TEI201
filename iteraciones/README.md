# Evolución e iteraciones del prototipo

Esta carpeta documenta las decisiones y modificaciones del proyecto de **alarma para personas sordas o con dificultades auditivas**. Una **iteración** es un cambio de diseño o funcionamiento entre versiones; un **registro de eventos** es evidencia de las activaciones durante las pruebas. Ambos son complementarios, pero no equivalentes.

## Etapas documentadas

| Etapa | Situación observada | Cambio o decisión registrada | Evidencia |
| --- | --- | --- | --- |
| [Iteración 1](iteracion_1/README.md) | Primera prueba con ESP32, buzzer y vibración inicial poco intensa; cables que podían desconectarse; detención dependiente del teléfono. | Buscar motores más adecuados, mejorar fijaciones y añadir control físico. | Fotografías y notas de la iteración 1. |
| [Iteración 2](iteracion_2/README.md) | Se incorporaron dos motores de vibración y controles físicos. Se reportó calentamiento anormal del portapilas. | Mejorar vibración y autonomía de uso; reemplazar el módulo de alimentación defectuoso y revisar seguridad. | Fotografías, anotaciones y [videos del portapilas](../testing/evidencias/README.md). |
| [Iteración 3](iteracion_3/README.md) | Se desarrolló la versión 4.1 del firmware y después una revisión con historial local de activaciones. | Integrar y documentar modos, pantalla, parada física/web, historial persistente y CSV. | [Ficha funcional del 21/11](../testing/datos/Ficha_pruebas_alarma.pdf) y [32 activaciones del 22/11](../testing/datos/analisis_historial_2026-11-22.md). |

La fecha concreta de cada cambio de diseño anterior debe cotejarse con el historial de versiones del equipo; no se asignan fechas ni métricas comparativas no verificadas.

## Resultados comparables que sí están documentados

- En la primera iteración se identificó **vibración insuficiente** del sistema inicial. No se midió instrumentalmente su intensidad.
- En la segunda se introdujeron **dos motores** y botones, y se observó una falla de calentamiento en el portapilas. No consta una medición comparativa de consumo ni aceleración de vibración.
- En pruebas funcionales del **21/11/2026**, se documentaron **10 pruebas** distribuidas en los tres modos (3 vibración, 3 sonido, 4 combinadas), según [ficha de pruebas](../testing/datos/Ficha_pruebas_alarma.pdf).
- En el **registro del 22/11/2026**, aparecen **32 activaciones**, **29 detenciones registradas** y **3 registros incompletos**. Esto documenta el uso del sistema de registro, no equivale a 32 pruebas de despertar satisfactorias.

No se incluyen cifras de latencia de activación, consumo en mA, tasa de errores hardware ni satisfacción de usuarios sin una fuente experimental que las respalde.

## Versiones de software

- [Código de la versión previamente documentada](../software/src/alarma_final/alarma_final.ino).
- [Revisiones 4.1 con historial y CSV](../software/src/prototipo_4_1_revisiones/README.md), reconstruibles desde el código base mediante una diferencia verificada.
- [Otras versiones conservadas](../software/versiones_anteriores/).

## Próximas validaciones de diseño

1. Probar la alimentación nueva y documentar voltaje, seguridad y continuidad sin cortocircuitos.
2. Repetir la prueba de historial después de un reinicio controlado y un corte de energía intencional, con observación externa.
3. Verificar que el encapsulado pueda abrirse para reparación y que aloje todos los componentes.
4. Medir vibración o validar con usuarios del grupo objetivo antes de afirmar eficacia para despertar durante el sueño.
5. Revisar que el esquema, montaje físico y versión de código presentados coincidan.

Las evidencias del registro y el [protocolo de validación](../testing/protocolo_registro_eventos.md) se encuentran en **testing/**.
