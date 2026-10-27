# Iteración 1 - Concepto Inicial

## Información General

**Fecha:** [23/10/2026]  
**Versión:** v1.0  
**Estado:** Prototipo alpha - Prueba de concepto  
**Avance asociado:** Planificación inicial / Avance #1

---

## Descripción

Alarma tipo despertador para personas con algun grado de discapacidad auditiva, se coloca bajo la almohada y vibra cuando se activa la alarma

**Objetivo de esta iteración:**
- Probar conexión de sensores básicos
- Validar comunicación con microcontrolador
- Demostrar concepto de actuación
- Circuito básico en protoboard

---

## Componentes Utilizados

### Hardware
- Microcontrolador: ESP32 Devkit V1 30 Pines MicroUSB
- Actuadores:
  - Motor Vibrador PWM Switch DC
  - Buzzer Pasivo
- Otros: 
- Cable Micro-USD
- Cables Puente

### Software
- IDE: Arduino IDE
- Librerías:
  - ESP32 Arduino Core(Expressif Systems) - Versión3.3.12
  - AsyncTCP (ESP32Async) - Versión 3.5.0
  - ESPAsyncWebServer (ESP32Async) - Versión 3.12.1
  - WiFi.h - Incluida en ESP32 Core 3.3.12
  - DNSServer.h - Incluida en ESP32 Core 3.3.12
  - Preferences.h - Incluida en ESP32 Core 3.3.12
  - esp_wifi.h - Incluida en ESP32 Core 3.3.12
  - Arduino.h - Incluida en ESP32 Core 3.3.12
- Versión código: v1.0

---

## Fotos del Prototipo

<img width="1600" height="1200" alt="image" src="https://github.com/user-attachments/assets/fdb5e378-60b1-4130-97ee-3a5fad0a3f21" />
<img width="1600" height="900" alt="image" src="https://github.com/user-attachments/assets/8a02f3ee-5bd1-467e-bb11-0e2da8048a70" />

---

## Resultados de Testing Inicial

### Funcionalidad Lograda
✅ Conexión de sensores básicos y correcta comunicación con el microcontrolador Esp32. 

✅ Codigo corriendo, actuadores funcionando.

❌ Vibración demasiado debil del motor vibrador PWM Switch DC.

### Problemas Identificados

1. **Problema 1:**
   - Descripción: Vibración del motor vibrador PWM Switch DC demasiado debil para lo que se espera del prototipo final.
   - Causa probable: Modelo (PWM Switch DC), simplemente no tiene una potencia de vibración lo suficientemente fuerte para lo que esperamos como grupo
   - Solución propuesta: Comprar un modelo de vibrador con una potencia bastante mayor a la que se tiene actualmente.

2. **Problema 2:**
   - Descripción: Conexiones muy propensas a soltarse a un minimo movimiento del prototipo,
   - Causa probable: Orden mal distribuído de los cables, pero principalmente el hecho de que se encuentre todo en un protoboard y no en una placa perforada.
   - Solución propuesta: Fijar microcontrolador, actuadores y cables a una placa perforada (soldar).

---

## Aprendizajes

### Técnicos
-Se comprobó la comunicación entre la ESP32 y los actuadores, permitiendo ejecutar el código y activar el motor vibrador y el buzzer.
-Se identificó que la potencia del motor vibrador utilizado es insuficiente para el objetivo del proyecto, por lo que se requiere un modelo más potente.
-Se observó que las conexiones mediante protoboard y cables puente pueden soltarse fácilmente al mover el dispositivo, por lo que es necesario mejorar su fijación.

### De Diseño
-La alarma debe generar vibraciones suficientemente intensas para que puedan percibirse al estar ubicada debajo de una almohada.
-Es importante considerar un sistema de apagado físico para evitar que el usuario dependa exclusivamente del celular.
-El encapsulado debe permitir organizar y proteger los componentes electrónicos, manteniendo un diseño adecuado para colocarlo debajo de la almohada.

---

## Plan para Iteración 2

### Mejoras Planificadas

**Hardware:**
- [ ] Reemplazar el motor vibrador actual por uno de mayor potencia.
- [ ] Implementar un botón físico para detener la alarma.
- [ ] Fijar y soldar las conexiones en una placa perforada para evitar desconexiones.
**Software:**
- [ ] Incorporar al código la lectura del botón físico para detener la alarma.
- [ ] Adaptar el control del motor vibrador al nuevo modelo seleccionado y comprobar su funcionamiento.

**Diseño:**
- [ ] Iniciar diseño de encapsulado
- [ ] Mejorar ruteo de cables

---

## Archivos en esta Carpeta

- `v1_codigo.ino` - Código de esta versión
- `v1_esquema.png` - Esquema del circuito
- `v1_fotos/` - Fotografías del prototipo
- `v1_notas.txt` - Notas adicionales del equipo
