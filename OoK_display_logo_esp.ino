// testshapes demo for Adafruit RGBmatrixPanel library.
// Demonstrates the drawing abilities of the RGBmatrixPanel library.
// For 16x32 RGB LED matrix:
// http://www.adafruit.com/products/420

// Written by Limor Fried/Ladyada & Phil Burgess/PaintYourDragon
// for Adafruit Industries.
// BSD license, all text above must be included in any redistribution.

// Display OoK logo on led matrix

#include <RGBmatrixPanel.h>

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
  Serial.printf("setup");
  matrix->begin();
}

void loop() {
  // Draw light grey rectangle
  //matrix->drawRect(6, 0, 20, 11, matrix->Color333(5, 5, 5));
  // Or round rectangle
  matrix->drawLine(8, 0, 24, 0, matrix->Color333(5, 5, 5));
  matrix->drawLine(24, 0, 26, 2, matrix->Color333(5, 5, 5));
  matrix->drawLine(26, 2, 26, 8, matrix->Color333(5, 5, 5));
  matrix->drawLine(26, 8, 24, 10, matrix->Color333(5, 5, 5));
  matrix->drawLine(24, 10, 8, 10, matrix->Color333(5, 5, 5));
  matrix->drawLine(8, 10, 6, 8, matrix->Color333(5, 5, 5));
  matrix->drawLine(6, 8, 6, 2, matrix->Color333(5, 5, 5));
  matrix->drawLine(6, 2, 8, 0, matrix->Color333(5, 5, 5));
  // Draw "K" rotated = 3 lines light grey
  matrix->drawLine(14, 12, 18, 12, matrix->Color333(5, 5, 5));
  matrix->drawLine(16, 13, 14, 15, matrix->Color333(5, 5, 5));
  matrix->drawLine(16, 13, 18, 15, matrix->Color333(5, 5, 5));
  // Draw small circle left
  matrix->drawRect(11, 5, 3, 3, matrix->Color333(5, 5, 5));
  //matrix->fillCircle(12, 6, 1, matrix->Color333(5, 5, 5));
  // Draw big right circle
  matrix->drawCircle(20, 5, 3, matrix->Color333(5, 5, 5));
   // draw a pixel for center of right circle
  matrix->drawPixel(20, 5, matrix->Color333(5, 5, 5));
  
  matrix->show();
  delay(5000);
  Serial.printf("Display Logo inlight grey OoK");

  // Clear area inside grey rectangle for changing draw of eyes
  matrix->clear();
    // Draw light grey rectangle
  //matrix->drawRect(6, 0, 20, 11, matrix->Color333(5, 5, 5));
  // Or round rectangle
  matrix->drawLine(8, 0, 24, 0, matrix->Color333(5, 5, 5));
  matrix->drawLine(24, 0, 26, 2, matrix->Color333(5, 5, 5));
  matrix->drawLine(26, 2, 26, 8, matrix->Color333(5, 5, 5));
  matrix->drawLine(26, 8, 24, 10, matrix->Color333(5, 5, 5));
  matrix->drawLine(24, 10, 8, 10, matrix->Color333(5, 5, 5));
  matrix->drawLine(8, 10, 6, 8, matrix->Color333(5, 5, 5));
  matrix->drawLine(6, 8, 6, 2, matrix->Color333(5, 5, 5));
  matrix->drawLine(6, 2, 8, 0, matrix->Color333(5, 5, 5));
  // Draw "K" rotated = 3 lines light grey
  matrix->drawLine(14, 12, 18, 12, matrix->Color333(5, 5, 5));
  matrix->drawLine(16, 13, 14, 15, matrix->Color333(5, 5, 5));
  matrix->drawLine(16, 13, 18, 15, matrix->Color333(5, 5, 5));
  matrix->show();
  // draw small red cross on left
  matrix->drawLine(11, 5, 13, 7, matrix->Color333(7, 0, 0));
  matrix->drawLine(11, 7, 13, 5, matrix->Color333(7, 0, 0));
   // Draw big right circle inblue
  //matrix->drawCircle(21, 5, 4, matrix->Color333(2, 3, 7));
   // draw a white pixel for center of right circle
  matrix->drawPixel(20, 5, matrix->Color333(7, 7, 7));
  matrix->show();
   delay(5000);

 // Clear area inside grey rectangle for changing draw of eyes
  matrix->clear();
    // Draw light grey rectangle
  //matrix->drawRect(6, 0, 20, 11, matrix->Color333(5, 5, 5));
  // Or round rectangle
  matrix->drawLine(8, 0, 24, 0, matrix->Color333(5, 5, 5));
  matrix->drawLine(24, 0, 26, 2, matrix->Color333(5, 5, 5));
  matrix->drawLine(26, 2, 26, 8, matrix->Color333(5, 5, 5));
  matrix->drawLine(26, 8, 24, 10, matrix->Color333(5, 5, 5));
  matrix->drawLine(24, 10, 8, 10, matrix->Color333(5, 5, 5));
  matrix->drawLine(8, 10, 6, 8, matrix->Color333(5, 5, 5));
  matrix->drawLine(6, 8, 6, 2, matrix->Color333(5, 5, 5));
  matrix->drawLine(6, 2, 8, 0, matrix->Color333(5, 5, 5));
  // Draw "K" rotated = 3 lines light grey
  matrix->drawLine(14, 12, 18, 12, matrix->Color333(5, 5, 5));
  matrix->drawLine(16, 13, 14, 15, matrix->Color333(5, 5, 5));
  matrix->drawLine(16, 13, 18, 15, matrix->Color333(5, 5, 5));
  matrix->show();
  // draw green tick on left
  matrix->drawLine(11, 6, 12, 7, matrix->Color333(0, 7, 2));
  matrix->drawLine(12, 7, 14, 5, matrix->Color333(0, 7, 2));
   // Draw big right circle
  matrix->drawCircle(20, 5, 3, matrix->Color333(5, 5, 5));
   // draw a pixel for center of right circle
  //matrix->drawPixel(21, 5, matrix->Color333(7, 7, 7));
  matrix->show();
   delay(5000);
   matrix->clear();
 /* 
  matrix->clear();
  // fix the screen with green
  matrix->fillRect(0, 0, 32, 16, matrix->Color333(0, 7, 0));
  //matrix->fillRect(0, 0, 32, 16, 0x07E0);
  matrix->show();
  delay(5000);
  Serial.printf("green screen");
  
  matrix->clear();
  // draw a box in yellow
  matrix->drawRect(0, 0, 32, 16, matrix->Color333(7, 7, 0));
  //matrix->drawRect(0, 0, 32, 16, 0xFFE0);
  matrix->show();
  delay(5000);
  Serial.printf("yellow box");

  matrix->clear();
  // draw an 'X' in red
  matrix->drawLine(0, 0, 31, 15, matrix->Color333(7, 0, 0));
  matrix->drawLine(31, 0, 0, 15, matrix->Color333(7, 0, 0));
  //matrix->drawLine(0, 0, 31, 15, 0xF800);
  //matrix->drawLine(31, 0, 0, 15, 0xF800);
  matrix->show();
  delay(5000);
  Serial.printf("red X");

  matrix->clear();
  // draw a blue circle
  matrix->drawCircle(7, 7, 7, matrix->Color333(0, 0, 7));
  //matrix->drawCircle(7, 7, 7, 0x001F);
  matrix->show();
  delay(5000);
  Serial.printf("blue circle");

  matrix->clear();
  // fill a violet circle
  matrix->fillCircle(23, 7, 7, matrix->Color333(7, 0, 7));
  //matrix->fillCircle(23, 7, 7, 0xF81F);
  matrix->show();
  delay(5000);
  Serial.printf("violet circle");

  matrix->clear();
  Serial.printf("black screen");


  // draw some text!
  matrix->setCursor(1, 0);  // start at top left, with one pixel of spacing
  matrix->setTextSize(1);   // size 1 == 8 pixels high
  Serial.printf ("text");
  
  // print each letter with a rainbow color
  //matrix->setTextColor(matrix->Color333(7,0,0));
  matrix->setTextColor(0xF800);
  matrix->print('1');
  //matrix->setTextColor(matrix->Color333(7,4,0));
  matrix->setTextColor(0xFBF0);
  matrix->print('6');
  //matrix->setTextColor(matrix->Color333(7,7,0));
  matrix->setTextColor(0xFFE0);
  matrix->print('x');
  //matrix->setTextColor(matrix->Color333(4,7,0));
  matrix->print('3');
  //matrix->setTextColor(matrix->Color333(0,7,0));
  matrix->print('2');

  matrix->setCursor(1, 9);  // next line
  //matrix->setTextColor(matrix->Color333(0,7,7));
  matrix->print('*');
  //matrix->setTextColor(matrix->Color333(0,4,7));
  matrix->print('R');
  //matrix->setTextColor(matrix->Color333(0,0,7));
  matrix->print('G');
  //matrix->setTextColor(matrix->Color333(4,0,7));
  matrix->print('B');
  //matrix->setTextColor(matrix->Color333(7,0,4));
  matrix->print('*');
  matrix->show();
  // whew!// Do nothing -- image doesn't change
*/
}
