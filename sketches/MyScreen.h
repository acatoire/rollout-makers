/*
  Morse.h - Library for flashing Morse code.
  Created by David A. Mellis, November 2, 2007.
  Released into the public domain.
*/
#ifndef MyScreen_h
#define MyScreen_h

#include "Arduino.h"

#include <RGBmatrixPanel.h>

#define byCar   0
#define byBike  1


#define CLK 4
#define OE   0
#define LAT 2
#define A   12
#define B   13
#define C   14

class MyScreen
{
  public:
    MyScreen(int pin);
    void Setup(void);
    void Clear(void);
    void Show(void);
    void Print_bike_car (uint8_t minutesByBike, uint8_t minutesByCar);

  private:
    int pin_m;
    RGBmatrixPanel matrix_m;
};

#endif // MyScreen_h

