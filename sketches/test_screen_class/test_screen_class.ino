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
  uint8_t j;
  
  for(i = -7; i < 32; i++)
  {
    screen.Clear();
    screen.PrintStickMan(i, GREEN, i, 0);
    screen.Update();
    delay(50); 
  }

    
  for(i = -7; i < 32; i++)
  {
    screen.Clear();
    screen.PrintFull(WHITE);
    screen.PrintBmp(1, RED, 0, 0);
    screen.PrintStickMan(i, GREEN, i, 0);
    delay(50); 
    screen.Update();
  }

  for(j = 0; j<110;j++)
  {
    screen.Clear();
    screen.PrintBattery(j, WHITE, 0, 0);
    delay(50); 
    screen.Update();
  }

  //for(i = 0; i < 10; i++)
  //{
  //  screen.PrintBmp(1, WHITE, RED, 0, 0);
  //  delay(500); 
  //  screen.PrintBmp(1, RED, WHITE, 0, 0);
  //  delay(500); 
  //}

  //for(i = -26; i < 35; i++)
  //{
  //  screen.PrintBmp(0, RED, WHITE, i, 0);
  //  delay(50); 
  //}
//
  //for(i = -26; i < 35; i++)
  //{
  //  screen.PrintCar(RED, i, -4);
  //  delay(50); 
  //}
//
  //for(i = -26; i < 35; i++)
  //{
  //  screen.PrintBike(BLUE, i, 0);
  //  delay(50); 
  //}

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
