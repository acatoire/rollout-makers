// testshapes demo for Adafruit RGBmatrixPanel library.
// Demonstrates the drawing abilities of the RGBmatrixPanel library.
// For 16x32 RGB LED matrix:
// http://www.adafruit.com/products/420

// Written by Limor Fried/Ladyada & Phil Burgess/PaintYourDragon
// for Adafruit Industries.
// BSD license, all text above must be included in any redistribution.

// Display OoK logo on led matrix

#include <RGBmatrixPanel.h>


#define byCar   0
#define byBike  1

uint8_t generate_value(uint8_t type);
void screen_bike_car (uint8_t minutesByBike, uint8_t minutesByCar);


#define CLK 4
#define OE   0
#define LAT 2
#define A   12
#define B   13
#define C   14

const uint8_t rgbpins[] = { 17,18,19,21,22,23 };
RGBmatrixPanel *matrix = new RGBmatrixPanel(A, B, C, CLK, LAT, OE, true, (uint8_t *)rgbpins);

#define clear()          fillScreen(0)
#define show()           swapBuffers(true)


void setup() {
  Serial.begin(115200);
  Serial.println("setup");
  matrix->begin();

}

void loop() {

  screen_bike_car(generate_value(byBike), generate_value(byCar));

  delay(5000);

}

void screen_bike_car (uint8_t minutesByBike, uint8_t minutesByCar)
{
  
  String convertNumber;

  Serial.printf ("Update screen bike/car with givens values: %u/%u\n", minutesByBike, minutesByCar);
  matrix->setTextSize(1);   // size 1 == 8 pixels high

  matrix->clear();
  
  // print each letter with a rainbow color
  matrix->setCursor(8, 0);  // First line
  matrix->setTextColor(matrix->Color333(0,7,0));
  
  convertNumber = String(minutesByBike);
  
  matrix->print(convertNumber);
  matrix->print("mn");

  matrix->setCursor(8, 9);  // Second line
  matrix->setTextColor(matrix->Color333(7,0,0));
  convertNumber = String(minutesByCar);
  
  matrix->print(convertNumber);
  matrix->print("mn");
  
  matrix->show();

}

uint8_t generate_value(uint8_t type)
{
  uint8_t value;
  
  value = random(15, 45);

  Serial.printf ("Generate random value: %u\n", value);

  return value;
}
