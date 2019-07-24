/*
   Test for web server

*/

#include <WiFi.h>
#include <WiFiClient.h>
#include <ESPmDNS.h>

#include <WiFiClientSecure.h>
#include <GoogleMapsDirectionsApi.h>

#include "config.h"

void wifiConnect(void);

String GetTimeByBike(void);
String GetTimeByCar(void);

// Global declaration
const int led = 13;

WiFiClientSecure client;
GoogleMapsDirectionsApi api(GOOGLE_MAP_API_KEY, client);

//Google map Inputs
String origin = "143 Boulevard Robert Schuman, Nantes";
String destination = "17 Rue de la Petite Baratte, 44315 Nantes";


//Free Google Maps Api only allows for 2500 "elements" a day, so carful you dont go over
int api_mtbs = 10000; //mean time between api requests
bool firstTime = true;

//Optional
DirectionsInputOptions inputOptions;


void setup(void) 
{
  // Board config
  pinMode(led, OUTPUT);
  digitalWrite(led, 0);
  
  Serial.begin(115200);

  wifiConnect();


  //These are all optional (although departureTime needed for traffic)
  inputOptions.departureTime = "now"; //can also be a future timestamp
  inputOptions.trafficModel = "best_guess"; //Defaults to this anyways
  inputOptions.avoid = "ferries";
  inputOptions.units = "metric";
  inputOptions.travelMode = "driving"; //BICYCLING
}


void loop(void) 
{
  String time;

  if(firstTime)
  {
    firstTime = false;

    time = GetTimeByBike();
    Serial.printf("Time by bike:");
    Serial.println(time);

    sleep(10);

    time = GetTimeByCar();
    Serial.printf("Time by car:");
    Serial.println(time);
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


String GetTimeByCar(void)
{
  String out;

  DirectionsResponse responseCar;
  DirectionsResponse response;

  inputOptions.travelMode = "driving"; 
  inputOptions.trafficModel = "best_guess";
  response = api.directionsApi(origin, destination, inputOptions);
  responseCar = response;
  response = api.directionsApi(origin, destination, inputOptions);

  // Distance todo in struct
  //out = responseBicycling.distance_value;
  // Time
  //out = responseCar.duration_value; // TODO see why strange value in int
  
  out = responseCar.duration_text;

  return out;
}

String GetTimeByBike(void)
{
  String out;

  DirectionsResponse responseBicycling;
  DirectionsResponse response;

  inputOptions.travelMode = "bicycling";
  inputOptions.trafficModel = "";
  response = api.directionsApi(origin, destination, inputOptions);
  responseBicycling = response;
  response = api.directionsApi(origin, destination, inputOptions);

  // Distance todo in struct
  //out = responseBicycling.distance_value;
  // Time
  // out = responseBicycling.duration_value;

  out = responseBicycling.duration_text; // TODO see why strange value in int

  return out;
}
