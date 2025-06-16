#define TRIG_PIN 9  
#define ECHO_PIN 10  
#define BUZZER_PIN 7  // Cambiado a pin 7

void setup() {
    Serial.begin(9600);
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
    pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {
    // Enviar pulso ultrasónico
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    // Medir el eco
    long duration = pulseIn(ECHO_PIN, HIGH);
    float distance = duration * 0.034 / 2;  // Convertir a cm

    Serial.print("Distancia: ");
    Serial.print(distance);
    Serial.println(" cm");

    // Si está a 1 cm o menos, activar el buzzer
    if (distance <= 1.0) {
        digitalWrite(BUZZER_PIN, HIGH);  // Encender buzzer
    } else {
        digitalWrite(BUZZER_PIN, LOW);   // Apagar buzzer
    }

    delay(100);  // Pequeña pausa
}
