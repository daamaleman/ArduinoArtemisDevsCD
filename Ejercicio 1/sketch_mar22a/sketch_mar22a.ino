#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define DHTPIN 5
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);


void setup() {
  // Declaracion de variables
  //pinMode(13, OUTPUT);
  //Serial.begin(9600);
  //Serial.println("Hola desde arduino");

  Serial.begin(9600);
  dht.begin();  
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Iniciando...");
  delay(2000);
  lcd.clear();
}

void loop() {
  // Bucle 
  //digitalWrite(13, HIGH);
  //Serial.println("Led on ");
  //delay(2000);
  //digitalWrite(13, LOW);
  //Serial.println("Led off ");
  //delay(1000);

  delay(1000);
// Leemos la humedad relativa
  float h = dht.readHumidity();
// Leemos la temperatura en grados centígrados (por defecto)
  float t = dht.readTemperature();
// Comprobamos si ha habido algún error en la lectura
  if(isnan(h)|| isnan(t)){
    Serial.println("Error obteniendo los datos del sensor DHT11");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Error!...");
    return;
  }

  // Imprimimos los valores en el Monitor Serie
  Serial.print("Humedad: ");
  Serial.print(h);
  Serial.print("%  |  Temperatura: ");
  Serial.print(t);
  Serial.println("°C");  

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(t);
  lcd.print("C");

  lcd.setCursor(0, 1);
  lcd.print("Humedad: ");
  lcd.print(h);
  lcd.print("%");
}