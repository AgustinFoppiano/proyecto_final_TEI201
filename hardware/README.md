# Hardware - Documentación

## Contenido
Esta carpeta contiene toda la documentación técnica del hardware del proyecto.

### 📁 Carpetas

#### `esquemas/`
Diagramas de circuitos y esquemáticos del sistema

#### `bom/`
Bill of Materials (Lista de materiales)

#### `fotos/`
Fotografías de alta resolución del prototipo ensamblado

---

## Instrucciones de Ensamble

### Componentes Principales
1. **ESP32:** Microcontrolador principal encargado de procesar la información y controlar los componentes electrónicos del sistema.
2. **Pantalla OLED:** Dispositivo utilizado para visualizar información y mensajes del sistema.
3. **Buzzer:** Componente encargado de emitir señales sonoras de alerta.
4. **Motor vibrador:** Módulo que genera vibraciones para proporcionar alertas físicas al usuario.
5. **Protoboard:** Base utilizada para montar y conectar los componentes electrónicos sin necesidad de soldadura.
6. **Cables Dupont:** Permiten realizar las conexiones eléctricas entre la ESP32 y los componentes.
7. **Cable USB:** Utilizado para alimentar y programar la ESP32 desde un computador.

### Pasos de Ensamblaje
1. Colocar la placa ESP32 sobre la protoboard, dejando espacio para los demás componentes.
2. Instalar la pantalla OLED sobre la protoboard.
3. Colocar el buzzer en la protoboard.
4. Conectar el módulo de vibración utilizando cables Dupont.
5. Realizar las conexiones de alimentación, tierra y señales entre la ESP32 y los componentes, siguiendo el esquema eléctrico del proyecto.
6. Conectar la ESP32 al computador mediante un cable USB.
7. Cargar el programa desarrollado para el sistema.
8. Verificar el funcionamiento de la pantalla OLED, el buzzer y el motor vibrador.

### Precauciones
- ⚠️ Verificar las conexiones eléctricas antes de alimentar el circuito.
- ⚠️ Respetar los voltajes de funcionamiento de cada componente.
- ⚠️ No conectar cargas que superen la capacidad de corriente de los pines de la ESP32.
- ⚠️ Desconectar la alimentación antes de modificar las conexiones.
- ⚠️ Manipular cuidadosamente los componentes para evitar daños en sus conexiones.

---

## Especificaciones Técnicas

**Alimentación:** [Voltaje y corriente]  
**Consumo:** [Watts/mA]  
**Dimensiones:** [mm x mm x mm]  
**Peso:** [gramos]

---

## Troubleshooting

| Problema | Posible Causa | Solución |
|----------|---------------|----------|
| [Problema 1] | [Causa] | [Solución] |
| [Problema 2] | [Causa] | [Solución] |
