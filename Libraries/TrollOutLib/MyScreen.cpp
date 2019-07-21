/*
  MyScreen
  Screen management class
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
  uint16_t color_body;

  color_body = WHITE;


  MyScreen::Clear();

  switch(type)
  {
    case 0:

      MyScreen::PrintOoK_empty(color_body);

      // Draw small circle left
      matrix_m->drawRect(11, 5, 3, 3, color_body);
      //matrix_m->fillCircle(12, 6, 1, color_body);
      // Draw big right circle
      matrix_m->drawCircle(20, 5, 3, color_body);
      // draw a pixel for center of right circle
      matrix_m->drawPixel(20, 5, color_body);

      break;
      
    case 1:

      MyScreen::PrintOoK_empty(color_body);

      // Draw small circle left
      matrix_m->drawRect(11, 5, 3, 3, color_body);
      matrix_m->fillCircle(12, 6, 1, color_body);
      // Draw big right circle
      matrix_m->drawCircle(20, 5, 3, color_body);
      // draw a pixel for center of right circle
      matrix_m->drawPixel(20, 5, color_body);

      break;

    case 2:

        MyScreen::PrintOoK_empty(color_body);

        // draw small red cross on left
        matrix_m->drawLine(11, 5, 13, 7, RED);
        matrix_m->drawLine(11, 7, 13, 5, RED);
        // draw a white pixel for center of right circle
        matrix_m->drawPixel(20, 5, color_body);
        
        break;
    case 3:

        MyScreen::PrintOoK_empty(color_body);

        // draw small red cross on left
        matrix_m->drawLine(11, 5, 13, 7, RED);
        matrix_m->drawLine(11, 7, 13, 5, RED);
        // Draw big right circle inblue
        matrix_m->drawCircle(21, 5, 4, BLUE);
        // draw a white pixel for center of right circle
        matrix_m->drawPixel(20, 5, color_body);
        
        break;

      case 4:

        MyScreen::PrintOoK_empty(color_body);
        // draw green tick on left
        matrix_m->drawLine(11, 6, 12, 7, GREEN);
        matrix_m->drawLine(12, 7, 14, 5,GREEN);
        // Draw big right circle
        matrix_m->drawCircle(20, 5, 3, color_body);
      
        break;

      case 5:

        MyScreen::PrintOoK_empty(color_body);
        // draw green tick on left
        matrix_m->drawLine(11, 6, 12, 7, GREEN);
        matrix_m->drawLine(12, 7, 14, 5, GREEN);
        // Draw big right circle
        matrix_m->drawCircle(20, 5, 3, color_body);
        // draw a pixel for center of right circle
        matrix_m->drawPixel(21, 5, color_body);

        break;

    default:
      matrix_m->fillScreen(MAGENTA);
      break;
  }

  MyScreen::Update();

}

void MyScreen::PrintOoK_empty(uint16_t color)
{

// Head : round rectangle
matrix_m->drawLine(8, 0, 24, 0,   color);
matrix_m->drawLine(24, 0, 26, 2,  color);
matrix_m->drawLine(26, 2, 26, 8,  color);
matrix_m->drawLine(26, 8, 24, 10, color);
matrix_m->drawLine(24, 10, 8, 10, color);
matrix_m->drawLine(8, 10, 6, 8,   color);
matrix_m->drawLine(6, 8, 6, 2,    color);
matrix_m->drawLine(6, 2, 8, 0,    color);

// Body: "K" rotated = 3 lines
matrix_m->drawLine(14, 12, 18, 12, color);
matrix_m->drawLine(16, 13, 14, 15, color);
matrix_m->drawLine(16, 13, 18, 15, color);

}

