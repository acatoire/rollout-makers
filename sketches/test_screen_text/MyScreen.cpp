/*
  Morse.cpp - Library for flashing Morse code.
  Created by David A. Mellis, November 2, 2007.
  Released into the public domain.
*/

#include "Arduino.h"

#include <RGBmatrixPanel.h>

#include "MyScreen.h"

MyScreen::MyScreen(void)
{


}


void MyScreen::Setup(void) 
{

  matrix_m->begin();

}


void MyScreen::Clear(void)
{

  matrix_m->fillScreen(0);

}


void MyScreen::Update(void)
{

  matrix_m->swapBuffers(true);

}


void MyScreen::PrintFull(uint8_t R, uint8_t G, uint8_t B)
{

  matrix_m->fillScreen(matrix_m->Color333(R, G, B));

  MyScreen::Update();

}


void MyScreen::PrintTwoTimes(uint8_t minutesByBike, uint8_t minutesByCar)
{
  
  String convertNumber;

  matrix_m->setTextSize(1);   // size 1 == 8 pixels high

  MyScreen::Clear();
  
  // print each letter with a rainbow color
  matrix_m->setCursor(8, 0);  // First line
  matrix_m->setTextColor(matrix_m->Color333(0,7,0));
  
  convertNumber = String(minutesByBike);
  
  matrix_m->print(convertNumber);
  matrix_m->print("mn");

  matrix_m->setCursor(8, 9);  // Second line
  matrix_m->setTextColor(matrix_m->Color333(7,0,0));
  convertNumber = String(minutesByCar);
  
  matrix_m->print(convertNumber);
  matrix_m->print("mn");
  
  MyScreen::Update();

}

void MyScreen::PrintOoK(uint8_t type)
{
  MyScreen::Clear();


  // Draw light grey rectangle
  //matrix->drawRect(6, 0, 20, 11, matrix->Color333(5, 5, 5));
  // Or round rectangle
  matrix_m->drawLine(8, 0, 24, 0,   matrix_m->Color333(5, 5, 5));
  matrix_m->drawLine(24, 0, 26, 2,  matrix_m->Color333(5, 5, 5));
  matrix_m->drawLine(26, 2, 26, 8,  matrix_m->Color333(5, 5, 5));
  matrix_m->drawLine(26, 8, 24, 10, matrix_m->Color333(5, 5, 5));
  matrix_m->drawLine(24, 10, 8, 10, matrix_m->Color333(5, 5, 5));
  matrix_m->drawLine(8, 10, 6, 8,   matrix_m->Color333(5, 5, 5));
  matrix_m->drawLine(6, 8, 6, 2,    matrix_m->Color333(5, 5, 5));
  matrix_m->drawLine(6, 2, 8, 0,    matrix_m->Color333(5, 5, 5));
  // Draw "K" rotated = 3 lines light grey
  matrix_m->drawLine(14, 12, 18, 12, matrix_m->Color333(5, 5, 5));
  matrix_m->drawLine(16, 13, 14, 15, matrix_m->Color333(5, 5, 5));
  matrix_m->drawLine(16, 13, 18, 15, matrix_m->Color333(5, 5, 5));
  // Draw small circle left
  matrix_m->drawRect(11, 5, 3, 3, matrix_m->Color333(5, 5, 5));
  //matrix->fillCircle(12, 6, 1, matrix->Color333(5, 5, 5));
  // Draw big right circle
  matrix_m->drawCircle(20, 5, 3, matrix_m->Color333(5, 5, 5));
   // draw a pixel for center of right circle
  matrix_m->drawPixel(20, 5, matrix_m->Color333(5, 5, 5));

  MyScreen::Update();

}

