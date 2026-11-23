# Lista de materiales (BOM)

Inventario técnico del sistema de alarma con ESP32, incluidos los componentes previstos para el encapsulado. Los costos de compra se incorporan cuando se disponga de boletas, comprobantes o cotizaciones.

**Archivo editable:** [BOM completo en CSV](bom_completo.csv), compatible con Excel y Google Sheets.

## Materiales

| Componente | Cantidad | Especificación | Estado |
|---|---|---|---|
| ESP32 DevKit V1 | 1 unidad | 30 pines, Micro-USB, Wi-Fi y Bluetooth | Identificado |
| Pantalla OLED | 1 unidad | 1,3 pulgadas, interfaz I²C, cuatro pines | Identificado |
| Buzzer pasivo | 1 unidad | Dos terminales, reproducción de melodías | Identificado |
| Módulo relé | 1 unidad | Un canal, Songle SRD-05VDC-SL-C, 5 V | Identificado |
| Motores vibratorios DC | 2 unidades | 1,5–6 V, 3500 RPM según anuncio comercial | Identificado |
| Módulo portabaterías | 1 unidad | Tipo power bank, alojamiento doble 18650 | Identificado |
| Baterías Li-ion | 2 unidades | 3,7 V nominales, formato 18650 probable | Identificado |
| Pulsadores | 2 unidades | Táctiles con tapa azul y blanca | Identificado |
| Protoboards compactas | 2 unidades | 400 puntos cada una, 83,5 × 54,5 × 8,5 mm | Cambio previsto |
| Cables jumper/Dupont | 1 lote básico | Juego surtido para prototipado | Identificado |
| Filamento PLA | Según impresión | Material para el encapsulado 3D | Por dimensionar |

## Presupuesto

El archivo CSV incluye columnas de **proveedor, precio unitario y subtotal**, disponibles para completar con importes comprobables. No se asignaron precios hipotéticos como si fueran gastos del equipo.

La referencia comercial disponible para **dos motores vibratorios** es **$2.540 CLP por el par**; constituye un precio anunciado, no una compra acreditada.

**Cables:** se registra **1 lote básico** de cables jumper/Dupont, en lugar de contar los conductores individuales.

**Encapsulado:** el PLA se registra como material de impresión; el consumo exacto en gramos depende del diseño definitivo y del laminado.

Para cerrar el costo total del prototipo se requieren los valores efectivos de los componentes y la cantidad de PLA consumida. El monto total no puede calcularse todavía sin esos datos.

## Referencias del proyecto

- [Fichas de componentes](../componentes.md).
- [Fotografías del montaje](../fotos/README.md).
- [Modelo del encapsulado](../../diseno_3d/README.md).

Los elementos de fijación integrados en la impresión forman parte del PLA; cualquier tornillo o accesorio independiente se incorporará si se utiliza en el montaje definitivo.
