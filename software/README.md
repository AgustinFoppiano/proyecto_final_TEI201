# Software - Documentación

## Contenido
Esta carpeta contiene todo el código y documentación del software del proyecto.

### 📁 Carpetas

#### `src/`
Código fuente del proyecto (.ino para Arduino/ESP32)

#### `librerias/`
Librerías adicionales necesarias (no incluidas en Arduino IDE)

#### `docs/`
Documentación técnica del software

---

## Stack Tecnológico

**Plataforma:** Arduino / ESP32  
**Lenguaje:** C/C++  
**IDE:** Arduino IDE 2.x 

## Librerías principales
- **ESP32 Arduino Core (Espressif Systems)** - Versión **3.3.12**
- **AsyncTCP (ESP32Async)** - Versión **3.5.0**
- **ESPAsyncWebServer (ESP32Async)** - Versión **3.12.1**
- **WiFi.h** - Incluida en **ESP32 Core 3.3.12**
- **DNSServer.h** - Incluida en **ESP32 Core 3.3.12**
- **Preferences.h** - Incluida en **ESP32 Core 3.3.12**
- **esp_wifi.h** - Incluida en **ESP32 Core 3.3.12**
- **Arduino.h** - Incluida en **ESP32 Core 3.3.12**
---

## Instalación y Configuración

### 1. Instalar Arduino IDE
[Instrucciones de instalación]

### 2. Configurar ESP32/Arduino
[Pasos de configuración]

### 3. Instalar Librerías
```bash
# Copiar librerías personalizadas
cp -r librerias/* ~/Arduino/libraries/
```

### 4. Cargar Código
1. Abrir `src/main.ino`
2. Seleccionar placa y puerto
3. Compilar y subir

---

## Configuración de Parámetros

Editar las siguientes constantes en el código:

```cpp
// WiFi
#define WIFI_SSID "tu_red"
#define WIFI_PASS "tu_password"

// Sensores
#define SENSOR_PIN 4
#define SAMPLE_RATE 1000

// Otros parámetros
```

---

## Arquitectura del Software

[Incluir diagrama de flujo o arquitectura]

### Módulos Principales
1. **Inicialización** - Setup del sistema
2. **Lectura de Sensores** - Captura de datos
3. **Procesamiento** - Análisis y decisiones
4. **Actuación** - Control de actuadores
5. **Comunicación** - Envío de datos

---

## API / Endpoints (si aplica)

| Endpoint | Método | Descripción |
|----------|--------|-------------|
| `/status` | GET | Estado del sistema |
| `/data` | GET | Datos de sensores |
| `/control` | POST | Control de actuadores |
