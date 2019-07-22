/*
  TestClass
*/

#include "Arduino.h"

#include "MyTravel.h"


MyTravel::MyTravel(WiFiClientSecure client, String apiKey):
  api_m(apiKey, client)
{
  //These are all optional (although departureTime needed for traffic)
  inputOptions_m.departureTime = "now"; //can also be a future timestamp
  inputOptions_m.trafficModel = "best_guess"; //Defaults to this anyways
  inputOptions_m.avoid = "ferries";
  inputOptions_m.units = "metric";
  inputOptions_m.travelMode = "driving";

}

void MyTravel::Init(String from, String to)
{

  String origin_m       = from;
  String destination_m  = to;

}

// TODO return a struct with (timeInMinutes, DistanceInKmx10)
String MyTravel::GetInfoByBike(void)
{
  String out;

  DirectionsResponse responseFinal;
  DirectionsResponse response;

  inputOptions_m.travelMode = "bicycling";
  inputOptions_m.trafficModel = "";

  if (millis() < (api_lasttime_m + api_mtbs_m))
  {
    // Wait request to be allowed
    delay(api_mtbs_m);
  }
  else
  {

  }
    
  // Send request
  response = api_m.directionsApi(origin_m, destination_m, inputOptions_m);
  responseFinal = response;
  response = api_m.directionsApi(origin_m, destination_m, inputOptions_m);

  api_lasttime_m = millis();
  
  // Distance todo in struct
  //out = responseFinal.distance_value;
  // Time
  // out = responseFinal.duration_value;// TODO see why strange value in int

  out = responseFinal.duration_text; 

  return out;

}


String MyTravel::GetInfoByCar (void)
{
  String out;

  DirectionsResponse responseFinal;
  DirectionsResponse response;

  inputOptions_m.travelMode = "driving"; 
  inputOptions_m.trafficModel = "best_guess";

  if (millis() < (api_lasttime_m + api_mtbs_m))
  {
    // Wait request to be allowed
    delay(api_mtbs_m);
  }
  else
  {
    
  }
  // Send request
  response = api_m.directionsApi(origin_m, destination_m, inputOptions_m);
  responseFinal = response;
  response = api_m.directionsApi(origin_m, destination_m, inputOptions_m);

  api_lasttime_m = millis();

  // Distance todo in struct
  //out = responseFinal.distance_value;
  // Time
  // out = responseFinal.duration_value;// TODO see why strange value in int
  
  out = responseFinal.duration_text; 

  return out;
}


uint8_t MyTravel::GetInfo (uint8_t type)
{
  // todo common code between bike and car
}


