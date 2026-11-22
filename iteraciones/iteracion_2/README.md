# Iteración 2 - Primera Mejora Significativa

## Información General

**Fecha:** [20/11/2025]  
**Versión:** v2.0  
**Estado:** Prototipo funcional mejorado  
**Avance asociado:** Avance #2

---


---
Iteración 2 – Mejoras del prototipo

Descripción

Segunda versión de la alarma vibratoria para personas sordas o con discapacidad auditiva, enfocada en aumentar la intensidad de vibración y mejorar la autonomía del usuario.

Objetivos de esta iteración:

Mejorar el sistema de vibración.

Incorporar controles físicos.

Reducir la dependencia del celular.

Cambios respecto a v1

Hardware

Agregado:

Dos motores vibratorios de 1,5–6 V y 3500 RPM.

Dos pulsadores táctiles.

Modificado:

Sistema de activación de la alarma: incorporación de motores vibratorios para aumentar la intensidad del estímulo.

Removido:

Buzzer inicial, debido a su baja capacidad de vibración.

Software

Nuevas funcionalidades:

Control del apagado mediante botones físicos.

Adaptación de la lógica de activación para los motores vibratorios.

Optimizaciones:

Reducción de la dependencia del celular para controlar la alarma.

Bugs corregidos:

Pendiente de documentar las fallas de software efectivamente solucionadas.

Diseño mecánico

Diseño del encapsulado a cargo del integrante responsable del modelado 3D.

Estado de fabricación e integración pendiente de confirmar.



---

## Fotos del Prototipo v2

Incluir en esta carpeta:
<img width="1200" height="1600" alt="PHOTO-2026-11-21-21-47-17" src="https://github.com/user-attachments/assets/d2945ed1-0ebf-4ee3-84c4-bbba9afbd767" />

---

## Resultados de Testing

### Funcionalidad Lograda
✅ [Función 1] vibracion notoriamente mas fuerte, botones funcionales 
✅ [Función 2] vibracion notoriamente mas fuerte, botones funcionales 
✅ [Función 3] vibracion notoriamente mas fuerte, botones funcionales 
⚠️ [Función 4] se quemo el portapilas


---

## Problemas Pendientes

1. **Problema 1: Cortocircuito en el módulo portabaterías**
   - **Descripción:** El módulo funcionaba correctamente hasta que se desprendió una conexión que debió ser soldada nuevamente. Posteriormente, al insertar las baterías, se produjo un cortocircuito y sobrecalentamiento. No se logró identificar la causa exacta.
   - **Prioridad:** Alta.
   - **Plan para v3:** Revisar las conexiones y soldaduras con un multímetro, identificar el origen de la falla y reemplazar el módulo si presenta daños, antes de volver a energizar el circuito.

---

## Plan para Iteración 3 (Versión Final)

### Mejoras Críticas

**Hardware:**
- [ ] [Mejora crítica 1]
- [ ] [Mejora crítica 2]

**Software:**
- [ ] [Optimización 1]
- [ ] [Feature faltante]

**Diseño:**
- [ ] Refinar encapsulado
- [ ] Mejorar accesibilidad
- [ ] Finalizar sistema de montaje

**Testing:**
- [ ] Testear con 5+ usuarios
- [ ] Validar métricas ODS
- [ ] Instalación en contexto real

---

## Archivos en esta Carpeta

- `v2_codigo.ino` - Código de esta versión
- `v2_esquema.png` - Esquema del circuito actualizado
- `v2_modelo3d.f3d` - Primer diseño en Fusion 360
- `v2_fotos/` - Fotografías del prototipo
- `v2_feedback.pdf` - Compilación de comentarios recibidos
