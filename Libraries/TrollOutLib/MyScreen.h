/*
  MyScreen
  Screen management class
*/

#ifndef MyScreen_h
#define MyScreen_h

#include <RGBmatrixPanel.h>
#include <MyScreenBmp.h>

// Color definitions in RGB 656 (http://www.barth-dev.de/online/rgb565-color-picker/)
#define BLACK    0x0000
#define BLUE     0x001F
#define RED      0xF800
#define GREEN    0x07E0
#define CYAN     0x07FF
#define MAGENTA  0xF81F
#define YELLOW   0xFFE0 
#define WHITE    0xFFFF


#define OoK_Fail      2
#define OoK_Success   4


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

    void PrintFull(uint16_t color);
    void PrintFull(uint8_t R, uint8_t G, uint8_t B);
    void PrintTwoTimes(uint8_t minutesByBike, uint8_t minutesByCar);
    void PrintTwoDistance(uint8_t distanceByBike, uint8_t distanceByCar);
    void PrintTwoEmissionGas(uint8_t distance,uint8_t gas, uint8_t transportation);
    void PrintTestStatus(uint8_t actual, uint8_t total);
    void PrintJenkins(uint8_t * textToPrint);
    void PrintLoading(void);

    void PrintOoK_empty(uint16_t color);
    void PrintOoK(uint8_t type);
    void PrintBike(uint16_t color, int8_t decX, int8_t decY);
    void PrintCar(uint16_t color, int8_t decX, int8_t decY);
    void PrintBmp(uint8_t type, uint16_t color, int8_t decX, int8_t decY);
    void PrintStickMan(uint8_t frame, uint16_t color, int8_t decX, int8_t decY);
	void PrintBattery(uint8_t percentage, uint16_t shape_color, int8_t decX, int8_t decY);

  
  private:
    RGBmatrixPanel *matrix_m = new RGBmatrixPanel(_A, _B, _C, _CLK, _LAT, _OE, true, (uint8_t *)rgbpins);



};
#endif // MyValue_h

