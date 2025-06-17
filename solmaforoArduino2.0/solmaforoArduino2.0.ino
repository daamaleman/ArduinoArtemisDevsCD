#include <Wire.h>
#include <Adafruit_VEML6075.h>

// Crea una instancia del sensor VEML6075
Adafruit_VEML6075 uvSensor = Adafruit_VEML6075();

void setup() {
  // Inicia la comunicación Serial
  Serial.begin(9600);
  
  // Inicia el sensor VEML6075
  if (!uvSensor.begin()) {
    Serial.println("No se pudo encontrar el sensor VEML6075.");
    while (1);
  }
  
  Serial.println("Sensor VEML6075 listo para medir.");
}

void loop() {
  // Lee el valor de radiación UV (luz UV-A) en lux
  uint16_t uvLevel = uvSensor.readUV();
  
  // Convierte el valor en lux (o la unidad que prefieras)
  float lux = uvSensor.toLux(uvLevel);
  
  // Imprime el valor de radiación UV
  Serial.print("Radiación UV (Lux): ");
  Serial.println(lux);
  
  // Espera un segundo antes de la siguiente lectura
  delay(1000);
}