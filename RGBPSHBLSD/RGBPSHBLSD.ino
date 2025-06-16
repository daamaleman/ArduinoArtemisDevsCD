#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

int redPin = 11;     // Pin del LED Rojo
int greenPin = 10;   // Pin del LED Verde
int bluePin = 9;     // Pin del LED Azul
int buttonPin = 3;   // Botón en el pin 3
int colorState = 0;  // Estado para alternar colores
bool buttonPressed = false;

void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(buttonPin, INPUT);

  // Inicializar el LCD
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Color: Apagado");
}

void loop() {
  int buttonState = digitalRead(buttonPin);

  // Detectar el cambio de estado del botón (evita cambios múltiples por rebote)
  if (buttonState == HIGH && !buttonPressed) {
    buttonPressed = true;
    
    colorState = (colorState + 1) % 5;  // Cambia el estado y lo cicla entre 0 y 4
    changeColor(colorState);
  } else if (buttonState == LOW) {
    buttonPressed = false;  // Restablecer cuando el botón se suelta
  }
}

// Función para cambiar el color del LED RGB y actualizar el LCD
void changeColor(int state) {
  switch (state) {
    case 0: setColor(250, 0, 0, "Azul"); break;
    case 1: setColor(0, 255, 0, "Verde"); break;
    case 2: setColor(0, 0, 255, "rojo"); break;
    case 3: setColor(255, 255, 0, "Celeste verdoso"); break;
    case 4: setColor(0, 0, 0, "Apagado"); break;
  }
}

// Función para establecer los valores de color del LED RGB y actualizar el LCD
void setColor(int red, int green, int blue, String colorName) {
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);

  // Mostrar el color actual en el LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Color:");
  lcd.setCursor(0, 1);
  lcd.print(colorName);
}