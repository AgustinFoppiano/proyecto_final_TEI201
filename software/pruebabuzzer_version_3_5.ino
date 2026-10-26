// VERSION 3.2
// Base estable: VERSION 2.3 (sonido confirmado funcionando)
// Motor vibrador confirmado funcionando en D15.


#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <DNSServer.h>
#include <ESPAsyncWebServer.h>
#include <esp_wifi.h>
#include <Preferences.h>

// =====================================================
// CONFIGURACION
// =====================================================

const char* wifiNombre = "Alarma para sordos";
const char* wifiContrasena = "porfavor";

#define MAX_CLIENTES 4
#define CANAL_WIFI 6
#define MAX_ALARMAS 10

#define BUZZER 18
#define MOTOR_VIBRACION 15

// =====================================================
// PORTAL
// =====================================================

const IPAddress ipLocal(4, 3, 2, 1);
const IPAddress ipGateway(4, 3, 2, 1);
const IPAddress mascara(255, 255, 255, 0);

const String direccionPortal = "http://4.3.2.1";

DNSServer dnsServer;
AsyncWebServer server(80);
Preferences memoria;

// =====================================================
// ALARMAS
//
// repeticion:
// 0 = Una vez
// 1 = Todos los dias
// 2 = Dias elegidos
// 3 = Fecha especifica
// =====================================================

struct Alarma {

  uint8_t hora;
  uint8_t minuto;

  uint8_t tono;
  uint8_t modo;

  uint8_t repeticion;
  uint8_t diasSemana;

  uint16_t anio;
  uint8_t mes;
  uint8_t dia;

  bool activa;
};

Alarma alarmas[MAX_ALARMAS];

uint8_t cantidadAlarmas = 0;

long ultimoDiaActivado[MAX_ALARMAS];

// =====================================================
// FORMATO ANTIGUO
// =====================================================

struct AlarmaVieja {

  uint8_t hora;
  uint8_t minuto;
  uint8_t tono;
  uint8_t modo;
  bool activa;
};

// =====================================================
// HORA
// =====================================================

bool horaSincronizada = false;

int64_t horaLocalSincronizada = 0;

uint32_t millisSincronizacion = 0;

String ultimoEvento = "";

// =====================================================
// ALARMA SONANDO
// =====================================================

int alarmaSonandoIndice = -1;

bool musicaActiva = false;

int notaActual = 0;

bool pausaEntreNotas = false;

unsigned long siguienteCambioMusica = 0;

// =====================================================
// 0 - HOMECOMING (Samsung)
// Adaptacion monofonica corta para buzzer pasivo.
// El original Samsung existe como Homecoming.ogg.
// =====================================================

const int homecomingNotas[] = {
  587, 740, 880, 1175,
  880, 740, 659, 740,
  880, 988, 880, 740
};

const int homecomingDuraciones[] = {
  200, 200, 240, 380,
  200, 200, 300, 200,
  200, 320, 220, 420
};

const int homecomingCantidad =
  sizeof(homecomingNotas) /
  sizeof(homecomingNotas[0]);

// =====================================================
// 1 - QUANTUM BELL (Samsung)
// Adaptacion monofonica corta para buzzer pasivo.
// El original Samsung existe como Quantum_Bell.ogg.
// =====================================================

const int quantumNotas[] = {
  1760, 2349, 2093, 2637,
  2349, 1760, 1976, 2349,
  2637, 2093, 1976, 1760
};

const int quantumDuraciones[] = {
  150, 260, 160, 340,
  180, 240, 160, 260,
  320, 180, 220, 420
};

const int quantumCantidad =
  sizeof(quantumNotas) /
  sizeof(quantumNotas[0]);

// =====================================================
// 2 - SPACE BELL (Samsung)
// Adaptacion monofonica corta para buzzer pasivo.
// El original Samsung existe como Space_Bell.ogg.
// =====================================================

const int spaceNotas[] = {
  988, 1480, 1976, 2637,
  1976, 1568, 1319, 1976,
  2349, 1976, 1480, 988
};

const int spaceDuraciones[] = {
  200, 180, 300, 360,
  180, 220, 180, 280,
  340, 200, 220, 440
};

const int spaceCantidad =
  sizeof(spaceNotas) /
  sizeof(spaceNotas[0]);

// =====================================================
// 3 - MEGALOVANIA - Toby Fox
// Fragmento corto del riff inicial para buzzer.
// Este es el motivo que ya fue probado con el buzzer D18.
// =====================================================

const int megalovaniaNotas[] = {
  294, 294, 587, 440, 415,
  392, 349, 294, 349, 392
};

const int megalovaniaDuraciones[] = {
  140, 140, 280, 280, 140,
  280, 280, 140, 140, 280
};

const int megalovaniaCantidad =
  sizeof(megalovaniaNotas) /
  sizeof(megalovaniaNotas[0]);

// =====================================================
// 4 - NEVER GONNA GIVE YOU UP
// Rick Astley
//
// Fragmento reconocible adaptado desde la secuencia
// para buzzer publicada en robsoncouto/arduino-songs.
// El 0 representa una pausa.
// =====================================================

const int neverGonnaNotas[] = {
  0,   659, 740, 659,
  440, 494, 587, 494,
  740, 740, 659, 440,
  494, 587, 494, 659,
  659, 587, 554, 494,
  440, 494, 587, 494
};

const int neverGonnaDuraciones[] = {
  237, 237, 237, 710,
  118, 118, 118, 118,
  355, 355, 710, 118,
  118, 118, 118, 355,
  355, 355, 118, 355,
  118, 118, 118, 118
};

const int neverGonnaCantidad =
  sizeof(neverGonnaNotas) /
  sizeof(neverGonnaNotas[0]);

// =====================================================
// 5 - TAKE ON ME
// a-ha
//
// Riff principal adaptado desde la secuencia
// para buzzer publicada en robsoncouto/arduino-songs.
// El 0 representa una pausa.
// =====================================================

const int takeOnMeNotas[] = {
  740, 740, 587, 494,
  0,   494, 0,   659,
  0,   659, 0,   659,
  831, 831, 880, 988,
  880, 880, 880, 659,
  0,   587, 0,   740,
  0,   740, 0,   740,
  659, 659, 740, 659
};

const int takeOnMeDuraciones[] = {
  174, 174, 174, 174,
  174, 174, 174, 174,
  174, 174, 174, 174,
  174, 174, 174, 174,
  174, 174, 174, 174,
  174, 174, 174, 174,
  174, 174, 174, 174,
  174, 174, 174, 174
};

const int takeOnMeCantidad =
  sizeof(takeOnMeNotas) /
  sizeof(takeOnMeNotas[0]);

// =====================================================
// NOMBRES
// =====================================================

String nombreTono(uint8_t tono) {

  switch (tono) {

    case 0:
      return "Homecoming";

    case 1:
      return "Quantum Bell";

    case 2:
      return "Space Bell";

    case 3:
      return "Megalovania";

    case 4:
      return "Never Gonna Give You Up";

    case 5:
      return "Take On Me";
  }

  return "Tono";
}

String nombreModo(uint8_t modo) {

  switch (modo) {

    case 0:
      return "Sonido";

    case 1:
      return "Vibración";

    case 2:
      return "Sonido + vibración";
  }

  return "Modo";
}

// =====================================================
// PAGINA WEB
// =====================================================

const char paginaWeb[] PROGMEM =
  "\n"
  "<!DOCTYPE html>\n"
  "<html lang=\"es\">\n"
  "\n"
  "<head>\n"
  "\n"
  "<meta charset=\"UTF-8\">\n"
  "\n"
  "<meta\n"
  "  name=\"viewport\"\n"
  "  content=\"width=device-width, initial-scale=1.0\">\n"
  "\n"
  "<title>Alarmas proyecto</title>\n"
  "\n"
  "<style>\n"
  "\n"
  "* {\n"
  "  box-sizing: border-box;\n"
  "}\n"
  "\n"
  "body {\n"
  "  margin: 0;\n"
  "  font-family: Arial, sans-serif;\n"
  "  background: #f2f2f7;\n"
  "  color: #111;\n"
  "}\n"
  "\n"
  ".app {\n"
  "  max-width: 500px;\n"
  "  margin: auto;\n"
  "  padding: 20px;\n"
  "}\n"
  "\n"
  ".cabecera {\n"
  "  display: flex;\n"
  "  justify-content: space-between;\n"
  "  align-items: center;\n"
  "  margin-bottom: 10px;\n"
  "}\n"
  "\n"
  "h1 {\n"
  "  margin: 0;\n"
  "  font-size: 32px;\n"
  "}\n"
  "\n"
  ".boton-mas {\n"
  "  width: 48px;\n"
  "  height: 48px;\n"
  "  border: none;\n"
  "  border-radius: 50%;\n"
  "  background: #007aff;\n"
  "  color: white;\n"
  "  font-size: 30px;\n"
  "}\n"
  "\n"
  ".estado-hora {\n"
  "  color: #666;\n"
  "  font-size: 14px;\n"
  "  margin-bottom: 20px;\n"
  "}\n"
  "\n"
  ".alarma {\n"
  "  background: white;\n"
  "  border-radius: 18px;\n"
  "  padding: 18px;\n"
  "  margin-bottom: 15px;\n"
  "}\n"
  "\n"
  ".alarma-superior {\n"
  "  display: flex;\n"
  "  justify-content: space-between;\n"
  "  align-items: center;\n"
  "}\n"
  "\n"
  ".hora {\n"
  "  font-size: 42px;\n"
  "  font-weight: 300;\n"
  "}\n"
  "\n"
  ".detalle {\n"
  "  color: #666;\n"
  "  margin-top: 8px;\n"
  "  line-height: 1.6;\n"
  "}\n"
  "\n"
  ".interruptor {\n"
  "  width: 52px;\n"
  "  height: 30px;\n"
  "  position: relative;\n"
  "}\n"
  "\n"
  ".interruptor input {\n"
  "  display: none;\n"
  "}\n"
  "\n"
  ".slider {\n"
  "  position: absolute;\n"
  "  inset: 0;\n"
  "  background: #ccc;\n"
  "  border-radius: 20px;\n"
  "}\n"
  "\n"
  ".slider:before {\n"
  "  content: \"\";\n"
  "  position: absolute;\n"
  "  width: 26px;\n"
  "  height: 26px;\n"
  "  left: 2px;\n"
  "  top: 2px;\n"
  "  background: white;\n"
  "  border-radius: 50%;\n"
  "  transition: 0.2s;\n"
  "}\n"
  "\n"
  ".interruptor input:checked + .slider {\n"
  "  background: #34c759;\n"
  "}\n"
  "\n"
  ".interruptor input:checked + .slider:before {\n"
  "  transform: translateX(22px);\n"
  "}\n"
  "\n"
  ".acciones {\n"
  "  display: flex;\n"
  "  gap: 10px;\n"
  "  margin-top: 15px;\n"
  "}\n"
  "\n"
  ".acciones button {\n"
  "  border: none;\n"
  "  border-radius: 10px;\n"
  "  padding: 10px 14px;\n"
  "  font-size: 15px;\n"
  "}\n"
  "\n"
  ".editar {\n"
  "  background: #e5e5ea;\n"
  "}\n"
  "\n"
  ".eliminar {\n"
  "  background: #ffe5e5;\n"
  "  color: #d70015;\n"
  "}\n"
  "\n"
  ".editor {\n"
  "  display: none;\n"
  "  background: white;\n"
  "  border-radius: 20px;\n"
  "  padding: 20px;\n"
  "}\n"
  "\n"
  ".editor.visible {\n"
  "  display: block;\n"
  "}\n"
  "\n"
  ".campo {\n"
  "  margin-bottom: 22px;\n"
  "}\n"
  "\n"
  ".titulo-campo {\n"
  "  display: block;\n"
  "  font-weight: bold;\n"
  "  margin-bottom: 10px;\n"
  "}\n"
  "\n"
  "input[type=\"time\"],\n"
  "input[type=\"date\"],\n"
  "select {\n"
  "  width: 100%;\n"
  "  padding: 14px;\n"
  "  border: 1px solid #ddd;\n"
  "  border-radius: 12px;\n"
  "  font-size: 18px;\n"
  "  background: white;\n"
  "}\n"
  "\n"
  ".modo-opcion,\n"
  ".dia-opcion {\n"
  "  display: block;\n"
  "  padding: 9px 0;\n"
  "  font-size: 17px;\n"
  "}\n"
  "\n"
  ".botones-editor {\n"
  "  display: flex;\n"
  "  gap: 10px;\n"
  "}\n"
  "\n"
  ".guardar {\n"
  "  flex: 1;\n"
  "  border: none;\n"
  "  padding: 14px;\n"
  "  border-radius: 12px;\n"
  "  background: #007aff;\n"
  "  color: white;\n"
  "  font-size: 17px;\n"
  "}\n"
  "\n"
  ".cancelar {\n"
  "  border: none;\n"
  "  padding: 14px;\n"
  "  border-radius: 12px;\n"
  "  background: #e5e5ea;\n"
  "  font-size: 17px;\n"
  "}\n"
  "\n"
  ".vacio {\n"
  "  text-align: center;\n"
  "  color: #777;\n"
  "  margin-top: 60px;\n"
  "}\n"
  "\n"
  ".evento {\n"
  "  display: none;\n"
  "  background: white;\n"
  "  border-radius: 15px;\n"
  "  padding: 14px;\n"
  "  margin-bottom: 15px;\n"
  "  font-size: 15px;\n"
  "}\n"
  "\n"
  ".detener-alarma {\n"
  "  display: none;\n"
  "  width: 100%;\n"
  "  border: none;\n"
  "  border-radius: 15px;\n"
  "  padding: 18px;\n"
  "  margin-bottom: 18px;\n"
  "  background: #d70015;\n"
  "  color: white;\n"
  "  font-size: 19px;\n"
  "  font-weight: bold;\n"
  "}\n"
  "\n"
  ".detener-alarma.visible {\n"
  "  display: block;\n"
  "}\n"
  "\n"
  ".opciones-extra {\n"
  "  display: none;\n"
  "  background: #f7f7f8;\n"
  "  padding: 14px;\n"
  "  margin-top: 10px;\n"
  "  border-radius: 12px;\n"
  "}\n"
  "\n"
  ".opciones-extra.visible {\n"
  "  display: block;\n"
  "}\n"
  "\n"
  ".aviso {\n"
  "  position: fixed;\n"
  "  left: 50%;\n"
  "  bottom: 25px;\n"
  "\n"
  "  transform:\n"
  "    translateX(-50%)\n"
  "    translateY(20px);\n"
  "\n"
  "  width: calc(100% - 40px);\n"
  "  max-width: 420px;\n"
  "\n"
  "  background: #222;\n"
  "  color: white;\n"
  "\n"
  "  padding: 14px 18px;\n"
  "\n"
  "  border-radius: 14px;\n"
  "  text-align: center;\n"
  "\n"
  "  opacity: 0;\n"
  "  pointer-events: none;\n"
  "\n"
  "  transition:\n"
  "    opacity 0.25s,\n"
  "    transform 0.25s;\n"
  "}\n"
  "\n"
  ".aviso.visible {\n"
  "  opacity: 1;\n"
  "\n"
  "  transform:\n"
  "    translateX(-50%)\n"
  "    translateY(0);\n"
  "}\n"
  "\n"
  "</style>\n"
  "\n"
  "</head>\n"
  "\n"
  "<body>\n"
  "\n"
  "<div class=\"app\">\n"
  "\n"
  "<div id=\"pantallaPrincipal\">\n"
  "\n"
  "<div class=\"cabecera\">\n"
  "\n"
  "<h1>Alarmas</h1>\n"
  "\n"
  "<button\n"
  "class=\"boton-mas\"\n"
  "onclick=\"nuevaAlarma()\">\n"
  "\n"
  "+\n"
  "\n"
  "</button>\n"
  "\n"
  "</div>\n"
  "\n"
  "\n"
  "<div\n"
  "id=\"estadoHora\"\n"
  "class=\"estado-hora\">\n"
  "\n"
  "Sincronizando hora...\n"
  "\n"
  "</div>\n"
  "\n"
  "\n"
  "<div\n"
  "id=\"ultimoEvento\"\n"
  "class=\"evento\">\n"
  "</div>\n"
  "\n"
  "\n"
  "<button\n"
  "id=\"botonDetener\"\n"
  "class=\"detener-alarma\"\n"
  "onclick=\"detenerAlarma()\">\n"
  "\n"
  "Detener alarma\n"
  "\n"
  "</button>\n"
  "\n"
  "\n"
  "<div id=\"listaAlarmas\"></div>\n"
  "\n"
  "</div>\n"
  "\n"
  "\n"
  "<div\n"
  "id=\"editor\"\n"
  "class=\"editor\">\n"
  "\n"
  "<h2 id=\"tituloEditor\">\n"
  "Nueva alarma\n"
  "</h2>\n"
  "\n"
  "\n"
  "<div class=\"campo\">\n"
  "\n"
  "<label class=\"titulo-campo\">\n"
  "Hora\n"
  "</label>\n"
  "\n"
  "<input\n"
  "type=\"time\"\n"
  "id=\"hora\">\n"
  "\n"
  "</div>\n"
  "\n"
  "\n"
  "<div class=\"campo\">\n"
  "\n"
  "<label class=\"titulo-campo\">\n"
  "Tono / melodía\n"
  "</label>\n"
  "\n"
  "<select id=\"tono\">\n"
  "\n"
  "<option value=\"0\">\n"
  "Homecoming\n"
  "</option>\n"
  "\n"
  "<option value=\"1\">\n"
  "Quantum Bell\n"
  "</option>\n"
  "\n"
  "<option value=\"2\">\n"
  "Space Bell\n"
  "</option>\n"
  "\n"
  "<option value=\"3\">\n"
  "Megalovania\n"
  "</option>\n"
  "\n"
  "<option value=\"4\">\n"
  "Never Gonna Give You Up\n"
  "</option>\n"
  "\n"
  "<option value=\"5\">\n"
  "Take On Me\n"
  "</option>\n"
  "\n"
  "</select>\n"
  "\n"
  "</div>\n"
  "\n"
  "\n"
  "<div class=\"campo\">\n"
  "\n"
  "<label class=\"titulo-campo\">\n"
  "Repetir\n"
  "</label>\n"
  "\n"
  "<select\n"
  "id=\"repeticion\"\n"
  "onchange=\"actualizarOpcionesRepeticion()\">\n"
  "\n"
  "<option value=\"0\">\n"
  "Una vez\n"
  "</option>\n"
  "\n"
  "<option value=\"1\">\n"
  "Todos los días\n"
  "</option>\n"
  "\n"
  "<option value=\"2\">\n"
  "Elegir días\n"
  "</option>\n"
  "\n"
  "<option value=\"3\">\n"
  "Fecha específica\n"
  "</option>\n"
  "\n"
  "</select>\n"
  "\n"
  "\n"
  "<div\n"
  "id=\"panelDias\"\n"
  "class=\"opciones-extra\">\n"
  "\n"
  "<label class=\"dia-opcion\">\n"
  "<input type=\"checkbox\" class=\"diaCheck\" value=\"1\">\n"
  "Lunes\n"
  "</label>\n"
  "\n"
  "<label class=\"dia-opcion\">\n"
  "<input type=\"checkbox\" class=\"diaCheck\" value=\"2\">\n"
  "Martes\n"
  "</label>\n"
  "\n"
  "<label class=\"dia-opcion\">\n"
  "<input type=\"checkbox\" class=\"diaCheck\" value=\"3\">\n"
  "Miércoles\n"
  "</label>\n"
  "\n"
  "<label class=\"dia-opcion\">\n"
  "<input type=\"checkbox\" class=\"diaCheck\" value=\"4\">\n"
  "Jueves\n"
  "</label>\n"
  "\n"
  "<label class=\"dia-opcion\">\n"
  "<input type=\"checkbox\" class=\"diaCheck\" value=\"5\">\n"
  "Viernes\n"
  "</label>\n"
  "\n"
  "<label class=\"dia-opcion\">\n"
  "<input type=\"checkbox\" class=\"diaCheck\" value=\"6\">\n"
  "Sábado\n"
  "</label>\n"
  "\n"
  "<label class=\"dia-opcion\">\n"
  "<input type=\"checkbox\" class=\"diaCheck\" value=\"0\">\n"
  "Domingo\n"
  "</label>\n"
  "\n"
  "</div>\n"
  "\n"
  "\n"
  "<div\n"
  "id=\"panelFecha\"\n"
  "class=\"opciones-extra\">\n"
  "\n"
  "<label class=\"titulo-campo\">\n"
  "Fecha\n"
  "</label>\n"
  "\n"
  "<input\n"
  "type=\"date\"\n"
  "id=\"fechaEspecifica\">\n"
  "\n"
  "</div>\n"
  "\n"
  "</div>\n"
  "\n"
  "\n"
  "<div class=\"campo\">\n"
  "\n"
  "<label class=\"titulo-campo\">\n"
  "Modo\n"
  "</label>\n"
  "\n"
  "<label class=\"modo-opcion\">\n"
  "\n"
  "<input\n"
  "type=\"radio\"\n"
  "name=\"modo\"\n"
  "value=\"0\">\n"
  "\n"
  "🔊 Sonido\n"
  "\n"
  "</label>\n"
  "\n"
  "\n"
  "<label class=\"modo-opcion\">\n"
  "\n"
  "<input\n"
  "type=\"radio\"\n"
  "name=\"modo\"\n"
  "value=\"1\">\n"
  "\n"
  "📳 Vibración\n"
  "\n"
  "</label>\n"
  "\n"
  "\n"
  "<label class=\"modo-opcion\">\n"
  "\n"
  "<input\n"
  "type=\"radio\"\n"
  "name=\"modo\"\n"
  "value=\"2\"\n"
  "checked>\n"
  "\n"
  "🔊📳 Sonido + vibración\n"
  "\n"
  "</label>\n"
  "\n"
  "</div>\n"
  "\n"
  "\n"
  "<div class=\"botones-editor\">\n"
  "\n"
  "<button\n"
  "class=\"cancelar\"\n"
  "onclick=\"cerrarEditor()\">\n"
  "\n"
  "Cancelar\n"
  "\n"
  "</button>\n"
  "\n"
  "\n"
  "<button\n"
  "class=\"guardar\"\n"
  "onclick=\"guardarAlarma()\">\n"
  "\n"
  "Guardar\n"
  "\n"
  "</button>\n"
  "\n"
  "</div>\n"
  "\n"
  "</div>\n"
  "\n"
  "</div>\n"
  "\n"
  "\n"
  "<div\n"
  "id=\"aviso\"\n"
  "class=\"aviso\">\n"
  "</div>\n"
  "\n"
  "\n"
  "<script>\n"
  "\n"
  "const nombresTonos = [\n"
  "\n"
  "  \"Homecoming\",\n"
  "\n"
  "  \"Quantum Bell\",\n"
  "\n"
  "  \"Space Bell\",\n"
  "\n"
  "  \"Megalovania\",\n"
  "\n"
  "  \"Never Gonna Give You Up\",\n"
  "\n"
  "  \"Take On Me\"\n"
  "\n"
  "];\n"
  "\n"
  "\n"
  "const nombresModos = [\n"
  "\n"
  "  \"Sonido\",\n"
  "\n"
  "  \"Vibración\",\n"
  "\n"
  "  \"Sonido + vibración\"\n"
  "\n"
  "];\n"
  "\n"
  "\n"
  "const nombresDias = [\n"
  "\n"
  "  \"Dom\",\n"
  "  \"Lun\",\n"
  "  \"Mar\",\n"
  "  \"Mié\",\n"
  "  \"Jue\",\n"
  "  \"Vie\",\n"
  "  \"Sáb\"\n"
  "\n"
  "];\n"
  "\n"
  "\n"
  "let alarmas = [];\n"
  "\n"
  "let alarmaEditando = -1;\n"
  "\n"
  "let temporizadorAviso;\n"
  "\n"
  "let estabaSonando = false;\n"
  "\n"
  "\n"
  "function dos(numero) {\n"
  "\n"
  "  return String(\n"
  "    numero\n"
  "  ).padStart(\n"
  "    2,\n"
  "    \"0\"\n"
  "  );\n"
  "}\n"
  "\n"
  "\n"
  "function fechaParaInput(fecha) {\n"
  "\n"
  "  return (\n"
  "\n"
  "    fecha.getFullYear() +\n"
  "\n"
  "    \"-\" +\n"
  "\n"
  "    dos(\n"
  "      fecha.getMonth() + 1\n"
  "    ) +\n"
  "\n"
  "    \"-\" +\n"
  "\n"
  "    dos(\n"
  "      fecha.getDate()\n"
  "    )\n"
  "  );\n"
  "}\n"
  "\n"
  "\n"
  "function mostrarAviso(texto) {\n"
  "\n"
  "  const aviso =\n"
  "    document.getElementById(\n"
  "      \"aviso\"\n"
  "    );\n"
  "\n"
  "\n"
  "  aviso.textContent =\n"
  "    texto;\n"
  "\n"
  "\n"
  "  aviso.classList.add(\n"
  "    \"visible\"\n"
  "  );\n"
  "\n"
  "\n"
  "  clearTimeout(\n"
  "    temporizadorAviso\n"
  "  );\n"
  "\n"
  "\n"
  "  temporizadorAviso =\n"
  "    setTimeout(\n"
  "      function() {\n"
  "\n"
  "        aviso.classList.remove(\n"
  "          \"visible\"\n"
  "        );\n"
  "\n"
  "      },\n"
  "      2500\n"
  "    );\n"
  "}\n"
  "\n"
  "\n"
  "function obtenerMascaraDias() {\n"
  "\n"
  "  let mascara = 0;\n"
  "\n"
  "\n"
  "  document\n"
  "    .querySelectorAll(\n"
  "      \".diaCheck\"\n"
  "    )\n"
  "    .forEach(\n"
  "      function(check) {\n"
  "\n"
  "        if (\n"
  "          check.checked\n"
  "        ) {\n"
  "\n"
  "          const dia =\n"
  "            Number(\n"
  "              check.value\n"
  "            );\n"
  "\n"
  "\n"
  "          mascara |=\n"
  "            (\n"
  "              1 << dia\n"
  "            );\n"
  "        }\n"
  "      }\n"
  "    );\n"
  "\n"
  "\n"
  "  return mascara;\n"
  "}\n"
  "\n"
  "\n"
  "function establecerMascaraDias(\n"
  "  mascara\n"
  ") {\n"
  "\n"
  "  document\n"
  "    .querySelectorAll(\n"
  "      \".diaCheck\"\n"
  "    )\n"
  "    .forEach(\n"
  "      function(check) {\n"
  "\n"
  "        const dia =\n"
  "          Number(\n"
  "            check.value\n"
  "          );\n"
  "\n"
  "\n"
  "        check.checked =\n"
  "          (\n"
  "            mascara &\n"
  "            (\n"
  "              1 << dia\n"
  "            )\n"
  "          ) !== 0;\n"
  "      }\n"
  "    );\n"
  "}\n"
  "\n"
  "\n"
  "function actualizarOpcionesRepeticion() {\n"
  "\n"
  "  const repeticion =\n"
  "    Number(\n"
  "      document.getElementById(\n"
  "        \"repeticion\"\n"
  "      ).value\n"
  "    );\n"
  "\n"
  "\n"
  "  const panelDias =\n"
  "    document.getElementById(\n"
  "      \"panelDias\"\n"
  "    );\n"
  "\n"
  "\n"
  "  const panelFecha =\n"
  "    document.getElementById(\n"
  "      \"panelFecha\"\n"
  "    );\n"
  "\n"
  "\n"
  "  panelDias.classList.remove(\n"
  "    \"visible\"\n"
  "  );\n"
  "\n"
  "\n"
  "  panelFecha.classList.remove(\n"
  "    \"visible\"\n"
  "  );\n"
  "\n"
  "\n"
  "  if (\n"
  "    repeticion === 2\n"
  "  ) {\n"
  "\n"
  "    panelDias.classList.add(\n"
  "      \"visible\"\n"
  "    );\n"
  "  }\n"
  "\n"
  "\n"
  "  if (\n"
  "    repeticion === 3\n"
  "  ) {\n"
  "\n"
  "    panelFecha.classList.add(\n"
  "      \"visible\"\n"
  "    );\n"
  "  }\n"
  "}\n"
  "\n"
  "\n"
  "function calcularProximaFecha(\n"
  "  hora,\n"
  "  minuto,\n"
  "  repeticion,\n"
  "  dias,\n"
  "  fechaTexto\n"
  ") {\n"
  "\n"
  "  const ahora =\n"
  "    new Date();\n"
  "\n"
  "\n"
  "  if (\n"
  "    repeticion === 0 ||\n"
  "    repeticion === 1\n"
  "  ) {\n"
  "\n"
  "    const fecha =\n"
  "      new Date(\n"
  "        ahora.getFullYear(),\n"
  "        ahora.getMonth(),\n"
  "        ahora.getDate(),\n"
  "        hora,\n"
  "        minuto,\n"
  "        0,\n"
  "        0\n"
  "      );\n"
  "\n"
  "\n"
  "    if (\n"
  "      fecha <= ahora\n"
  "    ) {\n"
  "\n"
  "      fecha.setDate(\n"
  "        fecha.getDate() + 1\n"
  "      );\n"
  "    }\n"
  "\n"
  "\n"
  "    return fecha;\n"
  "  }\n"
  "\n"
  "\n"
  "  if (\n"
  "    repeticion === 2\n"
  "  ) {\n"
  "\n"
  "    for (\n"
  "      let i = 0;\n"
  "      i <= 7;\n"
  "      i++\n"
  "    ) {\n"
  "\n"
  "      const fecha =\n"
  "        new Date(\n"
  "          ahora.getFullYear(),\n"
  "          ahora.getMonth(),\n"
  "          ahora.getDate() + i,\n"
  "          hora,\n"
  "          minuto,\n"
  "          0,\n"
  "          0\n"
  "        );\n"
  "\n"
  "\n"
  "      const diaSemana =\n"
  "        fecha.getDay();\n"
  "\n"
  "\n"
  "      const elegido =\n"
  "\n"
  "        (\n"
  "          dias &\n"
  "          (\n"
  "            1 << diaSemana\n"
  "          )\n"
  "        ) !== 0;\n"
  "\n"
  "\n"
  "      if (\n"
  "        elegido &&\n"
  "        fecha > ahora\n"
  "      ) {\n"
  "\n"
  "        return fecha;\n"
  "      }\n"
  "    }\n"
  "\n"
  "\n"
  "    return null;\n"
  "  }\n"
  "\n"
  "\n"
  "  if (\n"
  "    repeticion === 3\n"
  "  ) {\n"
  "\n"
  "    if (\n"
  "      !fechaTexto\n"
  "    ) {\n"
  "\n"
  "      return null;\n"
  "    }\n"
  "\n"
  "\n"
  "    const partes =\n"
  "      fechaTexto.split(\n"
  "        \"-\"\n"
  "      );\n"
  "\n"
  "\n"
  "    const fecha =\n"
  "      new Date(\n"
  "\n"
  "        Number(\n"
  "          partes[0]\n"
  "        ),\n"
  "\n"
  "        Number(\n"
  "          partes[1]\n"
  "        ) - 1,\n"
  "\n"
  "        Number(\n"
  "          partes[2]\n"
  "        ),\n"
  "\n"
  "        hora,\n"
  "\n"
  "        minuto,\n"
  "\n"
  "        0,\n"
  "\n"
  "        0\n"
  "      );\n"
  "\n"
  "\n"
  "    if (\n"
  "      fecha <= ahora\n"
  "    ) {\n"
  "\n"
  "      return null;\n"
  "    }\n"
  "\n"
  "\n"
  "    return fecha;\n"
  "  }\n"
  "\n"
  "\n"
  "  return null;\n"
  "}\n"
  "\n"
  "\n"
  "function calcularTiempoRestante(\n"
  "  fecha\n"
  ") {\n"
  "\n"
  "  const ahora =\n"
  "    new Date();\n"
  "\n"
  "\n"
  "  const diferencia =\n"
  "    fecha -\n"
  "    ahora;\n"
  "\n"
  "\n"
  "  const minutosTotales =\n"
  "    Math.max(\n"
  "      1,\n"
  "      Math.ceil(\n"
  "        diferencia /\n"
  "        60000\n"
  "      )\n"
  "    );\n"
  "\n"
  "\n"
  "  const dias =\n"
  "    Math.floor(\n"
  "      minutosTotales /\n"
  "      1440\n"
  "    );\n"
  "\n"
  "\n"
  "  const resto =\n"
  "    minutosTotales %\n"
  "    1440;\n"
  "\n"
  "\n"
  "  const horas =\n"
  "    Math.floor(\n"
  "      resto /\n"
  "      60\n"
  "    );\n"
  "\n"
  "\n"
  "  const minutos =\n"
  "    resto %\n"
  "    60;\n"
  "\n"
  "\n"
  "  let texto = \"\";\n"
  "\n"
  "\n"
  "  if (\n"
  "    dias > 0\n"
  "  ) {\n"
  "\n"
  "    texto +=\n"
  "\n"
  "      dias +\n"
  "\n"
  "      (\n"
  "        dias === 1\n"
  "          ? \" día\"\n"
  "          : \" días\"\n"
  "      );\n"
  "  }\n"
  "\n"
  "\n"
  "  if (\n"
  "    dias > 0 &&\n"
  "    horas > 0\n"
  "  ) {\n"
  "\n"
  "    texto +=\n"
  "      \" y \";\n"
  "  }\n"
  "\n"
  "\n"
  "  if (\n"
  "    horas > 0\n"
  "  ) {\n"
  "\n"
  "    texto +=\n"
  "\n"
  "      horas +\n"
  "\n"
  "      (\n"
  "        horas === 1\n"
  "          ? \" hora\"\n"
  "          : \" horas\"\n"
  "      );\n"
  "  }\n"
  "\n"
  "\n"
  "  if (\n"
  "    (dias > 0 || horas > 0) &&\n"
  "    minutos > 0\n"
  "  ) {\n"
  "\n"
  "    texto +=\n"
  "      \" y \";\n"
  "  }\n"
  "\n"
  "\n"
  "  if (\n"
  "    minutos > 0\n"
  "  ) {\n"
  "\n"
  "    texto +=\n"
  "\n"
  "      minutos +\n"
  "\n"
  "      (\n"
  "        minutos === 1\n"
  "          ? \" minuto\"\n"
  "          : \" minutos\"\n"
  "      );\n"
  "  }\n"
  "\n"
  "\n"
  "  return texto;\n"
  "}\n"
  "\n"
  "\n"
  "function descripcionRepeticion(\n"
  "  alarma\n"
  ") {\n"
  "\n"
  "  if (\n"
  "    alarma.repeat === 0\n"
  "  ) {\n"
  "\n"
  "    return (\n"
  "\n"
  "      \"Una vez · \" +\n"
  "\n"
  "      dos(\n"
  "        alarma.day\n"
  "      ) +\n"
  "\n"
  "      \"/\" +\n"
  "\n"
  "      dos(\n"
  "        alarma.month\n"
  "      ) +\n"
  "\n"
  "      \"/\" +\n"
  "\n"
  "      alarma.year\n"
  "    );\n"
  "  }\n"
  "\n"
  "\n"
  "  if (\n"
  "    alarma.repeat === 1\n"
  "  ) {\n"
  "\n"
  "    return \"Todos los días\";\n"
  "  }\n"
  "\n"
  "\n"
  "  if (\n"
  "    alarma.repeat === 2\n"
  "  ) {\n"
  "\n"
  "    const dias = [];\n"
  "\n"
  "\n"
  "    for (\n"
  "      let i = 1;\n"
  "      i <= 6;\n"
  "      i++\n"
  "    ) {\n"
  "\n"
  "      if (\n"
  "        alarma.days &\n"
  "        (\n"
  "          1 << i\n"
  "        )\n"
  "      ) {\n"
  "\n"
  "        dias.push(\n"
  "          nombresDias[i]\n"
  "        );\n"
  "      }\n"
  "    }\n"
  "\n"
  "\n"
  "    if (\n"
  "      alarma.days &\n"
  "      1\n"
  "    ) {\n"
  "\n"
  "      dias.push(\n"
  "        \"Dom\"\n"
  "      );\n"
  "    }\n"
  "\n"
  "\n"
  "    return dias.join(\n"
  "      \", \"\n"
  "    );\n"
  "  }\n"
  "\n"
  "\n"
  "  if (\n"
  "    alarma.repeat === 3\n"
  "  ) {\n"
  "\n"
  "    return (\n"
  "\n"
  "      \"Fecha: \" +\n"
  "\n"
  "      dos(\n"
  "        alarma.day\n"
  "      ) +\n"
  "\n"
  "      \"/\" +\n"
  "\n"
  "      dos(\n"
  "        alarma.month\n"
  "      ) +\n"
  "\n"
  "      \"/\" +\n"
  "\n"
  "      alarma.year\n"
  "    );\n"
  "  }\n"
  "\n"
  "\n"
  "  return \"\";\n"
  "}\n"
  "\n"
  "\n"
  "async function sincronizarHora() {\n"
  "\n"
  "  const ahora =\n"
  "    new Date();\n"
  "\n"
  "\n"
  "  try {\n"
  "\n"
  "    await fetch(\n"
  "\n"
  "      \"/api/sync-time\" +\n"
  "\n"
  "      \"?epoch=\" +\n"
  "      Date.now() +\n"
  "\n"
  "      \"&offset=\" +\n"
  "      ahora.getTimezoneOffset(),\n"
  "\n"
  "      {\n"
  "        method: \"POST\"\n"
  "      }\n"
  "\n"
  "    );\n"
  "\n"
  "  }\n"
  "\n"
  "  catch (error) {\n"
  "  }\n"
  "}\n"
  "\n"
  "\n"
  "function nuevaAlarma() {\n"
  "\n"
  "  alarmaEditando =\n"
  "    -1;\n"
  "\n"
  "\n"
  "  document.getElementById(\n"
  "    \"tituloEditor\"\n"
  "  ).textContent =\n"
  "    \"Nueva alarma\";\n"
  "\n"
  "\n"
  "  const ahora =\n"
  "    new Date();\n"
  "\n"
  "\n"
  "  document.getElementById(\n"
  "    \"hora\"\n"
  "  ).value =\n"
  "\n"
  "    dos(\n"
  "      ahora.getHours()\n"
  "    ) +\n"
  "\n"
  "    \":\" +\n"
  "\n"
  "    dos(\n"
  "      ahora.getMinutes()\n"
  "    );\n"
  "\n"
  "\n"
  "  document.getElementById(\n"
  "    \"tono\"\n"
  "  ).value =\n"
  "    \"0\";\n"
  "\n"
  "\n"
  "  document.getElementById(\n"
  "    \"repeticion\"\n"
  "  ).value =\n"
  "    \"0\";\n"
  "\n"
  "\n"
  "  establecerMascaraDias(\n"
  "    0\n"
  "  );\n"
  "\n"
  "\n"
  "  const fechaInput =\n"
  "    document.getElementById(\n"
  "      \"fechaEspecifica\"\n"
  "    );\n"
  "\n"
  "\n"
  "  fechaInput.min =\n"
  "    fechaParaInput(\n"
  "      ahora\n"
  "    );\n"
  "\n"
  "\n"
  "  fechaInput.value =\n"
  "    fechaParaInput(\n"
  "      ahora\n"
  "    );\n"
  "\n"
  "\n"
  "  document.querySelector(\n"
  "    'input[name=\"modo\"][value=\"2\"]'\n"
  "  ).checked =\n"
  "    true;\n"
  "\n"
  "\n"
  "  actualizarOpcionesRepeticion();\n"
  "\n"
  "\n"
  "  abrirEditor();\n"
  "}\n"
  "\n"
  "\n"
  "function abrirEditor() {\n"
  "\n"
  "  document.getElementById(\n"
  "    \"pantallaPrincipal\"\n"
  "  ).style.display =\n"
  "    \"none\";\n"
  "\n"
  "\n"
  "  document.getElementById(\n"
  "    \"editor\"\n"
  "  ).classList.add(\n"
  "    \"visible\"\n"
  "  );\n"
  "}\n"
  "\n"
  "\n"
  "function cerrarEditor() {\n"
  "\n"
  "  document.getElementById(\n"
  "    \"pantallaPrincipal\"\n"
  "  ).style.display =\n"
  "    \"block\";\n"
  "\n"
  "\n"
  "  document.getElementById(\n"
  "    \"editor\"\n"
  "  ).classList.remove(\n"
  "    \"visible\"\n"
  "  );\n"
  "}\n"
  "\n"
  "\n"
  "async function guardarAlarma() {\n"
  "\n"
  "  const horaTexto =\n"
  "    document.getElementById(\n"
  "      \"hora\"\n"
  "    ).value;\n"
  "\n"
  "\n"
  "  if (\n"
  "    !horaTexto\n"
  "  ) {\n"
  "\n"
  "    mostrarAviso(\n"
  "      \"Elige una hora\"\n"
  "    );\n"
  "\n"
  "    return;\n"
  "  }\n"
  "\n"
  "\n"
  "  const partes =\n"
  "    horaTexto.split(\n"
  "      \":\"\n"
  "    );\n"
  "\n"
  "\n"
  "  const hora =\n"
  "    Number(\n"
  "      partes[0]\n"
  "    );\n"
  "\n"
  "\n"
  "  const minuto =\n"
  "    Number(\n"
  "      partes[1]\n"
  "    );\n"
  "\n"
  "\n"
  "  const tono =\n"
  "    Number(\n"
  "      document.getElementById(\n"
  "        \"tono\"\n"
  "      ).value\n"
  "    );\n"
  "\n"
  "\n"
  "  const modo =\n"
  "    Number(\n"
  "      document.querySelector(\n"
  "        'input[name=\"modo\"]:checked'\n"
  "      ).value\n"
  "    );\n"
  "\n"
  "\n"
  "  const repeticion =\n"
  "    Number(\n"
  "      document.getElementById(\n"
  "        \"repeticion\"\n"
  "      ).value\n"
  "    );\n"
  "\n"
  "\n"
  "  const dias =\n"
  "    obtenerMascaraDias();\n"
  "\n"
  "\n"
  "  const fechaTexto =\n"
  "    document.getElementById(\n"
  "      \"fechaEspecifica\"\n"
  "    ).value;\n"
  "\n"
  "\n"
  "  if (\n"
  "    repeticion === 2 &&\n"
  "    dias === 0\n"
  "  ) {\n"
  "\n"
  "    mostrarAviso(\n"
  "      \"Elige al menos un día\"\n"
  "    );\n"
  "\n"
  "    return;\n"
  "  }\n"
  "\n"
  "\n"
  "  const proxima =\n"
  "    calcularProximaFecha(\n"
  "\n"
  "      hora,\n"
  "\n"
  "      minuto,\n"
  "\n"
  "      repeticion,\n"
  "\n"
  "      dias,\n"
  "\n"
  "      fechaTexto\n"
  "    );\n"
  "\n"
  "\n"
  "  if (\n"
  "    !proxima\n"
  "  ) {\n"
  "\n"
  "    mostrarAviso(\n"
  "      \"Esa fecha u hora ya pasó\"\n"
  "    );\n"
  "\n"
  "    return;\n"
  "  }\n"
  "\n"
  "\n"
  "  let anio = 0;\n"
  "  let mes = 0;\n"
  "  let dia = 0;\n"
  "\n"
  "\n"
  "  if (\n"
  "    repeticion === 0 ||\n"
  "    repeticion === 3\n"
  "  ) {\n"
  "\n"
  "    anio =\n"
  "      proxima.getFullYear();\n"
  "\n"
  "\n"
  "    mes =\n"
  "      proxima.getMonth() + 1;\n"
  "\n"
  "\n"
  "    dia =\n"
  "      proxima.getDate();\n"
  "  }\n"
  "\n"
  "\n"
  "  const activa =\n"
  "\n"
  "    alarmaEditando >= 0\n"
  "\n"
  "      ? alarmas[\n"
  "          alarmaEditando\n"
  "        ].active\n"
  "\n"
  "      : true;\n"
  "\n"
  "\n"
  "  const direccion =\n"
  "\n"
  "    \"/api/save\" +\n"
  "\n"
  "    \"?index=\" +\n"
  "    alarmaEditando +\n"
  "\n"
  "    \"&hour=\" +\n"
  "    hora +\n"
  "\n"
  "    \"&minute=\" +\n"
  "    minuto +\n"
  "\n"
  "    \"&tone=\" +\n"
  "    tono +\n"
  "\n"
  "    \"&mode=\" +\n"
  "    modo +\n"
  "\n"
  "    \"&repeat=\" +\n"
  "    repeticion +\n"
  "\n"
  "    \"&days=\" +\n"
  "    dias +\n"
  "\n"
  "    \"&year=\" +\n"
  "    anio +\n"
  "\n"
  "    \"&month=\" +\n"
  "    mes +\n"
  "\n"
  "    \"&day=\" +\n"
  "    dia +\n"
  "\n"
  "    \"&active=\" +\n"
  "    (\n"
  "      activa\n"
  "        ? 1\n"
  "        : 0\n"
  "    );\n"
  "\n"
  "\n"
  "  try {\n"
  "\n"
  "    const respuesta =\n"
  "      await fetch(\n"
  "\n"
  "        direccion,\n"
  "\n"
  "        {\n"
  "          method: \"POST\"\n"
  "        }\n"
  "\n"
  "      );\n"
  "\n"
  "\n"
  "    if (\n"
  "      !respuesta.ok\n"
  "    ) {\n"
  "\n"
  "      alert(\n"
  "        await respuesta.text()\n"
  "      );\n"
  "\n"
  "      return;\n"
  "    }\n"
  "\n"
  "\n"
  "    await cargarAlarmas();\n"
  "\n"
  "\n"
  "    cerrarEditor();\n"
  "\n"
  "\n"
  "    mostrarAviso(\n"
  "\n"
  "      \"La alarma sonará en \" +\n"
  "\n"
  "      calcularTiempoRestante(\n"
  "        proxima\n"
  "      )\n"
  "\n"
  "    );\n"
  "\n"
  "  }\n"
  "\n"
  "  catch (error) {\n"
  "\n"
  "    alert(\n"
  "      \"No se pudo guardar la alarma\"\n"
  "    );\n"
  "  }\n"
  "}\n"
  "\n"
  "\n"
  "async function cargarAlarmas() {\n"
  "\n"
  "  try {\n"
  "\n"
  "    const respuesta =\n"
  "      await fetch(\n"
  "\n"
  "        \"/api/alarms\",\n"
  "\n"
  "        {\n"
  "          cache: \"no-store\"\n"
  "        }\n"
  "\n"
  "      );\n"
  "\n"
  "\n"
  "    alarmas =\n"
  "      await respuesta.json();\n"
  "\n"
  "\n"
  "    mostrarAlarmas();\n"
  "\n"
  "  }\n"
  "\n"
  "  catch (error) {\n"
  "  }\n"
  "}\n"
  "\n"
  "\n"
  "function mostrarAlarmas() {\n"
  "\n"
  "  const lista =\n"
  "    document.getElementById(\n"
  "      \"listaAlarmas\"\n"
  "    );\n"
  "\n"
  "\n"
  "  lista.innerHTML =\n"
  "    \"\";\n"
  "\n"
  "\n"
  "  if (\n"
  "    alarmas.length === 0\n"
  "  ) {\n"
  "\n"
  "    lista.innerHTML =\n"
  "      '<div class=\"vacio\">No hay alarmas configuradas</div>';\n"
  "\n"
  "    return;\n"
  "  }\n"
  "\n"
  "\n"
  "  alarmas.forEach(\n"
  "\n"
  "    function(\n"
  "      alarma,\n"
  "      indice\n"
  "    ) {\n"
  "\n"
  "      const tarjeta =\n"
  "        document.createElement(\n"
  "          \"div\"\n"
  "        );\n"
  "\n"
  "\n"
  "      tarjeta.className =\n"
  "        \"alarma\";\n"
  "\n"
  "\n"
  "      tarjeta.innerHTML = `\n"
  "\n"
  "      <div class=\"alarma-superior\">\n"
  "\n"
  "        <div class=\"hora\">\n"
  "\n"
  "          ${dos(alarma.hour)}:${dos(alarma.minute)}\n"
  "\n"
  "        </div>\n"
  "\n"
  "\n"
  "        <label class=\"interruptor\">\n"
  "\n"
  "          <input\n"
  "            type=\"checkbox\"\n"
  "\n"
  "            ${\n"
  "              alarma.active\n"
  "                ? \"checked\"\n"
  "                : \"\"\n"
  "            }\n"
  "\n"
  "            onchange=\"\n"
  "              cambiarEstado(\n"
  "                ${indice},\n"
  "                this.checked\n"
  "              )\n"
  "            \">\n"
  "\n"
  "          <span class=\"slider\">\n"
  "          </span>\n"
  "\n"
  "        </label>\n"
  "\n"
  "      </div>\n"
  "\n"
  "\n"
  "      <div class=\"detalle\">\n"
  "\n"
  "        ${nombresTonos[alarma.tone]}\n"
  "\n"
  "        <br>\n"
  "\n"
  "        ${nombresModos[alarma.mode]}\n"
  "\n"
  "        <br>\n"
  "\n"
  "        ${descripcionRepeticion(alarma)}\n"
  "\n"
  "      </div>\n"
  "\n"
  "\n"
  "      <div class=\"acciones\">\n"
  "\n"
  "        <button\n"
  "          class=\"editar\"\n"
  "          onclick=\"editarAlarma(${indice})\">\n"
  "\n"
  "          Editar\n"
  "\n"
  "        </button>\n"
  "\n"
  "\n"
  "        <button\n"
  "          class=\"eliminar\"\n"
  "          onclick=\"eliminarAlarma(${indice})\">\n"
  "\n"
  "          Eliminar\n"
  "\n"
  "        </button>\n"
  "\n"
  "      </div>\n"
  "\n"
  "      `;\n"
  "\n"
  "\n"
  "      lista.appendChild(\n"
  "        tarjeta\n"
  "      );\n"
  "    }\n"
  "  );\n"
  "}\n"
  "\n"
  "\n"
  "function editarAlarma(\n"
  "  indice\n"
  ") {\n"
  "\n"
  "  alarmaEditando =\n"
  "    indice;\n"
  "\n"
  "\n"
  "  const alarma =\n"
  "    alarmas[indice];\n"
  "\n"
  "\n"
  "  document.getElementById(\n"
  "    \"tituloEditor\"\n"
  "  ).textContent =\n"
  "    \"Editar alarma\";\n"
  "\n"
  "\n"
  "  document.getElementById(\n"
  "    \"hora\"\n"
  "  ).value =\n"
  "\n"
  "    dos(\n"
  "      alarma.hour\n"
  "    )\n"
  "\n"
  "    + \":\" +\n"
  "\n"
  "    dos(\n"
  "      alarma.minute\n"
  "    );\n"
  "\n"
  "\n"
  "  document.getElementById(\n"
  "    \"tono\"\n"
  "  ).value =\n"
  "    String(\n"
  "      alarma.tone\n"
  "    );\n"
  "\n"
  "\n"
  "  document.getElementById(\n"
  "    \"repeticion\"\n"
  "  ).value =\n"
  "    String(\n"
  "      alarma.repeat\n"
  "    );\n"
  "\n"
  "\n"
  "  establecerMascaraDias(\n"
  "    alarma.days\n"
  "  );\n"
  "\n"
  "\n"
  "  const fechaInput =\n"
  "    document.getElementById(\n"
  "      \"fechaEspecifica\"\n"
  "    );\n"
  "\n"
  "\n"
  "  fechaInput.min =\n"
  "    fechaParaInput(\n"
  "      new Date()\n"
  "    );\n"
  "\n"
  "\n"
  "  if (\n"
  "    alarma.year > 0\n"
  "  ) {\n"
  "\n"
  "    fechaInput.value =\n"
  "\n"
  "      alarma.year +\n"
  "\n"
  "      \"-\" +\n"
  "\n"
  "      dos(\n"
  "        alarma.month\n"
  "      ) +\n"
  "\n"
  "      \"-\" +\n"
  "\n"
  "      dos(\n"
  "        alarma.day\n"
  "      );\n"
  "  }\n"
  "\n"
  "\n"
  "  document.querySelector(\n"
  "\n"
  "    'input[name=\"modo\"][value=\"' +\n"
  "\n"
  "    alarma.mode +\n"
  "\n"
  "    '\"]'\n"
  "\n"
  "  ).checked =\n"
  "    true;\n"
  "\n"
  "\n"
  "  actualizarOpcionesRepeticion();\n"
  "\n"
  "\n"
  "  abrirEditor();\n"
  "}\n"
  "\n"
  "\n"
  "async function cambiarEstado(\n"
  "  indice,\n"
  "  estado\n"
  ") {\n"
  "\n"
  "  await fetch(\n"
  "\n"
  "    \"/api/toggle\" +\n"
  "\n"
  "    \"?index=\" +\n"
  "    indice +\n"
  "\n"
  "    \"&active=\" +\n"
  "    (\n"
  "      estado\n"
  "        ? 1\n"
  "        : 0\n"
  "    ),\n"
  "\n"
  "    {\n"
  "      method: \"POST\"\n"
  "    }\n"
  "\n"
  "  );\n"
  "\n"
  "\n"
  "  await cargarAlarmas();\n"
  "\n"
  "  await actualizarEstado();\n"
  "}\n"
  "\n"
  "\n"
  "async function eliminarAlarma(\n"
  "  indice\n"
  ") {\n"
  "\n"
  "  await fetch(\n"
  "\n"
  "    \"/api/delete\" +\n"
  "\n"
  "    \"?index=\" +\n"
  "    indice,\n"
  "\n"
  "    {\n"
  "      method: \"POST\"\n"
  "    }\n"
  "\n"
  "  );\n"
  "\n"
  "\n"
  "  await cargarAlarmas();\n"
  "\n"
  "  await actualizarEstado();\n"
  "}\n"
  "\n"
  "\n"
  "async function detenerAlarma() {\n"
  "\n"
  "  await fetch(\n"
  "\n"
  "    \"/api/stop\",\n"
  "\n"
  "    {\n"
  "      method: \"POST\"\n"
  "    }\n"
  "\n"
  "  );\n"
  "\n"
  "\n"
  "  await actualizarEstado();\n"
  "\n"
  "  await cargarAlarmas();\n"
  "\n"
  "\n"
  "  mostrarAviso(\n"
  "    \"Alarma detenida\"\n"
  "  );\n"
  "}\n"
  "\n"
  "\n"
  "async function actualizarEstado() {\n"
  "\n"
  "  try {\n"
  "\n"
  "    const respuesta =\n"
  "      await fetch(\n"
  "\n"
  "        \"/api/status\",\n"
  "\n"
  "        {\n"
  "          cache: \"no-store\"\n"
  "        }\n"
  "\n"
  "      );\n"
  "\n"
  "\n"
  "    const estado =\n"
  "      await respuesta.json();\n"
  "\n"
  "\n"
  "    const elementoHora =\n"
  "      document.getElementById(\n"
  "        \"estadoHora\"\n"
  "      );\n"
  "\n"
  "\n"
  "    if (\n"
  "      estado.synced\n"
  "    ) {\n"
  "\n"
  "      elementoHora.textContent =\n"
  "\n"
  "        \"Hora sincronizada: \" +\n"
  "\n"
  "        dos(\n"
  "          estado.hour\n"
  "        )\n"
  "\n"
  "        + \":\" +\n"
  "\n"
  "        dos(\n"
  "          estado.minute\n"
  "        )\n"
  "\n"
  "        + \":\" +\n"
  "\n"
  "        dos(\n"
  "          estado.second\n"
  "        );\n"
  "\n"
  "    }\n"
  "\n"
  "    else {\n"
  "\n"
  "      elementoHora.textContent =\n"
  "        \"Hora no sincronizada\";\n"
  "    }\n"
  "\n"
  "\n"
  "    const evento =\n"
  "      document.getElementById(\n"
  "        \"ultimoEvento\"\n"
  "      );\n"
  "\n"
  "\n"
  "    if (\n"
  "      estado.event\n"
  "    ) {\n"
  "\n"
  "      evento.style.display =\n"
  "        \"block\";\n"
  "\n"
  "\n"
  "      evento.textContent =\n"
  "        estado.event;\n"
  "\n"
  "    }\n"
  "\n"
  "    else {\n"
  "\n"
  "      evento.style.display =\n"
  "        \"none\";\n"
  "    }\n"
  "\n"
  "\n"
  "    const boton =\n"
  "      document.getElementById(\n"
  "        \"botonDetener\"\n"
  "      );\n"
  "\n"
  "\n"
  "    if (\n"
  "      estado.ringing\n"
  "    ) {\n"
  "\n"
  "      boton.classList.add(\n"
  "        \"visible\"\n"
  "      );\n"
  "\n"
  "    }\n"
  "\n"
  "    else {\n"
  "\n"
  "      boton.classList.remove(\n"
  "        \"visible\"\n"
  "      );\n"
  "    }\n"
  "\n"
  "\n"
  "    if (\n"
  "      estado.ringing !==\n"
  "      estabaSonando\n"
  "    ) {\n"
  "\n"
  "      estabaSonando =\n"
  "        estado.ringing;\n"
  "\n"
  "\n"
  "      await cargarAlarmas();\n"
  "    }\n"
  "\n"
  "  }\n"
  "\n"
  "  catch (error) {\n"
  "  }\n"
  "}\n"
  "\n"
  "\n"
  "async function iniciar() {\n"
  "\n"
  "  await sincronizarHora();\n"
  "\n"
  "  await cargarAlarmas();\n"
  "\n"
  "  await actualizarEstado();\n"
  "\n"
  "\n"
  "  setInterval(\n"
  "    actualizarEstado,\n"
  "    500\n"
  "  );\n"
  "}\n"
  "\n"
  "\n"
  "iniciar();\n"
  "\n"
  "</script>\n"
  "\n"
  "</body>\n"
  "</html>\n";


// =====================================================
// FECHAS
// =====================================================

void fechaDesdeDias(
  int64_t z,
  int& anio,
  unsigned& mes,
  unsigned& dia
) {

  z +=
    719468;


  const int64_t era =

    (
      z >= 0
        ? z
        : z - 146096
    )
    /
    146097;


  const unsigned doe =

    (unsigned)(
      z -
      era * 146097
    );


  const unsigned yoe =

    (
      doe -
      doe / 1460 +
      doe / 36524 -
      doe / 146096
    )
    /
    365;


  anio =

    (int)yoe +

    (int)(
      era * 400
    );


  const unsigned doy =

    doe -

    (
      365 * yoe +

      yoe / 4 -

      yoe / 100
    );


  const unsigned mp =

    (
      5 * doy +
      2
    )
    /
    153;


  dia =

    doy -

    (
      153 * mp +
      2
    )
    /
    5

    +
    1;


  mes =

    mp +

    (
      mp < 10
        ? 3
        : -9
    );


  anio +=
    mes <= 2;
}

// =====================================================
// MEMORIA
// =====================================================

void guardarAlarmasEnMemoria() {

  memoria.begin(
    "alarmas",
    false
  );


  memoria.putUChar(
    "cantidad",
    cantidadAlarmas
  );


  memoria.putBytes(
    "datos",
    alarmas,
    sizeof(alarmas)
  );


  memoria.end();
}


void cargarAlarmasDeMemoria() {

  bool migrarViejas =
    false;


  memoria.begin(
    "alarmas",
    true
  );


  cantidadAlarmas =
    memoria.getUChar(
      "cantidad",
      0
    );


  if (
    cantidadAlarmas >
    MAX_ALARMAS
  ) {

    cantidadAlarmas =
      0;
  }


  size_t tamano =
    memoria.getBytesLength(
      "datos"
    );


  if (
    tamano ==
    sizeof(alarmas)
  ) {

    memoria.getBytes(
      "datos",
      alarmas,
      sizeof(alarmas)
    );
  }

  else if (
    tamano ==
    sizeof(AlarmaVieja) *
    MAX_ALARMAS
  ) {

    AlarmaVieja viejas[
      MAX_ALARMAS
    ];


    memoria.getBytes(
      "datos",
      viejas,
      sizeof(viejas)
    );


    for (
      int i = 0;
      i < cantidadAlarmas;
      i++
    ) {

      alarmas[i].hora =
        viejas[i].hora;


      alarmas[i].minuto =
        viejas[i].minuto;


      alarmas[i].tono =
        viejas[i].tono;


      alarmas[i].modo =
        viejas[i].modo;


      alarmas[i].activa =
        viejas[i].activa;


      alarmas[i].repeticion =
        1;


      alarmas[i].diasSemana =
        0;


      alarmas[i].anio =
        0;


      alarmas[i].mes =
        0;


      alarmas[i].dia =
        0;
    }


    migrarViejas =
      true;
  }

  else {

    cantidadAlarmas =
      0;
  }


  memoria.end();


  for (
    int i = 0;
    i < MAX_ALARMAS;
    i++
  ) {

    ultimoDiaActivado[i] =
      -1;
  }


  if (
    migrarViejas
  ) {

    guardarAlarmasEnMemoria();
  }
}

// =====================================================
// HORA
// =====================================================

int64_t obtenerHoraLocal() {

  if (
    !horaSincronizada
  ) {

    return 0;
  }


  uint32_t transcurrido =

    millis() -
    millisSincronizacion;


  return

    horaLocalSincronizada +

    (
      transcurrido /
      1000
    );
}

// =====================================================
// JSON
// =====================================================

String crearJsonAlarmas() {

  String json =
    "[";


  for (
    int i = 0;
    i < cantidadAlarmas;
    i++
  ) {

    if (
      i > 0
    ) {

      json += ",";
    }


    json += "{";


    json += "\"hour\":";
    json += alarmas[i].hora;


    json += ",\"minute\":";
    json += alarmas[i].minuto;


    json += ",\"tone\":";
    json += alarmas[i].tono;


    json += ",\"mode\":";
    json += alarmas[i].modo;


    json += ",\"repeat\":";
    json += alarmas[i].repeticion;


    json += ",\"days\":";
    json += alarmas[i].diasSemana;


    json += ",\"year\":";
    json += alarmas[i].anio;


    json += ",\"month\":";
    json += alarmas[i].mes;


    json += ",\"day\":";
    json += alarmas[i].dia;


    json += ",\"active\":";

    json +=

      alarmas[i].activa

        ? "true"

        : "false";


    json += "}";
  }


  json += "]";


  return json;
}

// =====================================================
// MUSICA
// =====================================================

int cantidadNotasTono(
  uint8_t tono
) {

  switch (tono) {

    case 0:
      return homecomingCantidad;

    case 1:
      return quantumCantidad;

    case 2:
      return spaceCantidad;

    case 3:
      return megalovaniaCantidad;

    case 4:
      return neverGonnaCantidad;

    case 5:
      return takeOnMeCantidad;
  }


  return 0;
}


int frecuenciaTono(
  uint8_t tono,
  int indice
) {

  switch (tono) {

    case 0:
      return homecomingNotas[
        indice
      ];

    case 1:
      return quantumNotas[
        indice
      ];

    case 2:
      return spaceNotas[
        indice
      ];

    case 3:
      return megalovaniaNotas[
        indice
      ];

    case 4:
      return neverGonnaNotas[
        indice
      ];

    case 5:
      return takeOnMeNotas[
        indice
      ];
  }


  return 0;
}


int duracionTono(
  uint8_t tono,
  int indice
) {

  switch (tono) {

    case 0:
      return homecomingDuraciones[
        indice
      ];

    case 1:
      return quantumDuraciones[
        indice
      ];

    case 2:
      return spaceDuraciones[
        indice
      ];

    case 3:
      return megalovaniaDuraciones[
        indice
      ];

    case 4:
      return neverGonnaDuraciones[
        indice
      ];

    case 5:
      return takeOnMeDuraciones[
        indice
      ];
  }


  return 200;
}

// =====================================================
// SALIDAS: SONIDO + VIBRACION
//
// modo:
// 0 = solo sonido
// 1 = solo vibracion
// 2 = sonido + vibracion
//
// El motor no produce notas musicales.
// Para representar la melodia, vibra durante cada nota
// y se apaga durante las pausas, usando exactamente
// las mismas duraciones que la cancion.
// =====================================================

void apagarSalidas() {

  ledcWriteTone(
    BUZZER,
    0
  );

  digitalWrite(
    MOTOR_VIBRACION,
    LOW
  );
}


void reproducirNotaActual(
  uint8_t tono,
  int indice,
  uint8_t modo
) {

  int frecuencia =
    frecuenciaTono(
      tono,
      indice
    );


  // -----------------------------
  // BUZZER
  // -----------------------------

  if (
    modo != 1 &&
    frecuencia > 0
  ) {

    ledcWriteTone(
      BUZZER,
      frecuencia
    );
  }

  else {

    ledcWriteTone(
      BUZZER,
      0
    );
  }


  // -----------------------------
  // MOTOR
  // -----------------------------
  //
  // HIGH = vibracion fuerte.
  // Si la melodia contiene una pausa real (frecuencia 0),
  // el motor tambien queda apagado durante esa pausa.

  if (
    modo != 0 &&
    frecuencia > 0
  ) {

    digitalWrite(
      MOTOR_VIBRACION,
      HIGH
    );
  }

  else {

    digitalWrite(
      MOTOR_VIBRACION,
      LOW
    );
  }
}


// =====================================================
// DETENER
// =====================================================

void detenerAlarmaActual() {

  musicaActiva =
    false;


  apagarSalidas();


  if (
    alarmaSonandoIndice >= 0
  ) {

    ultimoEvento =
      "Alarma detenida";
  }


  alarmaSonandoIndice =
    -1;


  notaActual =
    0;


  pausaEntreNotas =
    false;
}

// =====================================================
// INICIAR ALARMA
// =====================================================

void iniciarAlarma(
  int indice
) {

  if (
    indice < 0 ||
    indice >= cantidadAlarmas
  ) {

    return;
  }


  alarmaSonandoIndice =
    indice;


  ultimoEvento =

    "Alarma activada: " +

    nombreTono(
      alarmas[indice].tono
    )

    + " - " +

    nombreModo(
      alarmas[indice].modo
    );


  Serial.println(
    ultimoEvento
  );


  musicaActiva =
    true;


  notaActual =
    0;


  pausaEntreNotas =
    false;


  uint8_t tono =
    alarmas[indice].tono;


  reproducirNotaActual(

    tono,

    notaActual,

    alarmas[indice].modo

  );


  siguienteCambioMusica =

    millis() +

    duracionTono(
      tono,
      notaActual
    );
}

// =====================================================
// ACTUALIZAR MUSICA
// =====================================================

void actualizarMusica() {

  if (
    !musicaActiva ||
    alarmaSonandoIndice < 0
  ) {

    return;
  }


  if (
    alarmaSonandoIndice >=
    cantidadAlarmas
  ) {

    detenerAlarmaActual();

    return;
  }


  unsigned long ahora =
    millis();


  if (

    (long)(
      ahora -
      siguienteCambioMusica
    )

    < 0

  ) {

    return;
  }


  uint8_t tono =

    alarmas[
      alarmaSonandoIndice
    ].tono;


  if (
    !pausaEntreNotas
  ) {

    apagarSalidas();


    pausaEntreNotas =
      true;


    siguienteCambioMusica =
      ahora +
      40;
  }

  else {

    notaActual++;


    int cantidad =
      cantidadNotasTono(
        tono
      );


    // Al llegar al final,
    // vuelve al inicio de la parte reconocible.

    if (
      notaActual >=
      cantidad
    ) {

      notaActual =
        0;
    }


    reproducirNotaActual(

      tono,

      notaActual,

      alarmas[
        alarmaSonandoIndice
      ].modo

    );


    pausaEntreNotas =
      false;


    siguienteCambioMusica =

      ahora +

      duracionTono(
        tono,
        notaActual
      );
  }
}

// =====================================================
// FECHA
// =====================================================

bool correspondeFecha(
  const Alarma& alarma,
  int anio,
  unsigned mes,
  unsigned dia,
  int diaSemana
) {

  if (
    alarma.repeticion ==
    0
  ) {

    return

      alarma.anio ==
      anio

      &&

      alarma.mes ==
      mes

      &&

      alarma.dia ==
      dia;
  }


  if (
    alarma.repeticion ==
    1
  ) {

    return true;
  }


  if (
    alarma.repeticion ==
    2
  ) {

    return

      (
        alarma.diasSemana &

        (
          1 <<
          diaSemana
        )
      )

      != 0;
  }


  if (
    alarma.repeticion ==
    3
  ) {

    return

      alarma.anio ==
      anio

      &&

      alarma.mes ==
      mes

      &&

      alarma.dia ==
      dia;
  }


  return false;
}

// =====================================================
// COMPROBAR ALARMAS
// =====================================================

void comprobarAlarmas() {

  if (
    !horaSincronizada
  ) {

    return;
  }


  if (
    alarmaSonandoIndice >= 0
  ) {

    return;
  }


  int64_t ahora =
    obtenerHoraLocal();


  int segundosDia =
    ahora %
    86400;


  if (
    segundosDia < 0
  ) {

    segundosDia +=
      86400;
  }


  int64_t numeroDia =

    (
      ahora -
      segundosDia
    )
    /
    86400;


  int horaActual =
    segundosDia /
    3600;


  int minutoActual =

    (
      segundosDia %
      3600
    )
    /
    60;


  int anioActual;

  unsigned mesActual;
  unsigned diaActual;


  fechaDesdeDias(

    numeroDia,

    anioActual,

    mesActual,

    diaActual
  );


  int diaSemana =

    (
      (
        numeroDia +
        4
      )
      %
      7
      +
      7
    )
    %
    7;


  for (
    int i = 0;
    i < cantidadAlarmas;
    i++
  ) {

    if (
      !alarmas[i].activa
    ) {

      continue;
    }


    if (

      alarmas[i].hora !=
      horaActual

      ||

      alarmas[i].minuto !=
      minutoActual

    ) {

      continue;
    }


    if (
      !correspondeFecha(

        alarmas[i],

        anioActual,

        mesActual,

        diaActual,

        diaSemana
      )
    ) {

      continue;
    }


    if (
      ultimoDiaActivado[i] ==
      numeroDia
    ) {

      continue;
    }


    ultimoDiaActivado[i] =
      numeroDia;


    iniciarAlarma(
      i
    );


    if (

      alarmas[i].repeticion ==
      0

      ||

      alarmas[i].repeticion ==
      3

    ) {

      alarmas[i].activa =
        false;


      guardarAlarmasEnMemoria();
    }


    break;
  }
}

// =====================================================
// REPROGRAMAR UNA VEZ
// =====================================================

void reprogramarUnaVez(
  int indice
) {

  if (
    !horaSincronizada
  ) {

    return;
  }


  if (
    alarmas[indice].repeticion !=
    0
  ) {

    return;
  }


  int64_t ahora =
    obtenerHoraLocal();


  int segundosDia =
    ahora %
    86400;


  if (
    segundosDia < 0
  ) {

    segundosDia +=
      86400;
  }


  int64_t diaActual =

    (
      ahora -
      segundosDia
    )
    /
    86400;


  int segundosAlarma =

    alarmas[indice].hora *
    3600

    +

    alarmas[indice].minuto *
    60;


  int64_t diaObjetivo =
    diaActual;


  if (
    segundosAlarma <=
    segundosDia
  ) {

    diaObjetivo++;
  }


  int anio;

  unsigned mes;
  unsigned dia;


  fechaDesdeDias(

    diaObjetivo,

    anio,

    mes,

    dia
  );


  alarmas[indice].anio =
    anio;


  alarmas[indice].mes =
    mes;


  alarmas[indice].dia =
    dia;
}

// =====================================================
// WIFI
// =====================================================

void crearRedWifi() {

  WiFi.mode(
    WIFI_MODE_AP
  );


  WiFi.softAPConfig(
    ipLocal,
    ipGateway,
    mascara
  );


  WiFi.softAP(

    wifiNombre,

    wifiContrasena,

    CANAL_WIFI,

    0,

    MAX_CLIENTES
  );


  // Metodo que ya funciono con tu Samsung.

  esp_wifi_stop();

  esp_wifi_deinit();


  wifi_init_config_t configuracionWifi =
    WIFI_INIT_CONFIG_DEFAULT();


  configuracionWifi.ampdu_rx_enable =
    false;


  esp_wifi_init(
    &configuracionWifi
  );


  esp_wifi_start();


  delay(
    100
  );
}

// =====================================================
// SERVIDOR
// =====================================================

void configurarServidor() {

  // HORA

  server.on(

    "/api/sync-time",

    HTTP_POST,

    [](AsyncWebServerRequest* request) {

      if (

        !request->hasParam(
          "epoch"
        )

        ||

        !request->hasParam(
          "offset"
        )

      ) {

        request->send(
          400,
          "text/plain",
          "Error"
        );

        return;
      }


      int64_t epochMs =

        strtoll(

          request
          ->getParam(
            "epoch"
          )
          ->value()
          .c_str(),

          nullptr,

          10
        );


      int offsetMinutos =

        request
        ->getParam(
          "offset"
        )
        ->value()
        .toInt();


      horaLocalSincronizada =

        (
          epochMs /
          1000
        )

        -

        (
          (int64_t)
          offsetMinutos *
          60
        );


      millisSincronizacion =
        millis();


      horaSincronizada =
        true;


      request->send(
        200,
        "text/plain",
        "OK"
      );
    }
  );


  // LISTA

  server.on(

    "/api/alarms",

    HTTP_GET,

    [](AsyncWebServerRequest* request) {

      AsyncWebServerResponse*
        respuesta =

          request->beginResponse(

            200,

            "application/json",

            crearJsonAlarmas()
          );


      respuesta->addHeader(
        "Cache-Control",
        "no-store"
      );


      request->send(
        respuesta
      );
    }
  );


  // GUARDAR

  server.on(

    "/api/save",

    HTTP_POST,

    [](AsyncWebServerRequest* request) {

      const char* parametros[] = {

        "index",
        "hour",
        "minute",
        "tone",
        "mode",
        "repeat",
        "days",
        "year",
        "month",
        "day",
        "active"
      };


      for (
        int i = 0;
        i < 11;
        i++
      ) {

        if (
          !request->hasParam(
            parametros[i]
          )
        ) {

          request->send(
            400,
            "text/plain",
            "Faltan datos"
          );

          return;
        }
      }


      int indice =
        request->getParam(
          "index"
        )->value().toInt();


      int hora =
        request->getParam(
          "hour"
        )->value().toInt();


      int minuto =
        request->getParam(
          "minute"
        )->value().toInt();


      int tono =
        request->getParam(
          "tone"
        )->value().toInt();


      int modo =
        request->getParam(
          "mode"
        )->value().toInt();


      int repeticion =
        request->getParam(
          "repeat"
        )->value().toInt();


      int dias =
        request->getParam(
          "days"
        )->value().toInt();


      int anio =
        request->getParam(
          "year"
        )->value().toInt();


      int mes =
        request->getParam(
          "month"
        )->value().toInt();


      int dia =
        request->getParam(
          "day"
        )->value().toInt();


      bool activa =

        request->getParam(
          "active"
        )->value().toInt()

        == 1;


      if (
        indice == -1
      ) {

        if (
          cantidadAlarmas >=
          MAX_ALARMAS
        ) {

          request->send(
            400,
            "text/plain",
            "Máximo 10 alarmas"
          );

          return;
        }


        indice =
          cantidadAlarmas;


        cantidadAlarmas++;
      }

      else if (

        indice < 0 ||

        indice >=
        cantidadAlarmas

      ) {

        request->send(
          400,
          "text/plain",
          "Índice inválido"
        );

        return;
      }


      if (
        alarmaSonandoIndice ==
        indice
      ) {

        detenerAlarmaActual();
      }


      alarmas[indice].hora =
        hora;


      alarmas[indice].minuto =
        minuto;


      alarmas[indice].tono =
        tono;


      alarmas[indice].modo =
        modo;


      alarmas[indice].repeticion =
        repeticion;


      alarmas[indice].diasSemana =
        dias;


      alarmas[indice].anio =
        anio;


      alarmas[indice].mes =
        mes;


      alarmas[indice].dia =
        dia;


      alarmas[indice].activa =
        activa;


      ultimoDiaActivado[
        indice
      ] =
        -1;


      guardarAlarmasEnMemoria();


      request->send(
        200,
        "text/plain",
        "OK"
      );
    }
  );


  // ACTIVAR / DESACTIVAR

  server.on(

    "/api/toggle",

    HTTP_POST,

    [](AsyncWebServerRequest* request) {

      if (

        !request->hasParam(
          "index"
        )

        ||

        !request->hasParam(
          "active"
        )

      ) {

        request->send(
          400,
          "text/plain",
          "Error"
        );

        return;
      }


      int indice =

        request
        ->getParam(
          "index"
        )
        ->value()
        .toInt();


      bool activa =

        request
        ->getParam(
          "active"
        )
        ->value()
        .toInt()

        == 1;


      if (

        indice < 0 ||

        indice >=
        cantidadAlarmas

      ) {

        request->send(
          400,
          "text/plain",
          "Índice inválido"
        );

        return;
      }


      alarmas[indice].activa =
        activa;


      if (
        activa
      ) {

        ultimoDiaActivado[
          indice
        ] =
          -1;


        reprogramarUnaVez(
          indice
        );
      }


      if (

        !activa &&

        alarmaSonandoIndice ==
        indice

      ) {

        detenerAlarmaActual();
      }


      guardarAlarmasEnMemoria();


      request->send(
        200,
        "text/plain",
        "OK"
      );
    }
  );


  // ELIMINAR

  server.on(

    "/api/delete",

    HTTP_POST,

    [](AsyncWebServerRequest* request) {

      if (
        !request->hasParam(
          "index"
        )
      ) {

        request->send(
          400,
          "text/plain",
          "Error"
        );

        return;
      }


      int indice =

        request
        ->getParam(
          "index"
        )
        ->value()
        .toInt();


      if (

        indice < 0 ||

        indice >=
        cantidadAlarmas

      ) {

        request->send(
          400,
          "text/plain",
          "Índice inválido"
        );

        return;
      }


      if (
        alarmaSonandoIndice ==
        indice
      ) {

        detenerAlarmaActual();
      }

      else if (

        alarmaSonandoIndice >
        indice

      ) {

        alarmaSonandoIndice--;
      }


      for (

        int i = indice;

        i <
        cantidadAlarmas - 1;

        i++

      ) {

        alarmas[i] =
          alarmas[
            i + 1
          ];


        ultimoDiaActivado[i] =
          ultimoDiaActivado[
            i + 1
          ];
      }


      cantidadAlarmas--;


      guardarAlarmasEnMemoria();


      request->send(
        200,
        "text/plain",
        "OK"
      );
    }
  );


  // DETENER

  server.on(

    "/api/stop",

    HTTP_POST,

    [](AsyncWebServerRequest* request) {

      detenerAlarmaActual();


      request->send(
        200,
        "text/plain",
        "OK"
      );
    }
  );


  // ESTADO

  server.on(

    "/api/status",

    HTTP_GET,

    [](AsyncWebServerRequest* request) {

      String json =
        "{";


      json +=
        "\"synced\":";


      json +=

        horaSincronizada

          ? "true"

          : "false";


      if (
        horaSincronizada
      ) {

        int64_t ahora =
          obtenerHoraLocal();


        int segundosDia =
          ahora %
          86400;


        if (
          segundosDia < 0
        ) {

          segundosDia +=
            86400;
        }


        int hora =
          segundosDia /
          3600;


        int minuto =

          (
            segundosDia %
            3600
          )
          /
          60;


        int segundo =
          segundosDia %
          60;


        json +=
          ",\"hour\":";

        json +=
          hora;


        json +=
          ",\"minute\":";

        json +=
          minuto;


        json +=
          ",\"second\":";

        json +=
          segundo;
      }


      json +=
        ",\"ringing\":";


      json +=

        alarmaSonandoIndice >= 0

          ? "true"

          : "false";


      json +=
        ",\"event\":\"";


      json +=
        ultimoEvento;


      json +=
        "\"";


      json +=
        "}";


      AsyncWebServerResponse*
        respuesta =

          request->beginResponse(

            200,

            "application/json",

            json
          );


      respuesta->addHeader(
        "Cache-Control",
        "no-store"
      );


      request->send(
        respuesta
      );
    }
  );


  // =================================================
  // PORTAL CAUTIVO
  // =================================================

  server.on(
    "/generate_204",
    HTTP_ANY,

    [](AsyncWebServerRequest* request) {

      request->redirect(
        direccionPortal.c_str()
      );
    }
  );


  server.on(
    "/gen_204",
    HTTP_ANY,

    [](AsyncWebServerRequest* request) {

      request->redirect(
        direccionPortal.c_str()
      );
    }
  );


  server.on(
    "/hotspot-detect.html",
    HTTP_ANY,

    [](AsyncWebServerRequest* request) {

      request->redirect(
        direccionPortal.c_str()
      );
    }
  );


  server.on(
    "/connecttest.txt",
    HTTP_ANY,

    [](AsyncWebServerRequest* request) {

      request->redirect(
        "http://logout.net"
      );
    }
  );


  server.on(
    "/ncsi.txt",
    HTTP_ANY,

    [](AsyncWebServerRequest* request) {

      request->redirect(
        direccionPortal.c_str()
      );
    }
  );


  server.on(
    "/redirect",
    HTTP_ANY,

    [](AsyncWebServerRequest* request) {

      request->redirect(
        direccionPortal.c_str()
      );
    }
  );


  server.on(
    "/canonical.html",
    HTTP_ANY,

    [](AsyncWebServerRequest* request) {

      request->redirect(
        direccionPortal.c_str()
      );
    }
  );


  server.on(
    "/success.txt",
    HTTP_ANY,

    [](AsyncWebServerRequest* request) {

      request->send(
        200,
        "text/plain",
        ""
      );
    }
  );


  server.on(
    "/wpad.dat",
    HTTP_ANY,

    [](AsyncWebServerRequest* request) {

      request->send(
        404,
        "text/plain",
        ""
      );
    }
  );


  server.on(

    "/",

    HTTP_ANY,

    [](AsyncWebServerRequest* request) {

      AsyncWebServerResponse*
        respuesta =

          request->beginResponse(

            200,

            "text/html",

            paginaWeb
          );


      respuesta->addHeader(

        "Cache-Control",

        "no-cache, no-store, must-revalidate"
      );


      request->send(
        respuesta
      );
    }
  );


  server.onNotFound(

    [](AsyncWebServerRequest* request) {

      request->redirect(
        direccionPortal.c_str()
      );
    }

  );
}

// =====================================================
// SETUP
// =====================================================

void setup() {

  Serial.begin(
    115200
  );


  // Buzzer:
  // + -> D18
  // - -> GND

  ledcAttach(
    BUZZER,
    2000,
    8
  );


  ledcWriteTone(
    BUZZER,
    0
  );


  // Motor vibrador:
  // IN  -> D15
  // VCC -> alimentacion usada en el montaje que ya funciono
  // GND -> GND
  //
  // Empieza apagado para evitar vibracion accidental al arrancar.

  pinMode(
    MOTOR_VIBRACION,
    OUTPUT
  );


  digitalWrite(
    MOTOR_VIBRACION,
    LOW
  );


  cargarAlarmasDeMemoria();


  crearRedWifi();


  dnsServer.setTTL(
    3600
  );


  dnsServer.start(
    53,
    "*",
    ipLocal
  );


  configurarServidor();


  server.begin();


  Serial.println();

  Serial.println(
    "ALARMA INICIADA"
  );


  Serial.println(
    "BUZZER D18"
  );


  Serial.println(
    "MOTOR D15"
  );
}

// =====================================================
// LOOP
// =====================================================

void loop() {

  dnsServer.processNextRequest();


  comprobarAlarmas();


  actualizarMusica();


  delay(
    5
  );
}