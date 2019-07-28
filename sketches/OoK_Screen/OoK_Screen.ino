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

// screens
#define WAIT       0
#define RUN        1
#define FAIL       2
#define SUCCESS    3
#define DRAW       4

#define SCREEN_ID             V10
#define SCREEN_TEST_TOTAL     V11
#define SCREEN_TEST_ACTUAL    V12

uint8_t screen_id           = 0;
uint8_t screen_test_total   = 0;
uint8_t screen_test_actual  = 0;


// Config
const char wifiSsid[] = WIFI_SSID;
const char wifiPassword[] = WIFI_PASS;
char blynkAuth[] = "xbzggg5NU6Ye9G4XD6utHK6l_3nqb5Lr";

int8_t coorX = -7;
bool newValue = false;
uint8_t buttonValue = 0;
uint8_t stepValue = 0;
uint8_t valueDisplay = 0;
uint8_t dropMenuValue = 0;

BlynkTimer timerScreenUpdate;
BlynkTimer timerValueUpdate;
MyScreen screen;

void Draw(uint8_t id);


BLYNK_WRITE(SCREEN_ID)
{
  screen_id = param.asInt();
  newValue = true;
  Serial.print("screen_id value is: ");
  Serial.println(screen_id);
  
}

BLYNK_WRITE(SCREEN_TEST_TOTAL)
{
  screen_test_total = param.asInt(); 
  newValue = true;
  Serial.print("screen_test_total value is: ");
  Serial.println(screen_test_total);
  
}

BLYNK_WRITE(SCREEN_TEST_ACTUAL)
{
  screen_test_actual = param.asInt(); 
  newValue = true;
  Serial.print("screen_test_actual value is: ");
  Serial.println(screen_test_actual);
  
}


void setup(void) 
{
  Serial.begin(115200);
  Serial.print("Setup Start\n");

  Blynk.begin(blynkAuth, wifiSsid, wifiPassword);
  timerScreenUpdate.setInterval(100L, screenUpdate);
  timerValueUpdate.setInterval(5000L, valueUpdate);

  screen.Setup();

  Serial.print("Setup Done\n");

}

void valueUpdate(void)
{

  Blynk.syncAll();

}

void screenUpdate(void)
{

  screen.Clear();
    
  switch (screen_id)
  {
    case WAIT :
      Draw(0);

    break;

    case RUN :
      screen.PrintTestStatus(screen_test_actual, screen_test_total);

    break;
    
    case FAIL :
      screen.PrintOoK(OoK_Fail);

    break;
    
    case SUCCESS :
      screen.PrintOoK(OoK_Success);

    break;
    
    case DRAW :
      Draw(screen_test_actual);

    break;
  }

  screen.Update();
}

void Draw(uint8_t id)
{
  switch (id)
  {
    case 0:
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

      break;

    case 1:
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

    case 2:
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

    case 3:

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

    case 4:

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

  coorX++;
}



void loop(void) 
{
  Blynk.run();
  timerScreenUpdate.run();
  timerValueUpdate.run();
}


