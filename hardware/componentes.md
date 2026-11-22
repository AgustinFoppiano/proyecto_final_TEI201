# Catálogo ilustrado de componentes electrónicos

**Proyecto:** alarma accesible para personas sordas o con dificultades auditivas (TEI201, UAI).  
**Estado:** documentación técnica preliminar revisada el 22 de noviembre de 2026.  
**Criterio de evidencia:** fotografías reales y descripciones del equipo; los datos de fichas comerciales se distinguen de mediciones experimentales. Una característica no comprobada se marca como **pendiente de verificar**.

Las fotografías siguientes muestran **componentes comerciales reales visualmente similares**, enlazados a sus páginas de origen. Son **referencias para identificar el tipo de pieza**, no fotografías del montaje del equipo, ni pruebas del fabricante o las especificaciones exactas.

## 1. Microcontrolador ESP32 DevKit V1

<img src="https://down-br.img.susercontent.com/file/0f56f525b3dcd75991c5072f15fe04ed" alt="Fotografía de referencia de ESP32 DevKit V1 de 30 pines" width="260">

*Fotografía comercial de referencia ([Shopee Brasil](https://shopee.com.br/Placa-ESP32-WiFi-Bluetooth-DEVKit-V1-30-Pinos-i.277189279.10937160548)). No identifica necesariamente la unidad física del prototipo ni confirma sus especificaciones.*

- **Cantidad:** 1 unidad.
- **Identificación proporcionada:** ESP32 DevKit V1, 30 pines (dos hileras de 15), con Micro-USB.
- **Características de la familia ESP32:** Wi-Fi de 2,4 GHz (802.11 b/g/n), Bluetooth clásico y BLE según módulo, procesador de hasta 240 MHz en variantes ESP32-WROOM-32, periféricos GPIO, I²C, SPI, UART y PWM; **GPIO de lógica a 3,3 V**.
- **Elementos visibles de la placa:** puerto de programación/alimentación, regulador, pines y módulo con antena integrada.
- **Por confirmar en la unidad:** modelo exacto del módulo (WROOM-32 o variante), capacidad flash, chip USB-serie, dimensiones y consumo.
- **Función:** gestionar las alarmas, la interfaz web local, la pantalla, el buzzer, el relé y el botón de detención.
- **Justificación:** permite configurar el dispositivo desde un teléfono mediante Wi-Fi sin exigir un servidor externo para esa interfaz, y dispone de periféricos para los actuadores.
- **Referencia técnica:** [Espressif ESP32-WROOM-32](https://www.espressif.com/sites/default/files/documentation/esp32-wroom-32_datasheet_en.pdf).

## 2. Pantalla OLED I²C de 1,3 pulgadas

<img src="https://kuongshun.com/cdn/shop/products/AA142.jpg?v=1557283862" alt="Fotografía delantera y trasera de OLED I²C 1,3 pulgadas con ADD_SELECT" width="260">

*Fotografía comercial de referencia ([Kuongshun Electronic Shop](https://kuongshun.com/products/blue-i2c-iic-oled-lcd-module)). No identifica necesariamente la unidad física del prototipo ni confirma sus especificaciones.*

- **Cantidad:** 1 unidad.
- **Confirmado visualmente:** PCB azul marcada `1.3' OLED IIC`, cuatro pines rotulados `GND`, `VCC`, `SCL`, `SDA`, cuatro orificios de montaje y selector `ADD_SELECT`.
- **Dirección I²C indicada en la placa:** `0x78` o `0x7A` en notación de 8 bits; equivalen a `0x3C` y `0x3D` en direccionamiento de 7 bits.
- **Probable, no confirmado por número de parte:** resolución 128 × 64 píxeles, controlador SH1106, pantalla monocromática.
- **Por verificar:** tensión admitida por el módulo concreto, corriente, posición exacta de zona visible y distancias entre orificios.
- **Función:** mostrar la hora y animaciones asociadas a las melodías.
- **Justificación:** alto contraste y comunicación I²C con pocos conductores; permite inspeccionar información sin abrir la carcasa.
- **Ubicación prevista:** fijación detrás de la ventana superior del encapsulado; no apoyada suelta.
- **Referencia:** [LCDWiki, OLED IIC 1.3″](https://www.lcdwiki.com/1.3inch_IIC_OLED_Module_SKU%3AMC130GX).

## 3. Buzzer pasivo, sin módulo

<img src="https://cdn11.bigcommerce.com/s-yo2n39m6g3/products/361/images/6316/146-2__77705.1632222872.500.750.jpg?c=2" alt="Fotografía real de buzzer pasivo cilíndrico de dos terminales" width="260">

*Fotografía comercial de referencia ([Pixel Electric](https://www.pixelelectric.com/piezo-buzzers/buzzer-piezoelectric-passive/)). No identifica necesariamente la unidad física del prototipo ni confirma sus especificaciones.*

- **Cantidad:** 1 unidad.
- **Identificación proporcionada:** buzzer pasivo de dos terminales.
- **Principio de trabajo:** requiere señal periódica de excitación; permite variar las frecuencias y formar secuencias de tonos, a diferencia de un buzzer activo con tono fijo.
- **Por verificar:** tensión nominal, corriente, tecnología piezoeléctrica o electromagnética, diámetro, alto, resonancia e intensidad sonora.
- **Función:** avisos y melodías en modo sonido o modo combinado.
- **Justificación:** admite melodías configurables por software.
- **Ubicación prevista:** sobre una de las dos protoboards, próximo al relé.

## 4. Módulo de relé de un canal, 5 V

<img src="https://i.ebayimg.com/images/g/mY0AAOSwu1BeWNhC/s-l1200.jpg" alt="Fotografía del módulo de relé Songle SRD-05VDC-SL-C" width="260">

*Fotografía comercial de referencia ([Publicación de relé SRD-05VDC-SL-C en eBay](https://www.ebay.com/itm/174204872422)). No identifica necesariamente la unidad física del prototipo ni confirma sus especificaciones.*

- **Cantidad:** 1 unidad.
- **Confirmado por la inscripción fotografiada:** relé **Songle SRD-05VDC-SL-C**, bobina de **5 V CC**.
- **Módulo:** un canal, bornera con contactos **COM, NO y NC** y entrada de mando de tres conexiones.
- **Dato de la familia del relé:** contactos de conmutación hasta **10 A a 250 V CA / 10 A a 30 V CC** bajo condiciones nominales; **no describe la corriente de la bobina ni significa que deba utilizarse con esas cargas**.
- **Por verificar:** esquema interno del módulo, compatibilidad del control de 3,3 V del ESP32, consumo y alimentación reales, aislamiento, dimensiones y terminales.
- **Función:** conmutar la alimentación de los motores sin hacer pasar su corriente directamente por un pin GPIO del ESP32.
- **Justificación:** interfaz eléctrica de control para la carga; requiere comprobar que el conjunto es compatible con el voltaje de alimentación disponible.
- **Ubicación prevista:** próximo al buzzer, fijado mediante soporte desmontable.
- **Referencia:** [Songle SRD, documentación de la familia](https://www.songlerelay.com/).

## 5. Motores vibratorios DC

<img src="https://i5.walmartimages.com/seo/TOP-2Pcs-Mini-Vibration-Motor-3500RPM-DC-1-5-6V-for-Game-Joystick_6e9547a2-c73b-44eb-8b14-1e659615ad58.8965323fe4bbd35abeb9666b5dfaa8cd.jpeg" alt="Fotografía comercial de dos motores vibradores DC de 3500 RPM" width="260">

*Fotografía comercial de referencia ([Walmart (publicación de dos motores 1,5–6 V)](https://www.walmart.com/ip/16005762390)). No identifica necesariamente la unidad física del prototipo ni confirma sus especificaciones.*

- **Cantidad:** **2 unidades**.
- **Confirmado en fotos:** cuerpos metálicos cilíndricos y conductores rojo/negro.
- **Según la publicación comercial enviada:** rango de **1,5–6 V CC** y velocidad anunciada **3500 rpm**. Son características *publicadas por el vendedor*, no comprobadas instrumentalmente.
- **Principio:** un peso excéntrico gira y produce vibración.
- **Por verificar:** diámetro y grosor exactos, tensión nominal de operación elegida, corriente de arranque, consumo, frecuencia/intensidad real de vibración y fabricante.
- **Función:** señal táctil de alarma.
- **Justificación:** dos motores para aumentar la vibración respecto de versiones previas; **aún debe medirse su efectividad en condiciones reales**.
- **Disposición de diseño:** ambos en **el mismo costado** del encapsulado, sujetos con cunas y retenes que no bloqueen la excéntrica.
- **Precio de referencia de una publicación:** $2.540 CLP por **dos** motores ($1.270 por motor). **No es costo de compra verificado**.

## 6. Placa portabaterías tipo *power bank*

<img src="https://www.icstation.com/images/uploads/18650%20Lithium%20Battery%20Expansion%20Board.jpg" alt="Fotografía frontal y posterior de placa portabaterías doble 18650 con USB-C, Micro-USB y USB-A" width="260">

*Fotografía comercial de referencia ([ICStation](https://www.icstation.com/18650-lithium-battery-holder-mobile-power-expansion-board-p-15842.html)). No identifica necesariamente la unidad física del prototipo ni confirma sus especificaciones.*

- **Cantidad:** 1 unidad.
- **Observado en las fotografías:** placa negra para dos celdas cilíndricas, puerto USB-A, conectores de entrada de carga y electrónica de alimentación; hay vistas que muestran conectores USB-C y Micro-USB.
- **Funcionamiento informado por el equipo:** pulsación breve del botón externo blanco para mantener la alimentación encendida; pulsación prolongada para apagar el módulo.
- **Por verificar:** fabricante/modelo, cuáles puertos aceptan carga, tensión/corriente de salida, disposición interna de las celdas, tipo de protección y disipación térmica.
- **Función:** alimentar el dispositivo de forma portátil y permitir recargar las baterías.
- **Ubicación prevista:** alojamiento desmontable con conducto que guíe el cable hasta el **puerto que se confirme como entrada de carga**.
- **Precaución:** que la foto reciente muestre una boca USB-C no prueba por sí solo que ese sea el puerto habilitado para carga; comprobarlo con el módulo real antes de cerrar el diseño.

## 7. Baterías Li-ion

<img src="https://www.electronicscomp.com/image/cache/catalog/psss-power-3.7v-2600mah-3c-18650-icr-18-65-li-ion-rechargeable-cell-for-ebike-2-800x800.JPG" alt="Fotografía de dos celdas cilíndricas rojas Li-ion 18650 alineadas" width="260">

*Fotografía comercial de referencia ([ElectronicsComp (foto de referencia; marca/capacidad no identificadas en las celdas del prototipo)](https://www.electronicscomp.com/psss-power-3.7v-2600mah-3c-18650-icr-18-65-li-ion-rechargeable-cell-for-ebike)). No identifica necesariamente la unidad física del prototipo ni confirma sus especificaciones.*

- **Cantidad:** **2 unidades**.
- **Confirmado por el texto de sus envolturas:** química Li-ion, tensión nominal **3,7 V por celda**.
- **Formato probable:** 18650 (aproximadamente 18 mm de diámetro por 65 mm de longitud nominal; las celdas protegidas pueden ser más largas).
- **Tensión típica de carga completa:** alrededor de **4,2 V por celda**, siempre mediante un circuito cargador apropiado.
- **Por verificar:** capacidad real en mAh, fabricante, corriente máxima de descarga, protección eléctrica y estado físico.
- **Función:** almacenar energía.
- **Precaución:** **no asumir** conexión en serie/paralelo ni tensión final de salida sin verificar el circuito portabaterías. No cargar cubiertas por una almohada o ropa de cama.

## 8. Dos pulsadores táctiles: azul y blanco

<img src="https://i.ebayimg.com/images/g/AWcAAeSwKhdopIT1/s-l1200.jpg" alt="Fotografía de pulsadores táctiles de botón azul redondo" width="260">

<img src="https://laelectronica.com.gt/image/cache/catalog/Productos/Switches%20Y%20PushButtons/Push%20Buttons/push12mmblanco-1200x1200.jpg" alt="Fotografía real de pulsador blanco de cuatro terminales" width="260">

*Fotografías comerciales de referencia ([eBay (pulsador azul)](https://www.ebay.com/itm/396975102240) y [La Electrónica (pulsador blanco)](https://laelectronica.com.gt/pulsador-na-blanco)). No identifican necesariamente la unidad física del prototipo ni confirma sus especificaciones.*

- **Cantidad:** 2 unidades; tapas circulares azul y blanca.
- **Observado:** cuerpo negro con patas metálicas, compatibles visualmente con interruptores táctiles momentáneos de cuatro terminales.
- **Configuración probable:** contacto normalmente abierto (NO) mientras no se presiona; **por verificar** con multímetro y modelo exacto.
- **Por medir:** diámetro de tapa, alto de accionamiento, tamaño del cuerpo, carrera, fuerza y características eléctricas.
- **Botón azul:** detiene la alarma.
- **Botón blanco:** controla encendido y apagado sostenido por el **módulo portabaterías**, según explicación del equipo. El pulsador puede ser momentáneo aunque el módulo conserve el estado de encendido.
- **Montaje previsto:** laterales del encapsulado, protegidos contra pulsaciones accidentales.

## 9. Dos protoboards compactas de 400 puntos

<img src="https://thepihut.com/cdn/shop/files/half-size-breadboard-white-the-pi-hut-100058-42740225540291.jpg?crop=center&amp;height=1200&amp;v=1724830868&amp;width=1200" alt="Fotografía de protoboard compacta blanca de 400 puntos" width="260">

*Fotografía comercial de referencia ([The Pi Hut (fotografía de una unidad; el proyecto prevé dos)](https://thepihut.com/products/raspberry-pi-breadboard-half-size)). No identifica necesariamente la unidad física del prototipo ni confirma sus especificaciones.*

- **Cantidad final prevista:** **2 unidades** (reemplazan la protoboard grande provisional fotografiada).
- **Ficha comercial proporcionada:** **400 puntos por placa**, con **300 de conexión** y **100 de alimentación**. En total, **800 puntos** entre ambas.
- **Dimensiones anunciadas por placa:** **83,5 × 54,5 × 8,5 mm**.
- **Paso de contactos:** **2,54 mm** (0,1″).
- **Materiales según proveedor:** cuerpo ABS y contactos de bronce fosforoso/níquel.
- **Cables anunciados compatibles:** 20–29 AWG.
- **Montaje descrito:** base autoadhesiva y encastres laterales.
- **Estado:** **cambio previsto, pendiente de confirmar físicamente al recibir ambas unidades**. La cifra de 480 puntos mencionada antes no coincide con la ficha de la tienda.
- **Distribución:** placas contiguas; ESP32 cruzando la unión central entre ambas; buzzer encima de una de ellas; relé próximo.
- **Precaución de montaje:** los conectores de protoboard no están diseñados para recibir sacudidas continuas sin retención; revisar el cableado y fijaciones.

## 10. Cables, conectores y accesorios de montaje

<img src="https://img.eclife.com.tw/photo2011/prod_2016/5/G3020046-A.jpg" alt="Fotografía de cables jumper Dupont multicolores" width="260">

*Fotografía comercial de referencia ([EcLife (cables Dupont)](https://www.eclife.com.tw/led/moreinfo_117206.htm)). No identifica necesariamente la unidad física del prototipo ni confirma sus especificaciones.*

- **Cantidad:** pendiente de contar en el ensamble definitivo.
- **Elementos empleados o previstos:** cables jumper/Dupont, conductores para motores y botones, conectores USB y fijaciones desmontables para el encapsulado.
- **Tipos posibles:** macho–macho, macho–hembra y hembra–hembra, por confirmar en cada tramo.
- **Función:** unir alimentación, señales y actuadores, y permitir intervenciones sin desoldar todo el circuito.
- **Por documentar:** calibre, longitudes, cantidad, uniones soldadas y su aislamiento.

---

## Distinción entre documentación técnica y evidencias

- **Este catálogo:** modelos identificados, características, justificación técnica y fotografías comerciales externas de referencia, con enlaces a sus fuentes.
- **[BOM](bom/):** cantidades, especificaciones, proveedor, costo unitario y total. Los costos faltantes **deben obtenerse de boletas, comprobantes o cotizaciones reales; no se inventan**.
- **[Esquemas](esquemas/):** conexiones eléctricas verificadas.
- **[Fotos reales](fotos/):** evidencia del prototipo ensamblado en al menos tres ángulos.
- **[Diseño 3D](../diseno_3d/):** geometría, ensamblaje, renders y planos del encapsulado.

## Referencias fotográficas y verificación

Las fotografías visibles se enlazan directamente a publicaciones de sus proveedores o distribuidores, identificados junto a cada imagen. **No son imágenes generadas por IA** ni fotografías de las unidades adquiridas para este proyecto. No se han añadido copias de fotografías comerciales al repositorio; se utilizan enlaces externos, por lo que pueden cambiar si las tiendas modifican sus archivos. Las imágenes se incluyen para facilitar la identificación visual, no para atribuir marcas o especificaciones no comprobadas.

La elaboración de la documentación y sus herramientas están registradas en [FUENTES.md](../FUENTES.md).
