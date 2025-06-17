#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const int sensorPin = A0;

// Pines de relés por color
const int relePin3M = 3;  // Morado
const int relePin4R = 4;  // Rojo
const int relePin5N = 5;  // Naranja
const int relePin6A = 6;  // Amarillo
const int relePin7V = 7;  // Verde

const float vMin = 0.0;
const float vMax = 0.197;

// Convertir voltaje en índice UV
float calibrarUV(float voltage, float vMin, float vMax, float uvMax = 11.0) {
  voltage = constrain(voltage, vMin, vMax);
  return (voltage - vMin) / (vMax - vMin) * uvMax;
}

// Activar el relé correspondiente según el índice UV
void mostrarSemaforoUV(float uvIndex) {
  digitalWrite(relePin7V, uvIndex < 3);
  digitalWrite(relePin6A, uvIndex >= 3 && uvIndex < 6);
  digitalWrite(relePin5N, uvIndex >= 6 && uvIndex < 8);
  digitalWrite(relePin4R, uvIndex >= 8 && uvIndex < 11);
  digitalWrite(relePin3M, uvIndex >= 11);
}

void apagarTodosLosRele() {
  digitalWrite(relePin7V, LOW);
  digitalWrite(relePin6A, LOW);
  digitalWrite(relePin5N, LOW);
  digitalWrite(relePin4R, LOW);
  digitalWrite(relePin3M, LOW);
}

void setup() {
  Serial.begin(9600);

  pinMode(relePin7V, OUTPUT);
  pinMode(relePin6A, OUTPUT);
  pinMode(relePin5N, OUTPUT);
  pinMode(relePin4R, OUTPUT);
  pinMode(relePin3M, OUTPUT);
  apagarTodosLosRele();

  // Inicializar la pantalla OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("Error al iniciar OLED"));
    while (true); // Detener si falla
  }

  display.clearDisplay();
  display.setTextSize(2);  // Texto más grande
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("UV Ready");
  display.display();

  Serial.println(">>> Semaforo UV <<<");
  Serial.print("vMin: "); Serial.println(vMin, 3);
  Serial.print("vMax: "); Serial.println(vMax, 3);
}

void loop() {
  int raw = analogRead(sensorPin);
  float voltage = raw * (5.0 / 1023.0);
  float uvIndex = calibrarUV(voltage, vMin, vMax);

  Serial.print("🌞 Voltaje: ");
  Serial.print(voltage, 3);
  Serial.print(" V | UV Index: ");
  Serial.println(uvIndex, 2);

  display.clearDisplay();
  display.setTextSize(2);  // Tamaño grande para OLED
  display.setCursor(0, 0);
  display.print("UV:");
  display.println(uvIndex, 1);
  display.setCursor(0, 32);
  display.print("V: ");
  display.print(voltage, 2);
  display.print("V");
  display.display();

  mostrarSemaforoUV(uvIndex);
  delay(1000);
}
