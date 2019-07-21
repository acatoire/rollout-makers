/*
  Morse.h - Library for flashing Morse code.
  Created by David A. Mellis, November 2, 2007.
  Released into the public domain.
*/
#ifndef MyScreen_h
#define MyScreen_h


#define _CLK 4
#define _OE   0
#define _LAT 2
#define _A   12
#define _B   13
#define _C   14
const uint8_t rgbpins[] = { 17,18,19,21,22,23 };


class MyScreen
{
  public:
    MyScreen(void);
    void Setup(void);
    void Clear(void);
    void Update(void);
    void PrintFull(uint8_t R, uint8_t G, uint8_t B);
    void PrintTwoTimes(uint8_t minutesByBike, uint8_t minutesByCar);
    void PrintOoK(uint8_t type);
  
  private:
    RGBmatrixPanel *matrix_m = new RGBmatrixPanel(_A, _B, _C, _CLK, _LAT, _OE, true, (uint8_t *)rgbpins);
};
#endif // MyValue_h

