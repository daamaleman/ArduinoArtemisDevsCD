#include <SoftwareSerial.h>
const int bluetoothTx = 3;                           // bluetooth tx to 3 pin
const int bluetoothRx = 4;                           // bluetooth rx to 4 pin
SoftwareSerial bleSerial(bluetoothTx, bluetoothRx);  // Declare SoftwareSerial object for Bluetooth communication

void setup() {
  Serial.begin(9600);
  bleSerial.begin(9600);
}

void loop() {
  if (bleSerial.available()) {
    Serial.write(bleSerial.read());
  }
  if (Serial.available()) {
    bleSerial.write(Serial.read());
  }
}