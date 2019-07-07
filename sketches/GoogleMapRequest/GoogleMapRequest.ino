/*
   Copyright (c) 2015, Majenko Technologies
   All rights reserved.

   Redistribution and use in source and binary forms, with or without modification,
   are permitted provided that the following conditions are met:

 * * Redistributions of source code must retain the above copyright notice, this
     list of conditions and the following disclaimer.

 * * Redistributions in binary form must reproduce the above copyright notice, this
     list of conditions and the following disclaimer in the documentation and/or
     other materials provided with the distribution.

 * * Neither the name of Majenko Technologies nor the names of its
     contributors may be used to endorse or promote products derived from
     this software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
   ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
   WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
   DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
   ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
   (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
   LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
   ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
   SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <GoogleMapsApi.h>

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

#define GOOGLE_MAP_API_KEY "AIzaSyDLo1YPxFG6HKQd-uQ3darr7jfa8TgFswA" //

// Global declaration
WebServer server(80);
const int led = 13;

WiFiClient client;
GoogleMapsApi api(GOOGLE_MAP_API_KEY, client);

//flag for debug
bool request_flag = true;

//Inputs

String origin = "Nantes";//"143 Boulevard Robert Schuman, Nantes";
String destination = "Carquefou";// "17 Rue de la Petite Baratte, 44315 Nantes";
// For both origin and destination you should be
// able to pass multiple seperated by a |
// e.g destination1|destination2 etc

//Free Google Maps Api only allows for 2500 "elements" a day, so carful you dont go over
int api_mtbs = 6000; //mean time between api requests
long api_lasttime = 0;   //last time api request has been done
bool firstTime = true;


//Optional
String departureTime = "now"; //This can also be a timestamp, needs to be in the future for traffic info
String trafficModel = "best_guess"; //defaults to this anyways. see https://developers.google.com/maps/documentation/distance-matrix/intro#

void setup(void)
{
  // Board config
  pinMode(led, OUTPUT);
  digitalWrite(led, 0);

  Serial.begin(115200);
  wifiConnect();
  serverConfig();

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


void pageItineraire(void)
{
  String out = "map not working for now ";

  //////debug//////
  if (request_flag)
  {
    out = "Getting traffic from" + origin + " to " + destination;
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
          out += "Got an error status: " + status;
        }
      } else {
        out += "Reponse did not contain rows";
      }
    } else {
      //out += "Failed to parse Json";
    }
    request_flag = false;
  }

  //////debug end////////
  /*if ((millis() > api_lasttime + api_mtbs))  {
    checkGoogleMaps(out);
    api_lasttime = millis();
    }*/
  server.send(200, "text/plain", out);
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
  server.on("/itineraire", pageItineraire);
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
