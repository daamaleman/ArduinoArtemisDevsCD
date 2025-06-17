#define LED 9        // Pin del LED
#define SENSOR A0    // Pin del sensor de rotación

void setup() {
    pinMode(LED, OUTPUT);
    pinMode(SENSOR, INPUT);
}

void loop() {
    int valorSensor = analogRead(SENSOR);  // Leer el valor del potenciómetro (0-1023)
    int brillo = map(valorSensor, 0, 1023, 255, 0);  // Convertir a rango de brillo (255=máximo, 0=mínimo)

    analogWrite(LED, brillo);  // Ajustar el brillo del LED
    delay(10);  // Pequeña pausa para estabilidad
}