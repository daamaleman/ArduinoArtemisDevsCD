#include <SoftwareSerial.h>

SoftwareSerial bleSerial(3, 4); // RX, TX

// Pines de dirección (PWM) y tracción (digital)
const int DIR1 = 10;  // PWM - dirección derecha
const int DIR2 = 9;   // PWM - dirección izquierda
const int MOT1 = 6;   // digital - reversa
const int MOT2 = 11;  // digital - avance
const int BUZZER = 5;

// Variables de tiempo
char ultimoComando = 0;
unsigned long tiempoInicio = 0;
unsigned long tiempoPresionado = 0;

void setup() {
  bleSerial.begin(9600);
  pinMode(DIR1, OUTPUT);
  pinMode(DIR2, OUTPUT);
  pinMode(MOT1, OUTPUT);
  pinMode(MOT2, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  apagarMotores();
}

void loop() {
  if (bleSerial.available()) {
    char c = bleSerial.read();

    if (strchr("FBLRSGHIJY", c)) {
      if (c == ultimoComando) {
        tiempoPresionado = millis() - tiempoInicio;
      } else {
        ultimoComando = c;
        tiempoInicio = millis();
        tiempoPresionado = 0;
      }

      procesarComando(c, tiempoPresionado);
    }
  }
}

void procesarComando(char c, unsigned long tiempo) {
  apagarMotores();

  switch (c) {
    case 'F':
      direccion_centro();
      motor_adelante();
      break;

    case 'B':
      direccion_centro();
      motor_atras();
      break;

    case 'L':
    case 'G':
      direccion_pwm('L', tiempo);
      motor_adelante();
      break;

    case 'R':
    case 'H':
      direccion_pwm('R', tiempo);
      motor_adelante();
      break;

    case 'I':
      direccion_pwm('L', tiempo);
      motor_atras();
      break;

    case 'J':
      direccion_pwm('R', tiempo);
      motor_atras();
      break;

    case 'Y':
      beep(1, 100);
      break;

    case 'S':
    default:
      apagarMotores();
      break;
  }
}

// Dirección al centro
void direccion_centro() {
  analogWrite(DIR1, 0);
  analogWrite(DIR2, 0);
}

// Dirección PWM corregida
void direccion_pwm(char lado, unsigned long tiempo) {
  int fuerzaGiro = map(tiempo, 0, 2000, 160, 255);  // Más agresivo
  fuerzaGiro = constrain(fuerzaGiro, 160, 255);

  if (lado == 'L') {
    analogWrite(DIR2, fuerzaGiro);
    analogWrite(DIR1, 0);               // izquierda: DIR2
  
  } else {
    analogWrite(DIR1, fuerzaGiro);      // derecha: DIR1
    analogWrite(DIR2, 0);
  }
}

// Movimiento hacia adelante
void motor_adelante() {
  analogWrite(MOT1, 0);
  analogWrite(MOT2, 150);  // Velocidad fija
}

// Movimiento hacia atrás
void motor_atras() {
  analogWrite(MOT1, 150);  // Velocidad fija
  analogWrite(MOT2, 0);
}

// Apagar motores
void apagarMotores() {
  analogWrite(MOT1, 0);
  analogWrite(MOT2, 0);
  analogWrite(DIR1, 0);
  analogWrite(DIR2, 0);
}

// Beep
void beep(int veces, int duracion) {
  for (int i = 0; i < veces; i++) {
    digitalWrite(BUZZER, HIGH);
    delay(duracion);
    digitalWrite(BUZZER, LOW);
    delay(100);
  }
}
