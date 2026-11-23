### Información del Equipo
- **Integrantes:**
  - Benjamín Barrionuevo
  - Francisca Borne
  - Agustín Foppiano
  - Isidora Herrera
  - Luciano Vera
  
- **ODS Seleccionado:** 10. Reducción de las desigualdades
- **Problema a resolver:** Las personas con discapacidad auditiva tienen dificultad para usar alarmas convencionales.
### Descripción del Proyecto
Alarma dirigida a personas con discapacidad auditiva, programable desde el celular mediante una red Wi-Fi local creada por el ESP32. Permite seleccionar vibración, sonido o ambos como aviso, y utiliza una pantalla OLED para mostrar animaciones asociadas a las melodías.

### Estado del Proyecto
- **Código principal:** versión 4.1 para ESP32.
- **Archivo:** [`software/src/alarma_final/alarma_final.ino`](software/src/alarma_final/alarma_final.ino).
- **Versiones previas:** [`software/versiones_anteriores/`](software/versiones_anteriores/).
- **Revisión con historial y exportación CSV:** [versión 4.1 revisiones](software/src/prototipo_4_1_revisiones/README.md), reconstruible sin modificar el código base.

---

##  Estructura del Repositorio
```
├── hardware/          # Circuitos, esquemas y BOM
├── software/          # Código Arduino y librerías
├── diseno_3d/        # Modelos Fusion 360 y renders
├── testing/          # Validación con usuarios
├── documentacion/    # Reportes y presentación
├── iteraciones/      # Historial de versiones
└── FUENTES.md        # Fuentes y herramientas utilizadas
```

---

##  Inicio Rápido

### Requisitos Previos
- Arduino IDE 2.3.11.
- Placa seleccionada: ESP32 Dev Module, con el paquete esp32 by Espressif Systems 3.3.12.
- Esquema de partición: Huge APP (3 MB No OTA / 1 MB SPIFFS).
- Librerías: Async TCP 3.6.1, ESP Async WebServer 3.12.1 y U8g2 2.36.19.
- Cable USB compatible para conectar el ESP32 al computador.
- Autodesk Fusion 360 para visualizar y editar el modelo 3D.

### Instalación
1. Descargar o clonar el repositorio.
2. Instalar el soporte de ESP32 y las librerías indicadas en [software/librerias](software/librerias/README.md).
3. Abrir [alarma_final.ino](software/src/alarma_final/alarma_final.ino), seleccionar la placa, el puerto y el esquema de partición indicados, y cargarlo en el ESP32.
4. Desde el teléfono, conectarse a la red **Alarma para sordos** con la contraseña `porfavor`. Si el portal no se abre, entrar a **http://4.3.2.1**.
5. Configurar y guardar la alarma desde la interfaz. Al abrir la página, el teléfono sincroniza la hora del ESP32.

La [guía de software](software/README.md) incluye la instalación y el funcionamiento paso a paso.

---

## Evidencias para el Avance #3

- [Historial original de 32 activaciones (22/11/2026)](testing/datos/historial_alarmas_2026-11-22.csv).
- [Análisis y gráfico del historial](testing/datos/analisis_historial_2026-11-22.md).
- [Protocolo de verificación del registro](testing/protocolo_registro_eventos.md).
- [Evolución del prototipo y tres iteraciones](iteraciones/README.md).
- [Firmware 4.1 revisiones con historial](software/src/prototipo_4_1_revisiones/README.md).
- [Declaración de librerías, recursos e IA](FUENTES.md).

---

##  Checklist de Entrega

### Hardware ✓
- [ ] Esquema del circuito (Fritzing/Wokwi)
- [ ] BOM completo
- [ ] Fotos de alta resolución

### Software ✓
- [ ] Código comentado
- [ ] Librerías documentadas
- [ ] Manual de instalación

### Diseño 3D ✓
- [ ] Archivos Fusion 360 (.f3d) con TODOS los componentes
- [ ] Renders de alta calidad (1+ ángulos)
- [ ] Planos técnicos

### Testing ✓
- [ ] Reporte de testing con usuarios (mín. 5)
- [ ] Evidencias fotográficas/videos
- [ ] Datos cuantitativos

### Documentación ✓
- [ ] Reporte final (máx. 15 páginas)
- [ ] Presentación (10 min)

---


---

##  Licencia
Este proyecto es desarrollado como parte del curso TEI201 - Facultad de Ingenieria y Ciencias - Universidad Adolfo Ibañez
