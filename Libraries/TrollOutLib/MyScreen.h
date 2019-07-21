/*
  MyScreen
  Screen management class
*/

#ifndef MyScreen_h
#define MyScreen_h

// Color definitions in RGB 656 (http://www.barth-dev.de/online/rgb565-color-picker/)
#define BLACK    0x0000
#define BLUE     0x001F
#define RED      0xF800
#define GREEN    0x07E0
#define CYAN     0x07FF
#define MAGENTA  0xF81F
#define YELLOW   0xFFE0 
#define WHITE    0xFFFF


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


    
    void PrintOoK_empty(uint16_t color);
};
#endif // MyValue_h

