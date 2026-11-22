# Bill of Materials (BOM)

## Formato del Archivo

El archivo BOM debe incluir las siguientes columnas:

| Columna | Descripción | Ejemplo |
|---------|-------------|---------|
| Cantidad | Número de unidades | 1 |
| Componente | Nombre descriptivo | ESP32 DevKit V1 |
| Especificación | Detalles técnicos | 30 pines, WiFi+BT |
| Fabricante | Marca del componente | Espressif |
| Código/SKU | Identificador único | ESP32-WROOM-32 |
| Proveedor | Tienda/distribuidor | AliExpress, MercadoLibre |
| Precio Unitario | Costo por unidad (CLP) | $8,990 |
| Precio Total | Cantidad × Precio | $8,990 |
| Datasheet | Link a especificaciones | [URL] |



## Componentes utilizados

| Elemento | Especificación | Cantidad |
|---|---|---|
| ESP32 DevKit V1 | 30 pines, con conexión MicroUSB | 1 |
| Pantalla OLED | 1,3 pulgadas | 1 |
| Placa portabaterías | Tipo power bank, con dos baterías recargables Li-ion de 3,7 V y conexiones USB | 1 |
| Módulo de relé de un canal y 5 V | Relé Songle SRD-05VDC-SL-C | 1 |
| Motores redondos | 1,5 a 6 V y 3500 rpm | 2 |
| Botones | Pulsadores táctiles | 2 |

## Archivos a Incluir

- `bom_completo.xlsx` - Lista completa de materiales
- `bom_completo.pdf` - Versión PDF para visualización
- `datasheets/` - Carpeta con PDFs de componentes críticos

---

## Presupuesto Total

**Costo Total Estimado:** $[XXXXX] CLP

### Desglose por Categoría
- Microcontrolador: $X,XXX
- Sensores: $X,XXX
- Actuadores: $X,XXX
- Estructura/Encapsulado: $X,XXX
- Otros: $X,XXX
