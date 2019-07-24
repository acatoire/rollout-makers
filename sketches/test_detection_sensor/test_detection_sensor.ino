// testshapes demo for Adafruit RGBmatrixPanel library.
// Demonstrates the drawing abilities of the RGBmatrixPanel library.
// For 16x32 RGB LED matrix:
// http://www.adafruit.com/products/420

// Written by Limor Fried/Ladyada & Phil Burgess/PaintYourDragon
// for Adafruit Industries.
// BSD license, all text above must be included in any redistribution.

// Display OoK logo on led matrix


#include <MySensor.h>
#include <MyScreen.h>

#define SENSOR_PIN      34    //output 34 as sensor input
#define SENSOR_TIMEOUT  10000 //10 seconds between two detection before end of detection

MySensor sensor(SENSOR_PIN,SENSOR_TIMEOUT);
MyScreen screen;

void setup() 
{

  Serial.begin(115200);
  Serial.println("setup");
  screen.Setup();
}

void loop() 
{
    if(sensor.GetState() == true)
    {
      screen.Clear();
      screen.PrintCar(RED, 0, 0);
      screen.Update();
    }
    else
    {
      screen.Clear();
      screen.PrintBike(BLUE, 0, 0);
      screen.Update();
    }
    delay(200);
}
