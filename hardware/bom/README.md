# Presupuesto de materiales — alarma accesible

Para estimar el costo de fabricación se presenta una selección de precios de referencia de proveedores nacionales e internacionales. Las cantidades corresponden a los materiales considerados para una alarma.

**Criterio del cálculo:** se multiplican precios unitarios de referencia por las cantidades consideradas para **una alarma**. Algunos precios corresponden a tramos de compra por volumen diferentes entre proveedores; el valor de los motores se prorratea desde un paquete comercial y el PLA se calcula con un supuesto de consumo de 150 g. La estimación permite comparar escenarios de producción y está sujeta a cotizaciones y cantidades efectivas.

**Tipo de cambio de referencia:** US$1 = **$1.008,79 CLP** (dólar observado del Banco Central de Chile del 20-11-2026). [Fuente](https://www.bcentral.cl/es/web/banco-central/inicio/-/asset_publisher/Exzd7l9NC3Y6/content/dolar-observado). **Cifras aproximadas**, sin transporte, impuestos de importación, mano de obra, energía, mermas, embalaje ni certificaciones.

[Catálogo técnico](../componentes.md)

## Costo de un dispositivo

| Componente | Cantidad | Precio por unidad | Subtotal |
|:--|--:|--:|--:|
| ESP32 DevKit V1 | 1 | $2.623 | $2.623 |
| Pantalla OLED SH1106 | 1 | $1.513 | $1.513 |
| Buzzer pasivo | 1 | $30 | $30 |
| Módulo relé Songle 5 V | 1 | $999 | $999 |
| Motores vibratorios DC | 2 | $770 | $1.540 |
| Portabaterías doble 18650 | 1 | $1.775 | $1.775 |
| Baterías Li-ion 18650 | 2 | $958 | $1.916 |
| Pulsadores táctiles con tapa | 2 | $81 | $162 |
| Protoboards compactas 400 puntos | 2 | $525 | $1.050 |
| Cables Dupont/jumper | 1 | $827 | $827 |
| Cable USB-A a Micro-USB | 1 | $424 | $424 |
| PLA para la carcasa **(estimación: 150 g)** | 150 g | $13.890 / kg | $2.084 |
| **Costo estimado por alarma** | | | **$14.943** |

### Presupuesto total

- **Materiales electrónicos y conexiones:** $12.859 CLP
- **Encapsulado PLA (referencia de 150 g):** $2.084 CLP
- **Costo estimado de materiales:** **$14.943 CLP**.
- **Reserva orientativa para imprevistos (10 % de materiales):** $1.494 CLP.
- **Materiales más reserva:** $16.437 CLP.
- **Ganancia orientativa (10 % del subtotal):** $1.644 CLP.
- **Precio de referencia calculado:** **$18.081 CLP por alarma**.

El cálculo aplica dos incrementos consecutivos, con redondeo a pesos. La reserva del 10 % es una hipótesis para comparar costos; el precio debe ajustarse con transporte, importación, impuestos aplicables, mano de obra, embalaje, mermas y otros costos de comercialización.

### Desglose por categoría

- **Microcontrolador:** $2.623 CLP
- **Sensores:** $0 CLP (este montaje no emplea sensores independientes)
- **Actuadores (buzzer, relé y motores):** $2.569 CLP
- **Estructura / encapsulado PLA:** $2.084 CLP (supuesto de 150 g)
- **Otros (OLED, energía, interfaz y montaje):** $7.667 CLP

## Referencias comerciales por componente

Las imágenes se presentan junto a cada referencia de adquisición. Los precios están redondeados a pesos chilenos.

### 1. ESP32 DevKit V1

<img src="https://down-br.img.susercontent.com/file/0f56f525b3dcd75991c5072f15fe04ed" alt="Imagen comercial de ESP32 DevKit V1" width="205">

*Imagen de referencia: 30 pines · Micro-USB.*

**$2.623 CLP por unidad** · *Al por mayor*

**Cantidad por alarma:** 1 · **Subtotal:** **$2.623 CLP**

**Proveedor:** KUONGSHUN · Alibaba · [Ver compra o cotización](https://www.alibaba.com/product-detail/ESP-WROOM-32-WiFi-and-BLE_1600518241183.html).

DevKit V1, 30 pines; confirmar chip USB-serial y variante antes de comprar.

### 2. Pantalla OLED SH1106

<img src="https://kuongshun.com/cdn/shop/products/AA142.jpg?v=1557283862" alt="Imagen comercial de Pantalla OLED SH1106" width="205">

*Imagen de referencia: 1,3 pulgadas · I²C · 128×64 · 4 pines.*

**$1.513 CLP por unidad** · *Al por mayor*

**Cantidad por alarma:** 1 · **Subtotal:** **$1.513 CLP**

**Proveedor:** Reaper · Made-in-China · [Ver compra o cotización](https://reaper88.en.made-in-china.com/product/LAsRNucKHxph/China-1-3-Inch-OLED-Screen-128-64-Iic-Interface-Sh1106-White-Blue-1-3inch-OLED-Display-Module.html).

La referencia de $1.513 utiliza US$1,50 y el tipo de cambio indicado arriba. Una versión de la publicación mostraba ese precio para pedidos desde 10.000 unidades; la disponibilidad y el tramo deben consultarse al proveedor.

### 3. Buzzer pasivo

<img src="https://cdn11.bigcommerce.com/s-yo2n39m6g3/products/361/images/6316/146-2__77705.1632222872.500.750.jpg?c=2" alt="Imagen comercial de Buzzer pasivo" width="205">

*Imagen de referencia: Dos terminales · 12085/OKY0152.*

**$30 CLP por unidad** · *Al por mayor*

**Cantidad por alarma:** 1 · **Subtotal:** **$30 CLP**

**Proveedor:** Okystar · Alibaba · [Ver compra o cotización](https://www.alibaba.com/pla/OKY0152-Passive-Buzzer-Ac-12085-16r_1600975018432.html?biz=pla&mark=google_shopping&pcy=fr_en&product_id=1600975018432&searchText=acoustic+components+old).

Verificar excitación y tensión; la referencia de compra puede diferir del cuerpo del buzzer fotografiado.

### 4. Módulo relé Songle 5 V

<img src="https://i.ebayimg.com/images/g/mY0AAOSwu1BeWNhC/s-l1200.jpg" alt="Imagen comercial de Módulo relé Songle 5 V" width="205">

*Imagen de referencia: Un canal · SRD-05VDC-SL-C.*

**$999 CLP por unidad** · *Al por mayor*

**Cantidad por alarma:** 1 · **Subtotal:** **$999 CLP**

**Proveedor:** Proveedor Alibaba · [Ver compra o cotización](https://www.alibaba.com/product-introduction/1-Channel-Relay-Module-5V-Shield_60260447788.html).

Relé de bobina 5 V; confirmar disparo con GPIO a 3,3 V y disposición de terminales.

### 5. Motores vibratorios DC

<img src="https://i5.walmartimages.com/seo/TOP-2Pcs-Mini-Vibration-Motor-3500RPM-DC-1-5-6V-for-Game-Joystick_6e9547a2-c73b-44eb-8b14-1e659615ad58.8965323fe4bbd35abeb9666b5dfaa8cd.jpeg" alt="Imagen comercial de Motores vibratorios DC" width="205">

*Imagen de referencia: 3500 RPM · 1,5–6 V · metálicos redondos.*

**$770 CLP por unidad** · *Paquete comercial (no mayorista)*

**Cantidad por alarma:** 2 · **Subtotal:** **$1.540 CLP**

**Proveedor:** Crystally / Mercado Libre Chile · [Ver compra o cotización](https://www.mercadolibre.cl/motor-de-vibracion-crystally-6-piezas-3500-rpm-15-6-v-par/p/MLC2049031929).

Precio unitario prorrateado de paquete de seis ($4.619); referencia por paquete, no tarifa mayorista confirmada.

### 6. Portabaterías doble 18650

<img src="https://www.icstation.com/images/uploads/18650%20Lithium%20Battery%20Expansion%20Board.jpg" alt="Imagen comercial de Portabaterías doble 18650" width="205">

*Imagen de referencia: Shield V8 · 2 celdas · USB.*

**$1.775 CLP por unidad** · *Referencia mayorista · modelo por validar*

**Cantidad por alarma:** 1 · **Subtotal:** **$1.775 CLP**

**Proveedor:** Proveedores Shield V8 · Alibaba · [Ver compra o cotización](https://www.alibaba.com/showroom/shield-esp32.html).

Modelo orientativo: puertos, circuito de carga, protección y pulsador deben coincidir con el portabaterías real antes de fabricar la carcasa.

### 7. Baterías Li-ion 18650

<img src="https://www.electronicscomp.com/image/cache/catalog/psss-power-3.7v-2600mah-3c-18650-icr-18-65-li-ion-rechargeable-cell-for-ebike-2-800x800.JPG" alt="Imagen comercial de Baterías Li-ion 18650" width="205">

*Imagen de referencia: 3,7 V · FST18650 · 2600 mAh anunciado.*

**$958 CLP por unidad** · *Al por mayor*

**Cantidad por alarma:** 2 · **Subtotal:** **$1.916 CLP**

**Proveedor:** Ating Power / FST · Alibaba · [Ver compra o cotización](https://wholesaler.alibaba.com/product-detail/KC-Certificated-18650-Rechargeable-Battery-3_60834240125.html).

Formato equivalente probable, no misma marca confirmada. Verificar protección, capacidad real, ensayos y documentación de transporte.

### 8. Pulsadores táctiles con tapa

<img src="https://i.ebayimg.com/images/g/AWcAAeSwKhdopIT1/s-l1200.jpg" alt="Imagen comercial de Pulsadores táctiles con tapa" width="205">

<img src="https://laelectronica.com.gt/image/cache/catalog/Productos/Switches%20Y%20PushButtons/Push%20Buttons/push12mmblanco-1200x1200.jpg" alt="Otra vista de pulsador táctil" width="160">

*Imagen de referencia: 12×12 mm · 4 patas · tapas azul y blanca.*

**$81 CLP por unidad** · *Al por mayor*

**Cantidad por alarma:** 2 · **Subtotal:** **$162 CLP**

**Proveedor:** Proveedores de botones + tapas · Alibaba · [Ver compra o cotización](https://www.alibaba.com/product-introduction/4-Pin-Micro-PCB-Momentary-Dip_1600945281075.html) · [Ver tapas](https://www.alibaba.com/product-introduction/Wholesale-Push-Button-Caps-to-on_1600978695439.html).

US$0,07 por pulsador más US$0,01 por tapa. Confirmar compatibilidad y altura física.

### 9. Protoboards compactas 400 puntos

<img src="https://thepihut.com/cdn/shop/files/half-size-breadboard-white-the-pi-hut-100058-42740225540291.jpg?crop=center&amp;height=1200&amp;v=1724830868&amp;width=1200" alt="Imagen comercial de Protoboards compactas 400 puntos" width="205">

*Imagen de referencia: BB-801 · 400 contactos por placa.*

**$525 CLP por unidad** · *Al por mayor*

**Cantidad por alarma:** 2 · **Subtotal:** **$1.050 CLP**

**Proveedor:** Proveedor BB-801 · Alibaba · [Ver compra o cotización](https://www.alibaba.com/product-introduction/400-Ties-Mini-Solderless-Breadboard-Universal_1600900235173.html).

Son dos placas por alarma. Confirmar medida 83,5×54,5×8,5 mm y contactos al recibir.

### 10. Cables Dupont/jumper

<img src="https://img.eclife.com.tw/photo2011/prod_2016/5/G3020046-A.jpg" alt="Imagen comercial de Cables Dupont/jumper" width="205">

*Imagen de referencia: Lote básico de cables 120 piezas.*

**$827 CLP por unidad** · *Referencia de lote mayorista*

**Cantidad por alarma:** 1 · **Subtotal:** **$827 CLP**

**Proveedor:** Inventor Electronic · Alibaba · [Ver compra o cotización](https://www.alibaba.com/wholesale/electronic-dupont.html).

Se presupuesta un lote básico completo por prototipo; para fabricación en serie puede optimizarse.

### 11. Cable USB-A a Micro-USB

<img src="https://m.media-amazon.com/images/I/61X8GG0JdfL._AC_SL1500_.jpg" alt="Imagen comercial de Cable USB-A a Micro-USB" width="205">

*Imagen de referencia: Cable corto de alimentación.*

**$424 CLP por unidad** · *Referencia mayorista · enlace a catálogo*

**Cantidad por alarma:** 1 · **Subtotal:** **$424 CLP**

**Proveedor:** Proveedores de cables · Alibaba · [Ver compra o cotización](https://www.alibaba.com/wholesale/micro-usb-to-usb-2.0.html).

Referencia de cable; verificar longitud y orientación para alojarlo en la carcasa.

### 12. PLA para el encapsulado

**$13.890 CLP/kg** · *Referencia de compra local*. 

Para este presupuesto se han considerado **150 g** de filamento por carcasa: **$2.084 CLP**. **El peso no es una medición**: deberá sustituirse por los gramos del laminador de impresión cuando el diseño final esté listo. Compatible como tipo de material con la Ender 3 V3 del equipo.

**Proveedor:** TodoToner, Chile · [Ver filamento PLA Creality](https://www.todotoner.cl/impresoras/impresoras-3d/filamentos/pla-1kg-blanco).

---

**Pendiente para presupuesto industrial definitivo:** comprobación del portabaterías exacto y su seguridad, ficha de motores, configuración de contactos/botones, masa final del PLA, costos de ensamblaje, merma, transporte y empaque. Los precios que se muestran son **referencias de publicaciones**, no cotizaciones aceptadas o compras ya efectuadas.

[Volver a hardware](../README.md) · [Fotos del prototipo](../fotos/README.md)
