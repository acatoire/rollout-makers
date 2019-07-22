// testshapes demo for Adafruit RGBmatrixPanel library.
// Demonstrates the drawing abilities of the RGBmatrixPanel library.
// For 16x32 RGB LED matrix:
// http://www.adafruit.com/products/420

// Written by Limor Fried/Ladyada & Phil Burgess/PaintYourDragon
// for Adafruit Industries.
// BSD license, all text above must be included in any redistribution.

// Display OoK logo on led matrix


#include <MyValue.h>
#include <MyScreen.h>



MyScreen screen;
MyValue timeByCar(10);
MyValue timeByBike(10);

void setup() 
{

  Serial.begin(115200);
  Serial.println("setup");
  screen.Setup();

}

void loop() 
{
  int8_t i;

  for(i = 0; i < 30; i++)
  {
    screen.PrintBmp(1, WHITE, RED, 0, 0);
    delay(500); 
    screen.PrintBmp(1, RED, WHITE, 0, 0);
    delay(500); 
  }

  for(i = -26; i < 35; i++)
  {
    screen.PrintBmp(0, RED, WHITE, i, 0);
    delay(50); 
  }

  for(i = -26; i < 35; i++)
  {
    screen.PrintCar(RED, i, -4);
    delay(50); 
  }

  for(i = -26; i < 35; i++)
  {
    screen.PrintBike(BLUE, i, 0);
    delay(50); 
  }

  //screen.PrintOoK(0);
  //delay(1000);  
  //screen.PrintOoK(1);
  //delay(1000);  
  //screen.PrintOoK(2);
  //delay(1000);  
  //screen.PrintOoK(3);
  //delay(1000);  
  //screen.PrintOoK(4);
  //delay(1000);
  //screen.PrintOoK(5);
  //delay(1000);
  //screen.PrintFull(7, 7, 0);
  //delay(200);
  //screen.PrintFull(0, 7, 7);
  //delay(200);
  //screen.PrintFull(7, 0, 7);
  //delay(200);
  //screen.PrintTwoTimes(timeByBike.GetValue(), timeByCar.GetValue());
  //delay(1000);

}

