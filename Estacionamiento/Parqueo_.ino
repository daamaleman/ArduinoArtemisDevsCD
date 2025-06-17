#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

// LCD y servos
LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo myservo;   // entrada
Servo myservo2;  // salida

// Pines sensores ultrasónicos
const int trigPin = 6;
const int echoPin = 7;
const int trigPin2 = 9;
const int echoPin2 = 8;

// Variables del parqueo
int totalParqueo = 4;
int parqueoActual = 0;
String parqueos[] = {"A1", "A2", "A3", "A4"};

// Estados para barreras
bool entradaAbierta = false;
bool salidaAbierta = false;
unsigned long tiempoEntrada = 0;
unsigned long tiempoSalida = 0;
const unsigned long tiempoEspera = 3000; // tiempo para cerrar después de abrir

// Función para medir distancia
int medirDistancia(int trig, int echo) {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  long duracion = pulseIn(echo, HIGH, 30000);
  if (duracion == 0) return 999;
  return duracion * 0.034 / 2;
}

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);

  myservo.attach(5);    // entrada
  myservo2.attach(10);  // salida

  myservo.write(0);     // cerrada
  myservo2.write(0);    // cerrada

  lcd.setCursor(0, 0);
  lcd.print("Parqueo UAM");
  lcd.setCursor(0, 1);
  lcd.print("Bienvenido!");
  delay(2000);
  lcd.clear();
}

void loop() {
  unsigned long ahora = millis();
  int distance1 = medirDistancia(trigPin, echoPin);
  int distance2 = medirDistancia(trigPin2, echoPin2);

  // --- PROCESAR ENTRADA ---
  if (!entradaAbierta && distance1 < 15 && totalParqueo > 0) {
    String slot = parqueos[parqueoActual];
    parqueoActual++;
    totalParqueo--;

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Estacionar en:");
    lcd.setCursor(0, 1);
    lcd.print("Slot ");
    lcd.print(slot);

    myservo.write(90);  // abrir barrera
    entradaAbierta = true;
    tiempoEntrada = ahora;
  }

  // Cerrar barrera de entrada si el carro ya pasó
  if (entradaAbierta && distance1 > 20 && (ahora - tiempoEntrada > tiempoEspera)) {
    myservo.write(0);   // cerrar barrera
    entradaAbierta = false;

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Parqueo UAM");
    lcd.setCursor(0, 1);
    lcd.print("Bienvenido!");
    delay(1000);
    lcd.clear();
  }

  // Mostrar parqueo lleno si intentan entrar
  if (!entradaAbierta && distance1 < 15 && totalParqueo <= 0) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Parqueo lleno");
    lcd.setCursor(0, 1);
    lcd.print("Solo entrada y retorno");
    myservo.write(0);
    delay(3000);
    myservo.write(0); 
    delay(1500);
    lcd.clear();
  }

  // --- PROCESAR SALIDA ---
  if (!salidaAbierta && distance2 < 15) {
    myservo2.write(90); // abrir barrera
    salidaAbierta = true;
    tiempoSalida = ahora;
  }

  // Cerrar barrera de salida si el carro ya pasó
  if (salidaAbierta && distance2 > 20 && (ahora - tiempoSalida > tiempoEspera)) {
    myservo2.write(0);  // cerrar barrera
    salidaAbierta = false;

    if (parqueoActual > 0) {
      parqueoActual--;
      totalParqueo++;
    }
  }

  // Debug
  Serial.print("Entrada: ");
  Serial.print(distance1);
  Serial.print(" cm\tSalida: ");
  Serial.println(distance2);

  delay(100);
}

