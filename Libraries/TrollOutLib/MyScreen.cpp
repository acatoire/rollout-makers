/*
  MyScreen
  Screen management class
*/

#include "Arduino.h"

#include "MyScreen.h"
#include "MyScreenBmp.h"


// Macros
#define DecDrawLine(A, B, C, D, E) drawLine(decX + A, decY + B, decX + C, decY + D, E)
#define DecDrawRect(A, B, C, D, E) drawRect(decX + A, decY + B, C, D, E);



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

void MyScreen::PrintFull(uint16_t color)
{

  matrix_m->fillScreen(color);

}

void MyScreen::PrintFull(uint8_t R, uint8_t G, uint8_t B)
{

  matrix_m->fillScreen(matrix_m->Color333(R, G, B));

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
  
  //back wheel
  matrix_m->DecDrawLine(3,  5, 6, 5, color);  
  matrix_m->DecDrawLine(6,  6, 7, 6,   color);
  matrix_m->DecDrawLine(8,  7, 8, 8,   color);
  matrix_m->DecDrawLine(9,  8, 9, 11,   color);
  matrix_m->DecDrawLine(8, 11, 8, 12,   color);
  matrix_m->DecDrawLine(6, 13, 7, 13,   color);
  matrix_m->DecDrawLine(3, 14, 6, 14,   color);
  matrix_m->DecDrawLine(2, 13, 3, 13,   color);
  matrix_m->DecDrawLine(1, 11, 1, 12,   color);
  matrix_m->DecDrawLine(0,  8, 0, 11,   color);
  matrix_m->DecDrawLine(1,  7, 1, 8,   color);
  matrix_m->DecDrawLine(2,  6, 3, 6,   color);
  //Front wheel (x -> x+14)
  matrix_m->DecDrawLine(17,5,  20,5,   color);  
  matrix_m->DecDrawLine(20,6,  21,6,   color);
  matrix_m->DecDrawLine(22,7,  22,8,   color);
  matrix_m->DecDrawLine(23,8,  23,11,  color);
  matrix_m->DecDrawLine(22,11, 22,12,  color);
  matrix_m->DecDrawLine(20,13, 21,13,  color);
  matrix_m->DecDrawLine(17,14, 20,14,  color);
  matrix_m->DecDrawLine(16,13, 17,13,  color);
  matrix_m->DecDrawLine(15,11, 15,12,  color);
  matrix_m->DecDrawLine(14,8,  14,11,  color);
  matrix_m->DecDrawLine(15,7,  15,8,   color);
  matrix_m->DecDrawLine(16,6,  17,6,   color);
  //Carter
  matrix_m->DecDrawLine(5, 9,  10,4,   color);
  matrix_m->DecDrawLine(9, 4,  16,4,   color);
  matrix_m->DecDrawLine(16,1,  16,5,   color);
  matrix_m->DecDrawLine(17,6,  18,9,   color);
  matrix_m->DecDrawLine(5, 10, 11,10,  color);
  matrix_m->DecDrawLine(7, 2,  10,9,   color);
  matrix_m->DecDrawLine(11,9,  15,5,   color);
  //guidon
  matrix_m->DecDrawLine(16,1, 18,1,   color);
  // selle
  matrix_m->DecDrawLine(6,2, 9,2,   color);
  matrix_m->DecDrawLine(8,3, 8,6,   color);

}

void MyScreen::PrintCar(uint16_t color, int8_t decX, int8_t decY)
{
  
  //Glass of the Car
  matrix_m->DecDrawLine(16,  5,  19, 8, color); 
  matrix_m->DecDrawLine(15,  5,  18, 8, color); 
  // Car
  matrix_m->DecDrawLine( 2,  8,  8,  8, color); 
  matrix_m->DecDrawLine( 1,  9, 22,  9, color); 
  matrix_m->DecDrawLine( 1, 10, 24, 10, color); 
  matrix_m->DecDrawLine( 1, 11,  3, 11, color);   
  matrix_m->DecDrawLine( 8, 11, 16, 11, color);
  matrix_m->DecDrawLine(21, 11, 25, 11, color); 
  matrix_m->DecDrawLine( 1, 12,  2, 12, color); 
  matrix_m->DecDrawLine( 9, 12, 15, 12, color); 
  matrix_m->DecDrawLine(22, 12, 26, 12, color); 
  matrix_m->DecDrawLine( 1, 13,  2, 13, color); 
  matrix_m->DecDrawLine( 9, 13, 15, 13, color); 
  matrix_m->DecDrawLine(22, 13, 26, 13, color); 
  matrix_m->DecDrawLine( 2, 14,  2, 14, color); 
  matrix_m->DecDrawLine( 9, 14, 15, 14, color); 
  matrix_m->DecDrawLine(22, 14, 25, 14, color); 
  // back whDecDrawLine
  matrix_m->DecDrawLine( 5, 12,  6, 12, color);
  matrix_m->DecDrawLine( 4, 13,  7, 13, color);
  matrix_m->DecDrawLine( 4, 14,  7, 14, color);
  matrix_m->DecDrawLine( 5, 15,  6, 15, color);
  // front wDecDrawLine
  matrix_m->DecDrawLine(18, 12, 19, 12, color);
  matrix_m->DecDrawLine(17, 13, 20, 13, color);
  matrix_m->DecDrawLine(17, 14, 20, 14, color);
  matrix_m->DecDrawLine(18, 15, 19, 15, color);

} 

void MyScreen::PrintBmp(uint8_t type, uint16_t color, int8_t decX, int8_t decY)
{
    /*!
    @brief    Draw drawBitmap arguments explanation
    @param    x   Top left corner x coordinate
    @param    y   Top left corner y coordinate
    @param    bitmap  byte array with monochrome bitmap
    @param    w   Width of bitmap in pixels
    @param    h   Height of bitmap in pixels
    @param    color 16-bit 5-6-5 Color to draw pixels with
    @param    bg 16-bit 5-6-5 Color to draw background with
    */

  switch (type)
  {
  case 0:
    matrix_m->drawBitmap(decX, decY,  logo16_adafruit_bmp, 16, 16, color);
    break;
  case 1:
    matrix_m->drawBitmap(decX, decY,  logo16_check_pattern_bmp, 8, 16, color);
    matrix_m->drawBitmap(decX +  8, decY,  logo16_check_pattern_bmp, 8, 16, color);
    matrix_m->drawBitmap(decX + 16, decY,  logo16_check_pattern_bmp, 8, 16, color);
    matrix_m->drawBitmap(decX + 24, decY,  logo16_check_pattern_bmp, 8, 16, color);
    break;
  case 2:
    matrix_m->drawBitmap(decX, decY,  train_bmp, 24, 16, color);
    break;
  
  default:
    break;
  }

} 

void MyScreen::PrintStickMan(uint8_t frame, uint16_t color, int8_t decX, int8_t decY)
{
  /*!
  @brief    Draw drawBitmap arguments explanation
  @param    frame   Select 1 of the 7 frames for StickMan walking
  @param    color 16-bit 5-6-5 Color to draw pixels with
  @param    bg 16-bit 5-6-5 Color to draw background with
  */

  switch (frame % 7)
  {
  case 0:
    matrix_m->drawBitmap(decX, decY,  StickMan_0, 8, 16, color);
    break;
  case 1:
    matrix_m->drawBitmap(decX, decY,  StickMan_1, 8, 16, color);
    break;
  case 2:
    matrix_m->drawBitmap(decX, decY,  StickMan_2, 8, 16, color);
    break;
  case 3:
    matrix_m->drawBitmap(decX, decY,  StickMan_3, 8, 16, color);
    break;
  case 4:
    matrix_m->drawBitmap(decX, decY,  StickMan_4, 8, 16, color);
    break;
   case 5:
    matrix_m->drawBitmap(decX, decY,  StickMan_5, 8, 16, color);
    break;
   case 6:
    matrix_m->drawBitmap(decX, decY,  StickMan_6, 8, 16, color);
    break;
      
  default:
    break;
  }
 }
  void MyScreen::PrintBattery(uint8_t percentage, uint16_t shape_color, int8_t decX, int8_t decY)
{
  /*!
  @brief    Draw drawBitmap arguments explanation
  @param    percentage   value of ho is filled the battery (100% = full)
  @param    shape_color 16-bit 5-6-5 Color to draw shape with
  @param    decX, decY : offset of the position of the drawing
  */
  uint8_t formated_percentage;
  uint8_t level;
  if(percentage > 100) formated_percentage = 100;
  else formated_percentage = percentage;

  level = formated_percentage / 10;
  
  // Display external shape of the battery
  matrix_m->drawBitmap(decX, decY,  Battery_bmp, 16, 16, shape_color);
  
  // Display level of the battery 
  switch (level)
  {
	case 0:
		matrix_m->DecDrawLine(2, 13, 8, 13, 0xF800); 
		break;
	case 1:
		matrix_m->DecDrawRect(2, 13-level, 7, 1+level, 0xF980); 
		break;
	case 2:
		matrix_m->DecDrawRect(2, 13-level, 7, 1+level, 0xFA40); 
		break;
	case 3:
		matrix_m->DecDrawRect(2, 13-level, 7, 1+level, 0xFB40); 
		break;
	case 4:
		matrix_m->DecDrawRect(2, 13-level, 7, 1+level, 0xFD00); 
		break;
	case 5:
		matrix_m->DecDrawRect(2, 13-level, 7, 1+level, 0xFF20); 
		break;
	case 6:
		matrix_m->DecDrawRect(2, 13-level, 7, 1+level, 0xDF60); 
		break;
    case 7:
		matrix_m->DecDrawRect(2, 13-level, 7, 1+level, 0x9F40); 
		break;
	case 8:
		matrix_m->DecDrawRect(2, 13-level, 7, 1+level, 0x7741); 
		break;
	case 9:
		matrix_m->DecDrawRect(2, 13-level, 7, 1+level, 0x4FE0); 
		break;
	case 10:
		matrix_m->DecDrawRect(2, 13-level, 7, 1+level, 0x07E0); 
		break;	
  default:
    break;
  }

} 
