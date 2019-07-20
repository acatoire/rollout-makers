/*
  Morse.cpp - Library for flashing Morse code.
  Created by David A. Mellis, November 2, 2007.
  Released into the public domain.
*/

#include "Arduino.h"

#include "MyScreen.h"

MyScreen::MyScreen(int pin)
{

  pin_m = pin;

  const uint8_t rgbpins[] = { 17,18,19,21,22,23 };
  //matrix_m = new RGBmatrixPanel(A, B, C, CLK, LAT, OE, true, (uint8_t *)rgbpins);

}


void MyScreen::Setup() 
{

  //Serial.println("setup_screen");
  //matrix->begin();

}


void MyScreen::Clear(void)
{

  //fillScreen(0);

}


void MyScreen::Show(void)
{

  //swapBuffers(true);

}


void MyScreen::Print_bike_car (uint8_t minutesByBike, uint8_t minutesByCar)
{
  
  String convertNumber;
/*
  //Serial.printf ("Update screen bike/car with givens values: %u/%u\n", minutesByBike, minutesByCar);
  matrix_m->setTextSize(1);   // size 1 == 8 pixels high

  matrix_m->clear();
  
  // print each letter with a rainbow color
  matrix_m->setCursor(8, 0);  // First line
  matrix_m->setTextColor(matrix_m->Color333(0,7,0));
  
  convertNumber = String(minutesByBike);
  
  matrix_m->print(convertNumber);
  matrix_m.print("mn");

  matrix_m->setCursor(8, 9);  // Second line
  matrix_m->setTextColor(matrix->Color333(7,0,0));
  convertNumber = String(minutesByCar);
  
  matrix_m->print(convertNumber);
  matrix_m->print("mn");
  
  matrix_m->show();
*/
}

