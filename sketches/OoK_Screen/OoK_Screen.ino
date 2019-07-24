/*
   Test for web server

*/

#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <ESPmDNS.h>

#include <BlynkSimpleEsp32.h>
#include <MyScreen.h>

#include "config.h"

// Config
const char wifiSsid[] = WIFI_SSID;
const char wifiPassword[] = WIFI_PASS;
char blynkAuth[] = "xbzggg5NU6Ye9G4XD6utHK6l_3nqb5Lr";

int8_t coorX = -7;
bool newValue = false;
uint8_t buttonValue = 0;
uint8_t sliderValue = 0;
uint8_t dropMenuValue = 0;

BlynkTimer timer;
MyScreen screen;

// This function will be called every time Slider Widget
// in Blynk app writes values to the Virtual Pin 1
BLYNK_WRITE(V2)
{
  buttonValue = param.asInt();
  newValue = true;
  Serial.print("Button value is: ");
  Serial.println(buttonValue);
  
}

// This function will be called every time Slider Widget
// in Blynk app writes values to the Virtual Pin 1
BLYNK_WRITE(V1)
{
  sliderValue = param.asInt(); 
  newValue = true;
  Serial.print("Slider value is: ");
  Serial.println(sliderValue);
  
}

BLYNK_WRITE(V0)
{
  dropMenuValue = param.asInt();
  newValue = true;
  Serial.print("Drop list value is: ");
  Serial.println(dropMenuValue);
}

void setup(void) 
{
  Serial.begin(115200);
  Serial.print("Setup Start\n");

  Blynk.begin(blynkAuth, wifiSsid, wifiPassword);
  timer.setInterval(100L, screenUpdate);

  screen.Setup();

  Serial.print("Setup Done\n");

}

void screenUpdate()
{

  screen.Clear();
  switch (sliderValue)
  {
  case 0:
  case 1:
  case 2:
  case 3:
  case 4:
  case 5:
    screen.PrintOoK(sliderValue);
    //Serial.print("PrintOoK\n");

    break;
  case 6:
    if(newValue)
    {
      coorX = -7;
      newValue = false;
    }
    if(39 < coorX)
    {
      coorX = -7;
    }
    screen.PrintStickMan(coorX, BLUE, coorX, 0);
    //Serial.print("Sticky\n");
    break;
  case 7:
    if(newValue)
    {
      coorX = -26;
      newValue = false;
    }
    if(32 < coorX)
    {
      coorX = -26;
    }
    screen.PrintCar(RED, coorX, 0);
    //Serial.print("PrintCar\n");
    break;
  case 8:
    if(newValue)
    {
      coorX = -26;
      newValue = false;
    }
    if(32 < coorX)
    {
      coorX = -26;
    }
    screen.PrintBike(GREEN, coorX, 0);
    //Serial.print("PrintBike\n");
    break;
  case 9:
    if(newValue)
    {
      coorX = -24;
      newValue = false;
    }
    if(32 < coorX)
    {
      coorX = -24;
    }
    screen.PrintBmp(2, CYAN, coorX, 0);
    //Serial.print("PrintBike\n");
    break;
  
  default:
    break;
  }
  
  screen.Update();
  coorX++;
}


void loop(void) 
{
  Blynk.run();
  timer.run();
}


