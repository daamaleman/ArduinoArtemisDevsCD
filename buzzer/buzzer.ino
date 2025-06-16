#define BUZZER_PIN 7  // Pin del buzzer

void setup() {
    pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {
    digitalWrite(BUZZER_PIN, HIGH);  // Encender buzzer
    delay(1000);                     // Sonar 1 segundo
    digitalWrite(BUZZER_PIN, LOW);   // Apagar buzzer
    delay(2000);                     // Esperar 2 segundos
}
