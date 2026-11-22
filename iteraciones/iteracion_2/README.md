# Iteración 2 - Primera Mejora Significativa

## Información General

**Fecha:** [20/11/2025]  
**Versión:** v2.0  
**Estado:** Prototipo funcional mejorado  
**Avance asociado:** Avance #2

---


---

# Iteración 2 – Mejoras del prototipo

## Descripción

Segunda versión de la alarma vibratoria para personas sordas o con discapacidad auditiva, enfocada en aumentar la intensidad de vibración y mejorar la autonomía del usuario.

**Objetivos de esta iteración:**

- Mejorar el sistema de vibración.
- Incorporar controles físicos.
- Reducir la dependencia del celular.

---

## Cambios respecto a v1

### Hardware

**Agregado:**

- Dos motores vibratorios de 1,5–6 V y 3500 RPM.
- Dos pulsadores táctiles.

**Modificado:**

- Sistema de activación de la alarma: incorporación de motores vibratorios para aumentar la intensidad del estímulo.

**Removido:**

- Buzzer inicial, debido a su baja capacidad de vibración.

### Software

**Nuevas funcionalidades:**

- Control del apagado mediante botones físicos.
- Adaptación de la lógica de activación para los motores vibratorios.

**Optimizaciones:**

- Reducción de la dependencia del celular para controlar la alarma.

### Diseño mecánico

...

---

## Fotos del Prototipo v2

<img width="1200" height="1600" alt="Prototipo de alarma vibratoria v2" src="https://github.com/user-attachments/assets/d2945ed1-0ebf-4ee3-84c4-bbba9afbd767" />

---

## Resultados de Testing

### Funcionalidad lograda

✅ **Sistema de vibración:** Se observó una vibración notoriamente más intensa respecto al buzzer inicial.

✅ **Botones físicos:** Se comprobó el funcionamiento de los pulsadores para controlar la alarma.

⚠️ **Sistema de alimentación:** Se observó calentamiento en el portapilas. Ante un posible cortocircuito, se decidió reemplazarlo.

---

## Dificultad detectada

### Problema 1: Calentamiento del portapilas

- **Descripción:** Se desprendió una conexión que debió ser soldada nuevamente. Al colocar las pilas, el portapilas se calentó, incluso estando desconectado del resto del circuito.
- **Prioridad:** Alta.
- **Acción definida:** Se decidió reemplazar el portapilas. El proyecto funcionó en las pruebas realizadas.

---

## Plan para Iteración 3 (Versión Final)

### Mejoras críticas

**Hardware:**

- Se decidió reemplazar el portapilas.
- [ ] Verificar la seguridad de las conexiones eléctricas.

**Software:**

- [ ] Comprobar el funcionamiento integrado de los botones y motores.
- [ ] Verificar la correcta activación y desactivación de la alarma.

**Diseño:**

- [ ] Refinar encapsulado.
- [ ] Finalizar sistema de montaje.

**Testing:**

- [ ] Realizar pruebas de vibración bajo la almohada.
- [ ] Evaluar el funcionamiento autónomo del dispositivo.
- [ ] Registrar resultados de las pruebas realizadas.
- [ ] Validar el prototipo con usuarios de la población objetivo en una etapa posterior.

---

## Archivos en esta Carpeta

- `v2_codigo.ino` - Código utilizado en la segunda versión del prototipo.
- `v2_esquema.png` - Esquema de conexiones eléctricas de la versión 2.
Esquema del circuito actualizado
- `v2_modelo3d.f3d` - Primer diseño en Fusion 360
- `v2_fotos/` - Fotografías del prototipo
- `v2_feedback.pdf` - Compilación de comentarios recibidos
