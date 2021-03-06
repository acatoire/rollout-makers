/*
   Test for web server

*/

#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>

#include "config.h"

void wifiConnect(void);
void serverConfig(void);

// Pages function prototypes
void pageRoot(void);
void pageMinion(void);
void pageText(void);
void pageGraph(void);
void pageError(void);

// Config
const char *ssid = WIFI_SSID;
const char *password = WIFI_PASS;

// Global declaration
WebServer server(80);
const int led = 13;


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


void pageMinion(void) 
{
  String out = "<img class=\"fit-picture\" src=";
  out += "https://www.imagenspng.com.br/wp-content/uploads/2015/07/minions-02.png";
  out += " alt=\"Minion\" />";

  server.send(200, "text/html", out);
}


void pageText(void) 
{
  String out = "Test text";

  server.send(200, "text/plain", out);
}


void pageGraph(void) 
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
  server.on("/minion", pageMinion);
  server.on("/text", pageText);
  server.on("/test.svg", pageGraph);
  server.on("/inline", []() {
    server.send(200, "text/plain", "this works as well");
  });
  server.onNotFound(pageError);
  server.begin();
  Serial.println("HTTP server started");
}
