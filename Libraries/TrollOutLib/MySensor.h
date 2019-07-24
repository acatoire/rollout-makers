/*
  sensor Library 
*/
#ifndef MySensor_h
#define MySensor_h


class MySensor
{
  public:
    MySensor(uint8_t pin, uint16_t timeout);
    uint8_t GetState (void);
  
  private: 
    uint8_t   	pin_m;				//sensor pin number
	uint16_t  	timeout_m;			//detection timeout
	bool 		state_m;			//sensor state
	long 		lastDetection_m;	//Last detection time
};
#endif // MyValue_h

