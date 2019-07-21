/*
  Morse.h - Library for flashing Morse code.
  Created by David A. Mellis, November 2, 2007.
  Released into the public domain.
*/
#ifndef MyValue_h
#define MyValue_h


class MyValue
{
  public:
    MyValue(uint8_t value);
    void    Clear(void);
    void    Increment(int8_t value);
    uint8_t GetValue (void);
  
  private:
    void    Random(void);
    
    uint8_t   value_m;
};
#endif // MyValue_h

