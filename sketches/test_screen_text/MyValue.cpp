/*
  TestClass
*/

#include "Arduino.h"

#include "MyValue.h"

MyValue::MyValue(uint8_t value)
{

  value_m = value;

}


void MyValue::Clear() 
{

  value_m = 0;

}


void MyValue::Increment(int8_t value) 
{

  value_m = value_m + value;

}


void MyValue::Random(void) 
{

  value_m = random(10, 60);

}


uint8_t MyValue::GetValue (void)
{

  MyValue::Random();
  
  return value_m;

}

