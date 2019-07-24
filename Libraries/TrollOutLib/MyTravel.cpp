/*
  TestClass
*/

#include "Arduino.h"

#include "MyTravel.h"


MyTravel::MyTravel(WiFiClientSecure &client, String apiKey):
  api_m(apiKey, client)
{
  //These are all optional (although departureTime needed for traffic)
  inputOptions_m.departureTime = "now"; //can also be a future timestamp
  inputOptions_m.trafficModel = "best_guess"; //Defaults to this anyways
  inputOptions_m.avoid = "ferries";
  inputOptions_m.units = "metric";
  inputOptions_m.travelMode = "driving";

  
  bikeRefreshFlag_m = true;
  carRefreshFlag_m = true;
}

void MyTravel::Init(String from, String to)
{
  String origin_m       = from;
  String destination_m  = to;

}

// TODO return a struct with (timeInMinutes, DistanceInKmx10)
String MyTravel::GetDurationByBike(void)
{
  String out;
  DirectionsResponse responseFinal;
  DirectionsResponse response;

  inputOptions_m.travelMode = "bicycling";
  inputOptions_m.trafficModel = "";

  Serial.print("start bike request ");
  if(bikeRefreshFlag_m == true)
  {
	  // Send request
      response = api_m.directionsApi(origin_m, destination_m, inputOptions_m);
      responseFinal = response;
      response = api_m.directionsApi(origin_m, destination_m, inputOptions_m); 
	  bikeRefreshFlag_m = false;
	  api_lasttime_m = millis();
  }
  else if (millis() > (api_lasttime_m + api_mtbs_m))
  {
	  //next request is allowed
	  bikeRefreshFlag_m = true;
  }
  else
  {
       //nothing to do
  }

}
  
// TODO return a struct with (timeInMinutes, DistanceInKmx10)
DirectionsResponse MyTravel::GetInfoByBike(void)
{
  String out;
  DirectionsResponse responseFinal;
  DirectionsResponse response;

  inputOptions_m.travelMode = "bicycling";
  inputOptions_m.trafficModel = "";

  Serial.println("start bike request ");
  if(bikeRefreshFlag_m == true)
  {
	  // Send request
      response = api_m.directionsApi(origin_m, destination_m, inputOptions_m);
      responseFinal = response;
      response = api_m.directionsApi(origin_m, destination_m, inputOptions_m); 
	  bikeRefreshFlag_m = false;
	  api_lasttime_m = millis();
  }
  else if (millis() > (api_lasttime_m + api_mtbs_m))
  {
	  //next request is allowed
	  bikeRefreshFlag_m = true;
  }
  else
  {
       //nothing to do
  }
  
    Serial.println("end bike request ");
    responseFinal = ConvertValueintoMinutesAndKilometers(responseFinal);
  return responseFinal;

}


String MyTravel::GetDurationByCar (void)
{
  String out;

  DirectionsResponse responseFinal;
  DirectionsResponse response;

  inputOptions_m.travelMode = "driving"; 
  inputOptions_m.trafficModel = "best_guess";

  if(carRefreshFlag_m == true)
  {
	  // Send request
      response = api_m.directionsApi(origin_m, destination_m, inputOptions_m);
      responseFinal = response;
      response = api_m.directionsApi(origin_m, destination_m, inputOptions_m);

      api_lasttime_m = millis();
	  carRefreshFlag_m = false;
  }
  else if (millis() > (api_lasttime_m + api_mtbs_m))
  {
	  //next request is allowed
	  carRefreshFlag_m = true;
  }
  else
  {
       //nothing to do
  }
  
  out = responseFinal.duration_text; 

  return out;
}


DirectionsResponse MyTravel::GetInfoByCar (void)
{
  String out;

  DirectionsResponse responseFinal;
  DirectionsResponse response;

  inputOptions_m.travelMode = "driving"; 
  inputOptions_m.trafficModel = "best_guess";

  if(carRefreshFlag_m == true)
  {
	  // Send request
      response = api_m.directionsApi(origin_m, destination_m, inputOptions_m);
      responseFinal = response;
      response = api_m.directionsApi(origin_m, destination_m, inputOptions_m);

      api_lasttime_m = millis();
	  carRefreshFlag_m = false;
  }
  else if (millis() > (api_lasttime_m + api_mtbs_m))
  {
	  //next request is allowed
	  carRefreshFlag_m = true;
  }
  else
  {
       //nothing to do
  }
  
  responseFinal = ConvertValueintoMinutesAndKilometers(responseFinal);
  return responseFinal;
}

uint8_t MyTravel::GetInfo (uint8_t type)
{
  // todo common code between bike and car
}

DirectionsResponse MyTravel::ConvertValueintoMinutesAndKilometers(DirectionsResponse info)
{
  info.distance_value = info.distance_value/100; //convert meters into kilometers/10
  
  info.duration_value = info.duration_value/60; // convert second into minutes

  if(info.duration_value%60>=30)//round the value
  {
	  info.duration_value++;
  }
  else
  {
	  //nothing to do
  }
  info.durationTraffic_value = info.durationTraffic_value/60; // convert second into minutes
  if(info.durationTraffic_value%60>=30)//round the value
  {
	  info.durationTraffic_value++;
  }
  else
  {
	  //nothing to do
  } 
  return info;

}


