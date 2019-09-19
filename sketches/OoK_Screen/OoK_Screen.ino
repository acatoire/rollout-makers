/*
   Test for web server

*/

#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <ESPmDNS.h>

#include <BlynkSimpleEsp32.h>
#include <MyScreen.h>
#include <MyTravel.h>

#include "config.h"

// Screen Config
#define SCREEN_ID     V10
#define SCREEN_OPTION  V11
#define SCREEN_ACTUAL V12
#define SCREEN_MAX    V13
#define SCREEN_TEXT   V14

uint8_t screen_id      = 0;
uint8_t screen_option  = 0;
uint8_t screen_actual  = 0;
uint8_t screen_max     = 0;
uint8_t* screen_text   = (uint8_t*)"1234567890ABCDEFGHIJ";

// IDs definition
enum ScreenId
{
  SCREEN_WELCOME     = 0,
  SCREEN_TESTBENCH   = 1,
  SCREEN_JENKINS     = 2,
  SCREEN_MOBILITY    = 3,
  SCREEN_BATTERY     = 4,
  SCREEN_PICT        = 5
};

enum MobilityId
{
  MOB_WALK   = 1,
  MOB_BIKE   = 2,
  MOB_TRAM   = 3,
  MOB_CAR    = 4
};

enum PictureId
{
  PICT_NO            = 0,
  PICT_WALKING_MAN   = 1,
  PICT_BIKE          = 2,
  PICT_CAR           = 3,
  PICT_TRAIN         = 4
};

enum TestBenchScreenId
{
  TEST_OFF     = 0,
  TEST_RUN     = 1,
  TEST_FAILED  = 2,
  TEST_SUCCESS = 3
};


// Config
const char wifiPassword[] = WIFI_PASS;
const char wifiSsid[] = WIFI_SSID;
char blynkAuth[] = "xbzggg5NU6Ye9G4XD6utHK6l_3nqb5Lr";

WiFiClientSecure client;
String key = GOOGLE_MAP_API_KEY;
MyTravel travel(client, key);

bool newValue = false;
uint16_t loopId = 0;

BlynkTimer timerScreenUpdate;
BlynkTimer timerValueUpdate;
MyScreen screen;


// Get the server data

BLYNK_WRITE(SCREEN_ID)
{
  screen_id = param.asInt();
  newValue = true;
  Serial.print("screen_id value is: ");
  Serial.println(screen_id);
}

BLYNK_WRITE(SCREEN_OPTION)
{
  screen_option = param.asInt();
  newValue = true;
  Serial.print("screen_option value is: ");
  Serial.println(screen_option);
}

BLYNK_WRITE(SCREEN_ACTUAL)
{
  screen_actual = param.asInt();
  newValue = true;
  Serial.print("screen_actual value is: ");
  Serial.println(screen_actual);
}

BLYNK_WRITE(SCREEN_MAX)
{
  screen_max = param.asInt();
  newValue = true;
  Serial.print("screen_max value is: ");
  Serial.println(screen_max);
}

BLYNK_WRITE(SCREEN_TEXT)
{
  screen_text = (uint8_t*)param.asString();
  newValue = true;
  Serial.print("screen_text value is: ");
  Serial.println((char*)screen_text);
}

// Setup
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

// Function to periodically update value from server
void valueUpdate(void)
{

  Blynk.syncAll();

}

// Function to periodically update the screen
void screenUpdate(void)
{
  static DirectionsResponse infoBike;
  static DirectionsResponse infoCar;
  static bool requestInfo = true;
  screen.Clear();

  switch (screen_id)
  {
    case SCREEN_WELCOME :

      //screen.PrintFull(WHITE);
      //screen.PrintBmp(1, RED, 0, 0);
      screen.PrintStickMan(loopId, GREEN, loopId, 0);

      if (32 == loopId)
      {
        loopId = -7;
      }
      else
      {
        loopId++;
      }


      break;

    case SCREEN_TESTBENCH :
      switch (screen_id)
      {
        case TEST_RUN :
          screen.PrintTestStatus(screen_actual, screen_max);
          break;

        case TEST_FAILED :
          screen.PrintOoK(OoK_Fail);
          break;

        case TEST_SUCCESS :
          screen.PrintOoK(OoK_Success);
          break;

        case TEST_OFF :
        default:
          screen.Clear();
          break;
      }
      break;

    case SCREEN_JENKINS :
      screen.PrintJenkins(screen_text);
      break;

    case SCREEN_MOBILITY :

      if (requestInfo)
      {
        screen.PrintLoading();
        infoBike = travel.GetInfoByBike();
        infoCar = travel.GetInfoByCar();
        requestInfo = false;
      }//else NTD

      if (loopId < 40)
      {
        screen.PrintTwoTimes(infoBike.duration_value, infoCar.durationTraffic_value);
      }
      else if (loopId < 80)
      {
        screen.PrintTwoDistance((infoBike.distance_value / 10), (infoCar.distance_value / 10)); //TODO : manage decimal value
      }
      else if (loopId < 120) 
      {
        screen.PrintTwoEmissionGas((infoBike.distance_value / 10), 10, 0); //bike 10g.co2/km
      }
      else if (loopId < 160)
      {
         screen.PrintTwoEmissionGas((infoCar.distance_value / 10), 150, 1); //car 150 g.co2/km
      }
      else if (loopId < 200) 
      {
        screen.PrintBike(GREEN, 4, 0);
      }
      else if (loopId < 240)
      {
        screen.PrintCar(RED, 3, -2);
      }

      loopId++;
      loopId = loopId % 240;
      break;

    case SCREEN_BATTERY :
      screen.PrintBattery(screen_actual * 10, WHITE, 0, 0);
      break;

    case SCREEN_PICT :
      screen.PrintBmp(screen_option, WHITE, RED, 0);
      break;
  }

  screen.Update();
}


void loop(void)
{
  Blynk.run();
  timerScreenUpdate.run();
  timerValueUpdate.run();
}
