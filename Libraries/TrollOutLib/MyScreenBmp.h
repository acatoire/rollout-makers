
#ifndef _BMP_H
#define _BMP_H

#include "Arduino.h"

// Logo Adafruit
static const unsigned char PROGMEM logo16_adafruit_bmp[] =
{ B00000000, B11000000,
  B00000001, B11000000,
  B00000001, B11000000,
  B00000011, B11100000,
  B11110011, B11100000,
  B11111110, B11111000,
  B01111110, B11111111,
  B00110011, B10011111,
  B00011111, B11111100,
  B00001101, B01110000,
  B00011011, B10100000,
  B00111111, B11100000,
  B00111111, B11110000,
  B01111100, B11110000,
  B01110000, B01110000,
  B00000000, B00110000 };

// Check Pattern on 8bit wide, to be reproduce
static const unsigned char PROGMEM logo16_check_pattern_bmp[] =
{ B01010101,
  B10101010,
  B01010101,
  B10101010,
  B01010101,
  B10101010,
  B01010101,
  B10101010,
  B01010101,
  B10101010,
  B01010101,
  B10101010,
  B01010101,
  B10101010,
  B01010101,
  B10101010};

  // StickMan walking (7 frames)
  // StickMan frame 1
  static const unsigned char StickMan_1[] =
{ B00011100,
  B00100010,
  B00100010,
  B00100010,
  B00011100,
  B00001000,
  B00011100,
  B00101010,
  B01001011,
  B01001000,
  B00001000,
  B00010100,
  B00010010,
  B00100010,
  B00100001,
  B01000001};
// StickMan frame 2
  static const unsigned char StickMan_2[] =
{ B00011100,
  B00100010,
  B00100010,
  B00100010,
  B00011100,
  B00001000,
  B00011100,
  B00011100,
  B00101110,
  B00101000,
  B00001000,
  B00010100,
  B00010100,
  B00010010,
  B00100010,
  B01000010};
// StickMan frame 3
  static const unsigned char StickMan_3[] =
{ B00011100,
  B00100010,
  B00100010,
  B00100010,
  B00011100,
  B00001000,
  B00011100,
  B00011100,
  B00011100,
  B00011010,
  B00001000,
  B00001100,
  B00001100,
  B00010100,
  B00100100,
  B00000100};
// StickMan frame 4
  static const unsigned char StickMan_4[] =
{ B00011100,
  B00100010,
  B00100010,
  B00100010,
  B00011100,
  B00001000,
  B00011000,
  B00011000,
  B00011000,
  B00011000,
  B00001000,
  B00001100,
  B00001100,
  B00011000,
  B00111000,
  B00001000};
// StickMan frame 5
  static const unsigned char StickMan_5[] =
{ B00011100,
  B00100010,
  B00100010,
  B00100010,
  B00011100,
  B00001000,
  B00011000,
  B00011000,
  B00011100,
  B00011000,
  B00001000,
  B00001100,
  B00001110,
  B00001100,
  B00010000,
  B00010000};
// StickMan frame 6
  static const unsigned char StickMan_6[] =
{ B00011100,
  B00100010,
  B00100010,
  B00100010,
  B00011100,
  B00001000,
  B00011100,
  B00011100,
  B00101110,
  B00101000,
  B00001000,
  B00010100,
  B00010010,
  B00010100,
  B00100100,
  B00100000};
// StickMan frame 7
  static const unsigned char StickMan_7[] =
{ B00011100,
  B00100010,
  B00100010,
  B00100010,
  B00011100,
  B00001000,
  B00011100,
  B00101110,
  B00101011,
  B00101000,
  B00001000,
  B00010100,
  B00100010,
  B00100010,
  B01000010,
  B01000000};

  #endif //_BMP_H
