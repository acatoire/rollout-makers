/*
  MyScreen
  Screen management class
*/

#include "Arduino.h"

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


void MyScreen::PrintBike(uint16_t color, int8_t decX, int8_t decY)
{
  MyScreen::Clear();
  
  //back wheel
  matrix_m->drawLine(decX + 3, decY + 5 , decX + 6, decY + 5,   color);  
  matrix_m->drawLine(decX + 6, decY + 6 , decX + 7, decY + 6,   color);
  matrix_m->drawLine(decX + 8, decY + 7 , decX + 8, decY + 8,   color);
  matrix_m->drawLine(decX + 9, decY + 8 , decX + 9, decY + 11,   color);
  matrix_m->drawLine(decX + 8, decY + 11, decX + 8, decY + 12,   color);
  matrix_m->drawLine(decX + 6, decY + 13, decX + 7, decY + 13,   color);
  matrix_m->drawLine(decX + 3, decY + 14, decX + 6, decY + 14,   color);
  matrix_m->drawLine(decX + 2, decY + 13, decX + 3, decY + 13,   color);
  matrix_m->drawLine(decX + 1, decY + 11, decX + 1, decY + 12,   color);
  matrix_m->drawLine(decX + 0, decY + 8 , decX + 0, decY + 11,   color);
  matrix_m->drawLine(decX + 1, decY + 7 , decX + 1, decY + 8,   color);
  matrix_m->drawLine(decX + 2, decY + 6 , decX + 3, decY + 6,   color);
  //Front wheel (x -> x+14)
  matrix_m->drawLine(decX + 17, decY + 5,  decX + 20, decY + 5,   color);  
  matrix_m->drawLine(decX + 20, decY + 6,  decX + 21, decY + 6,   color);
  matrix_m->drawLine(decX + 22, decY + 7,  decX + 22, decY + 8,   color);
  matrix_m->drawLine(decX + 23, decY + 8,  decX + 23, decY + 11,  color);
  matrix_m->drawLine(decX + 22, decY + 11, decX + 22, decY + 12,  color);
  matrix_m->drawLine(decX + 20, decY + 13, decX + 21, decY + 13,  color);
  matrix_m->drawLine(decX + 17, decY + 14, decX + 20, decY + 14,  color);
  matrix_m->drawLine(decX + 16, decY + 13, decX + 17, decY + 13,  color);
  matrix_m->drawLine(decX + 15, decY + 11, decX + 15, decY + 12,  color);
  matrix_m->drawLine(decX + 14, decY + 8,  decX + 14, decY + 11,  color);
  matrix_m->drawLine(decX + 15, decY + 7,  decX + 15, decY + 8,   color);
  matrix_m->drawLine(decX + 16, decY + 6,  decX + 17, decY + 6,   color);
  //Carter
  matrix_m->drawLine(decX + 5,  decY + 9,  decX + 10, decY + 4,   color);
  matrix_m->drawLine(decX + 9,  decY + 4,  decX + 16, decY + 4,   color);
  matrix_m->drawLine(decX + 16, decY + 1,  decX + 16, decY + 5,   color);
  matrix_m->drawLine(decX + 17, decY + 6,  decX + 18, decY + 9,   color);
  matrix_m->drawLine(decX + 5,  decY + 10, decX + 11, decY + 10,  color);
  matrix_m->drawLine(decX + 7,  decY + 2,  decX + 10, decY + 9,   color);
  matrix_m->drawLine(decX + 11, decY + 9,  decX + 15, decY + 5,   color);
  //guidon
  matrix_m->drawLine(decX + 16, decY + 1, decX + 18, decY + 1,   color);
  // selle
  matrix_m->drawLine(decX + 6, decY + 2, decX + 9, decY + 2,   color);
  matrix_m->drawLine(decX + 8, decY + 3, decX + 8, decY + 6,   color);

  MyScreen::Update();
}

void MyScreen::PrintCar(uint16_t color, int8_t decX, int8_t decY)
{
  MyScreen::Clear();
  
  //Glass of the Car
  matrix_m->drawLine(decX + 16, decY + 5,  decX + 19, decY + 8,   color); 
  matrix_m->drawLine(decX + 15, decY + 5,  decX + 18, decY + 8,   color); 
  // Car
  matrix_m->drawLine(decX + 2, decY + 8,  decX + 8, decY + 8,   color); 
  matrix_m->drawLine(decX + 1, decY + 9,  decX + 22, decY + 9,   color); 
  matrix_m->drawLine(decX + 1, decY + 10,  decX + 24, decY + 10,   color); 
  matrix_m->drawLine(decX + 1, decY + 11,  decX + 3, decY + 11,   color);   
  matrix_m->drawLine(decX + 8, decY + 11,  decX + 16, decY + 11,   color);
  matrix_m->drawLine(decX + 21, decY + 11,  decX + 25, decY + 11,   color); 
  matrix_m->drawLine(decX + 1, decY + 12,  decX + 2, decY + 12,   color); 
  matrix_m->drawLine(decX + 9, decY + 12,  decX + 15, decY + 12,   color); 
  matrix_m->drawLine(decX + 22, decY + 12,  decX + 26, decY + 12,   color); 
  matrix_m->drawLine(decX + 1, decY + 13,  decX + 2, decY + 13,   color); 
  matrix_m->drawLine(decX + 9, decY + 13,  decX + 15, decY + 13,   color); 
  matrix_m->drawLine(decX + 22, decY + 13,  decX + 26, decY + 13,   color); 
  matrix_m->drawLine(decX + 2, decY + 14,  decX + 2, decY + 14,   color); 
  matrix_m->drawLine(decX + 9, decY + 14,  decX + 15, decY + 14,   color); 
  matrix_m->drawLine(decX + 22, decY + 14,  decX + 25, decY + 14,   color); 
  // back wheel
  matrix_m->drawLine(decX + 5, decY + 12,  decX + 6, decY + 12,   color);
  matrix_m->drawLine(decX + 4, decY + 13,  decX + 7, decY + 13,   color);
  matrix_m->drawLine(decX + 4, decY + 14,  decX + 7, decY + 14,   color);
  matrix_m->drawLine(decX + 5, decY + 15,  decX + 6, decY + 15,   color);
  // front wheel 
  matrix_m->drawLine(decX + 18, decY + 12,  decX + 19, decY + 12,   color);
  matrix_m->drawLine(decX + 17, decY + 13,  decX + 20, decY + 13,   color);
  matrix_m->drawLine(decX + 17, decY + 14,  decX + 20, decY + 14,   color);
  matrix_m->drawLine(decX + 18, decY + 15,  decX + 19, decY + 15,   color);
  MyScreen::Update();
} 

