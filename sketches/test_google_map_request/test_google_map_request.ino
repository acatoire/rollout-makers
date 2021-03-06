/*
   Copyright (c) 2015, Majenko Technologies
   All rights reserved.

   Redistribution and use in source and binary forms, with or without modification,
   are permitted provided that the following conditions are met:
*/

#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiClientSecure.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <GoogleMapsDirectionsApi.h>

#include "config.h"

void wifiConnect(void);
void serverConfig(void);

// Pages function prototypes
void pageRoot(void);
void pageMinion(void);
void pageText(void);
void drawGraph(void);
void pageError(void);

// Config
const char *ssid = WIFI_SSID;
const char *password = WIFI_PASS;

#define GOOGLE_MAP_API_KEY "HereYourGoogleMapAPI" //write your google map APi between the " "

// Global declaration
WebServer server(80);
const int led = 13;

WiFiClientSecure client;
GoogleMapsDirectionsApi api(GOOGLE_MAP_API_KEY, client);

//flag for debug
bool request_flag = true;

//Google map Inputs

String origin = "140 Boulevard Robert Schuman, Nantes";
String destination = "17 Rue de la Petite Baratte, 44315 Nantes";

//google map output
DirectionsResponse responseCar;
DirectionsResponse responseBicycling;
// For both origin and destination you should be
// able to pass multiple seperated by a |
// e.g destination1|destination2 etc

//Free Google Maps Api only allows for 2500 "elements" a day, so carful you dont go over
int api_mtbs = 10000; //mean time between api requests
long api_lasttime = 0;   //last time api request has been done
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
  serverConfig();

  //These are all optional (although departureTime needed for traffic)
  inputOptions.departureTime = "now"; //can also be a future timestamp
  inputOptions.trafficModel = "best_guess"; //Defaults to this anyways
  inputOptions.avoid = "ferries";
  inputOptions.units = "metric";
  inputOptions.travelMode = "driving"; //BICYCLING
}


void loop(void)
{
  server.handleClient();
}


// **************************** PAGES ******************************//
void pageRoot(void)
{
  Serial.println("Page root requested");
  digitalWrite(led, 1);
  char temp[400];
  int sec = millis() / 1000;
  int min = sec / 60;
  int hr = min / 60;

  snprintf(temp, 400,

           "<html>\
  <head>\
    <meta http-equiv='refresh' content='5'/>\
    <title>ESP32 Demo</title>\
    <style>\
      body { background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; }\
    </style>\
  </head>\
  <body>\
    <h1>Hello from ESP32!</h1>\
    <p>Uptime: %02d:%02d:%02d</p>\
    <img src=\"/test.svg\" />\
  </body>\
</html>",

           hr, min % 60, sec % 60
          );
  server.send(200, "text/html", temp);
  digitalWrite(led, 0);
}


void pageError(void)
{
  digitalWrite(led, 1);
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";

  for (uint8_t i = 0; i < server.args(); i++)
  {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }

  server.send(404, "text/plain", message);
  digitalWrite(led, 0);
}


void pageText(void)
{
  String out = "Test text";

  server.send(200, "text/plain", out);
}

void pageItineraireCar(void)
{
  DirectionsResponse response;
  String out = "map not working for now ";
  unsigned long timeNow = millis();
  if ((timeNow > api_lasttime + api_mtbs))
  {
    //////debug//////

    inputOptions.travelMode = "driving"; 
    response = api.directionsApi(origin, destination, inputOptions);
    responseCar = response;
    response = api.directionsApi(origin, destination, inputOptions);
    //////debug end////////
    /*if ((millis() > api_lasttime + api_mtbs))  {
      checkGoogleMaps(out);
      api_lasttime = millis();
      }*/
    api_lasttime = timeNow + api_mtbs;
  }
  else
  {

  }
  out = "Getting traffic from " + origin + " to " + destination + '\r';
  out += "Duration in car: " + responseCar.durationTraffic_text + '\r';
  out += "Distance: " + responseCar.distance_text + '\r';
  server.send(2000, "text/plain", out);
}

void pageItineraireBicycling(void)
{
  DirectionsResponse response;
  String out = "map not working for now ";
  if ((millis() > api_lasttime + api_mtbs))
  {
    //////debug//////

    inputOptions.travelMode = "bicycling";
    inputOptions.trafficModel = "";
    response = api.directionsApi(origin, destination, inputOptions);
    responseBicycling = response;
    response = api.directionsApi(origin, destination, inputOptions);
    //////debug end////////
    /*if ((millis() > api_lasttime + api_mtbs))  {
      checkGoogleMaps(out);
      api_lasttime = millis();
      }*/
    api_lasttime = millis();
  }
  else
  {

  }
  out = "Getting traffic from " + origin + " to " + destination + '\r';
  out += "Duration in bicycling: " + responseBicycling.duration_text + '\r';
  out += "Distance: " + responseBicycling.distance_text + '\r';
  server.send(2000, "text/plain", out);
}

void drawGraph(void)
{
  String out = "";
  char temp[100];
  out += "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" width=\"400\" height=\"150\">\n";
  out += "<rect width=\"400\" height=\"150\" fill=\"rgb(250, 230, 210)\" stroke-width=\"1\" stroke=\"rgb(0, 0, 0)\" />\n";
  out += "<g stroke=\"black\">\n";
  int y = rand() % 130;
  for (int x = 10; x < 390; x += 10)
  {
    int y2 = rand() % 130;
    sprintf(temp, "<line x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\" stroke-width=\"1\" />\n", x, 140 - y, x + 10, 140 - y2);
    out += temp;
    y = y2;
  }
  out += "</g>\n</svg>\n";

  server.send(200, "image/svg+xml", out);
}


// **************************** Functions ******************************//
void wifiConnect(void)
{

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

void serverConfig(void)
{
  if (MDNS.begin("esp32"))
  {
    Serial.println("MDNS responder started");
  }


  // Server request management
  server.on("/", pageRoot);
  server.on("/itineraireCar", pageItineraireCar);
  server.on("/itineraireBicycling", pageItineraireBicycling);
  server.on("/text", pageText);
  server.on("/test.svg", drawGraph);
  server.on("/inline", []() {
    server.send(200, "text/plain", "this works as well");
  });
  server.onNotFound(pageError);
  server.begin();
  Serial.println("HTTP server started");
}

/*String checkGoogleMaps(String out) {

  out += "Getting traffic for " + origin + " to " + destination;
  String responseString = api.distanceMatrix(origin, destination, departureTime, trafficModel);
  DynamicJsonBuffer jsonBuffer;
  JsonObject& response = jsonBuffer.parseObject(responseString);
  if (response.success()) {
    if (response.containsKey("rows")) {
      JsonObject& element = response["rows"][0]["elements"][0];
      String status = element["status"];
      if (status == "OK")
      {
        String distance = element["distance"]["text"];
        String duration = element["duration"]["text"];
        String durationInTraffic = element["duration_in_traffic"]["text"];

        out += "Distance: " + distance;
        out += "Distance: " + duration;
        out += "Distance: " + durationInTraffic;
      }
      else {
        out = "Got an error status: " + status;
      }
    } else {
      out = "Reponse did not contain rows";
    }
  } else {
    out = "Failed to parse Json";
  }
  out = "function done";
  return out;
  }*/
