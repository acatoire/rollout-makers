/*
   Test for web server

*/

#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <ESPmDNS.h>

#include <MyTravel.h>

#include "config.h"

void wifiConnect(void);

// Global declaration
const int led = 13;

bool firstTime = true;


WiFiClientSecure client;
String key = GOOGLE_MAP_API_KEY;
MyTravel travel(client, key);

void setup(void) 
{
  // Board config
  pinMode(led, OUTPUT);
  digitalWrite(led, 0);
  
  Serial.begin(115200);

  wifiConnect();
}


void loop(void) 
{
  DirectionsResponse info;

  if(firstTime)
  {
    firstTime = false;

    info = travel.GetInfoByBike();
    Serial.println("Time by bike: (string)" + info.duration_text);
    Serial.println("Distance by bike: " + info.distance_text);
    Serial.println(info.duration_value);
    
    info = travel.GetInfoByCar();
    Serial.println("Time by car: " + info.durationTraffic_text);
    Serial.println("Distance by car: " + info.distance_text);
    Serial.println(info.durationTraffic_value);
  }

}


// **************************** Functions ******************************//
void wifiConnect(void)
{
  // Config
  const char *ssid = WIFI_SSID;
  const char *password = WIFI_PASS;
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  
}
