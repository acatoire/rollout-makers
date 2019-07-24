/*
  SensorClass
*/

#include "Arduino.h"
#include "MySensor.h"

#define MAX_LONG	0xFFFFFFFF

MySensor::MySensor(uint8_t pin, uint16_t timeout)
{
  pinMode(pin, INPUT);
  pin_m = pin;
  timeout_m = timeout;
  state_m = 0;
  lastDetection_m = 0;
}


uint8_t MySensor::GetState (void)
{
	long currentTime = millis();
	
	//sensor detection OR timeout not elapsed
	if (digitalRead(pin_m) == HIGH)
	{
		Serial.println("Sensor : Input detection.\n");
		state_m = true;
		lastDetection_m = currentTime; //save the last detection
	}
	else if(lastDetection_m != 0)
	{
		if (((currentTime - lastDetection_m) > timeout_m) ||
			(((MAX_LONG - lastDetection_m) + currentTime) > timeout_m))
		{
			Serial.println("Sensor : End of  timeout.\n");
			lastDetection_m = 0;
			state_m = false;
		}
		else
		{
			Serial.println("Sensor : Timeout active\n");
			state_m = true;
		}
	}
	else
	{
		state_m = false;
	}
	return state_m;
}

