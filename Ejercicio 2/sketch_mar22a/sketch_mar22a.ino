#include <Wire.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

// Configuración de la pantalla OLED
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Configuración de la pantalla LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Configuración del sensor DHT11
#define DHTPIN 5
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

void setup() {
    Serial.begin(9600);
    dht.begin();

    // Inicializar la pantalla OLED
    if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
        Serial.println(F("Error al iniciar el OLED"));
        for (;;);
    }
    
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.println("Iniciando...");
    display.display();
    delay(2000);
    display.clearDisplay();

    // Inicializar la pantalla LCD
    lcd.init();
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print("Iniciando...");
    delay(2000);
    lcd.clear();
}

void loop() {
    float h = dht.readHumidity();
    float t = dht.readTemperature();

    if (isnan(h) || isnan(t)) {
        Serial.println("Error al leer los datos del sensor DHT11");
        display.clearDisplay();
        display.setCursor(0, 0);
        display.println("Error al leer");
        display.println("datos del sensor");
        display.display();
        
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Error!... ");
        
        delay(2000);
        return;
    }

    Serial.print("Humedad: ");
    Serial.print(h);
    Serial.print("%  |  Temperatura: ");
    Serial.print(t);
    Serial.println("C");

    // Mostrar datos en la pantalla OLED
    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0, 20);
    display.print("Temperatura: ");
    display.print(t);
    display.print(" C");

    display.setCursor(0, 40);
    display.print("Humedad: ");
    display.print(h);
    display.print(" %");

    display.display();

    // Mostrar datos en la pantalla LCD
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Temp: ");
    lcd.print(t);
    lcd.print("C");

    lcd.setCursor(0, 1);
    lcd.print("Humedad: ");
    lcd.print(h);
    lcd.print("%");

    delay(2000);
}