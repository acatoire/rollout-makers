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

  screen.PrintBike(BLUE);
  delay(5000); 
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

