#include <Wire.h>
#include <Adafruit_VEML6075.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// --- OLED CONFIG ---
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// --- SENSOR UV ---
Adafruit_VEML6075 uvSensor = Adafruit_VEML6075();

// --- RELES ---
const int relePin3M = 3;  // Morado
const int relePin4R = 4;  // Rojo
const int relePin5N = 5;  // Naranja
const int relePin6A = 6;  // Amarillo
const int relePin7V = 7;  // Verde

// --- FUNCIONES ---
void apagarTodosLosRele() {
  digitalWrite(relePin7V, LOW);
  digitalWrite(relePin6A, LOW);
  digitalWrite(relePin5N, LOW);
  digitalWrite(relePin4R, LOW);
  digitalWrite(relePin3M, LOW);
}

void mostrarSemaforoUV(float uvIndex) {
  digitalWrite(relePin7V, uvIndex < 3);               // Verde
  digitalWrite(relePin6A, uvIndex >= 3 && uvIndex < 6); // Amarillo
  digitalWrite(relePin5N, uvIndex >= 6 && uvIndex < 8); // Naranja
  digitalWrite(relePin4R, uvIndex >= 8 && uvIndex < 11);// Rojo
  digitalWrite(relePin3M, uvIndex >= 11);              // Morado
}

String nivelPeligro(float uv) {
  if (uv < 3) return "BAJO";
  if (uv < 6) return "MEDIO";
  if (uv < 8) return "ALTO";
  if (uv < 11) return "PELIGROSO";
  return "EXTREMO";
}

// --- SETUP ---
void setup() {
  Serial.begin(9600);

  // Inicializar relés
  pinMode(relePin7V, OUTPUT);
  pinMode(relePin6A, OUTPUT);
  pinMode(relePin5N, OUTPUT);
  pinMode(relePin4R, OUTPUT);
  pinMode(relePin3M, OUTPUT);
  apagarTodosLosRele();

  // Inicializar OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("Error al iniciar OLED"));
    while (true);
  }

  // Inicializar sensor UV
  if (!uvSensor.begin()) {
    Serial.println("No se pudo encontrar el sensor VEML6075.");
    while (true);
  }

  // Mensaje inicial
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("UV Ready");
  display.display();

  Serial.println(">>> Semaforo UV <<<");
}

// --- LOOP ---
void loop() {
  float uvIndex = uvSensor.readUVI(); // Índice UV estimado
  uvIndex = constrain(uvIndex, 0.0, 15.0); // Para evitar valores raros

  String mensaje = nivelPeligro(uvIndex);

  // --- Serial Monitor ---
  Serial.print("🌞 UV Index: ");
  Serial.print(uvIndex, 2);
  Serial.print(" | Nivel: ");
  Serial.println(mensaje);

  // --- OLED Display ---
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(0, 0);
  display.print("UV: ");
  display.println(uvIndex, 1);

  display.setCursor(0, 32);
  display.setTextSize(1);
  display.print("Nivel: ");
  display.println(mensaje);
  display.display();

  // --- Relé según UV ---
  mostrarSemaforoUV(uvIndex);

  delay(1000);
}
