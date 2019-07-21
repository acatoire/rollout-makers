/*
  Morse.h - Library for flashing Morse code.
  Created by David A. Mellis, November 2, 2007.
  Released into the public domain.
*/
#ifndef MyTravel_h
#define MyTravel_h


#include <WiFi.h>
#include <WiFiClient.h>
#include <ESPmDNS.h>

#include <WiFiClientSecure.h>
#include <GoogleMapsDirectionsApi.h>


class MyTravel
{
  public:
    MyTravel(String apiKey);
    void    Init(String from, String to);
    String GetInfoByBike(void);
    String GetInfoByCar (void);
  
  private:
    uint8_t GetInfo (uint8_t type);

    // Default value, replaced by Init()
    String origin_m       = "143 Boulevard Robert Schuman, Nantes";
    String destination_m  = "17 Rue de la Petite Baratte, 44315 Nantes";

    WiFiClientSecure client_m;
    String apiKey_m = "AIzaSyDLo1YPxFG6HKQd-uQ3darr7jfa8TgFswA";
    GoogleMapsDirectionsApi api_m(apiKey_m, client_m); //todo creat in constructor

    DirectionsInputOptions inputOptions_m;

    //Free Google Maps Api only allows for 2500 "elements" a day, so carful you dont go over
    uint16_t api_mtbs_m = 10000;   //mean time between api requests
    uint32_t api_lasttime_m = 0;   //last time api request has been done
    
};
#endif // MyValue_h

