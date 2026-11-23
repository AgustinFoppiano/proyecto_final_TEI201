# Hardware — documentación del prototipo

El prototipo corresponde a una alarma accesible para personas sordas o con dificultades auditivas que combina **vibración, sonido y una pantalla OLED** con control central por ESP32.

## Documentos principales

- **[Catálogo ilustrado de los componentes](componentes.md)**: identificación técnica, imágenes de referencia y fichas técnicas de cada pieza.
- **[Referencias fotográficas](imagenes_componentes/README.md)**: galería de imágenes de referencia.
- **[BOM y presupuesto comercial](bom/README.md)**: imágenes de referencia, proveedores por volumen, enlaces de compra, cantidades y cálculo del costo por alarma.
- **[Esquemas](esquemas/README.md)**: circuito a documentar.
- **[Fotografías reales](fotos/README.md)**: vistas del montaje y evidencia física.

## Componentes previstos y cantidades

1 ESP32 DevKit V1 de 30 pines; 1 OLED I²C de 1,3″; 1 buzzer pasivo; 1 módulo relé Songle SRD-05VDC-SL-C; 2 motores de vibración DC; 1 portabaterías para 2 celdas; 2 baterías Li-ion de 3,7 V; 2 pulsadores (azul y blanco); **2 protoboards compactas de 400 puntos**; **1 lote básico de cables jumper/Dupont**.

## Montaje: confirmado frente a previsto

- **Montaje fotografiado:** ESP32 y buzzer en protoboard de pruebas grande; OLED cableada; relé; dos motores; portabaterías y pulsadores. Corresponde a la fase provisional del prototipo.
- **Cambio previsto:** reemplazo de protoboards grandes por dos compactas **juntas** (83,5 × 54,5 × 8,5 mm por unidad, según ficha comercial).
- **Encapsulado en revisión:** dos mitades circulares, curvadas por ambas caras; OLED visible desde arriba; pulsadores protegidos en los costados; los dos motores en un mismo costado; portabaterías desmontable y guía para el conector de carga verificado.
- **Distribución propuesta:** ESP32 entre las dos protoboards, buzzer encima de una de ellas y relé próximo al buzzer. La posición prevista no equivale a una instalación física ya comprobada.

## Verificaciones críticas antes de presentar el ensamble como terminado

- [ ] Esquemático completo y actualizado, con tensión y corriente reales de cada módulo.
- [ ] Comprobar puerto de entrada de carga y tipo de conector del portabaterías.
- [ ] Confirmar dimensiones reales de las dos protoboards recibidas.
- [ ] Fijar cables y componentes para evitar desconexiones por vibración.
- [x] BOM con precios de referencia y cálculo unitario de materiales (estimación de producción).
- [ ] Sustituir referencias comerciales por cotizaciones confirmadas y validar el peso real de PLA.
- [ ] Fotografías del montaje **final** desde al menos tres ángulos.
- [ ] Verificar acceso a la electrónica y apertura del encapsulado sin dañarlo.
- [ ] Revisar las condiciones de temperatura y seguridad de las baterías; **no cargarlas bajo almohadas o ropa de cama**.

> **Nota:** este README no presenta como verificadas mediciones de consumo, peso o dimensiones finales del aparato que el equipo todavía no ha documentado.
