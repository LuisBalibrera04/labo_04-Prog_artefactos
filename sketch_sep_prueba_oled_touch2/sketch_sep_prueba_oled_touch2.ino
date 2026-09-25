#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define OLED_ADDRESS 0x3C

Adafruit_SH1106G display(
  SCREEN_WIDTH,
  SCREEN_HEIGHT,
  &Wire,
  OLED_RESET
);

// Pines táctiles asignados en el ESP32
const int pinBoton1 = 4;   // GPIO4 (Touch 0)
const int pinBoton2 = 15;  // GPIO15 (Touch 3)

// Tu umbral seleccionado
const int limiteToque = 700;

void setup() {
  Serial.begin(115200);

  Wire.begin(21, 22);

  if (!display.begin(OLED_ADDRESS, true)) {
    Serial.println("Error al iniciar la pantalla OLED");
    while (1);
  }

  display.clearDisplay();
  display.setTextColor(SH110X_WHITE);
}

void loop() {
  int lectura1 = touchRead(pinBoton1);
  int lectura2 = touchRead(pinBoton2);

  // Monitor serial para ver los valores en vivo
  Serial.print("Boton 1: ");
  Serial.print(lectura1);
  Serial.print(" | Boton 2: ");
  Serial.println(lectura2);

  display.clearDisplay();

  display.setTextSize(1);
  display.setCursor(26, 5);
  display.println("ESP32 TOUCH");

  // Si se toca el primer sensor
  if (lectura1 < limiteToque) {
    display.setCursor(12, 28);
    display.println("Boton 1 activado!");
    display.fillCircle(105, 52, 5, SH110X_WHITE);
  }
  // Si se toca el segundo sensor
  else if (lectura2 < limiteToque) {
    display.setCursor(12, 28);
    display.println("Boton 2 activado!");
    display.fillCircle(64, 52, 5, SH110X_WHITE);
  }
  // Si no se toca ninguno
  else {
    display.setCursor(32, 28);
    display.println("Esperando...");
    display.fillCircle(20, 52, 5, SH110X_WHITE);
  }

  display.display();

  delay(100);
}