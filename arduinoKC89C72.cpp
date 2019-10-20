#include "arduinoKC89C72.h"

//Pin connected to Data in (DS) of 74HC595
extern const int dataPin;
//Pin connected to latch pin (ST_CP) of 74HC595
extern const int latchPin;
//Pin connected to clock pin (SH_CP) of 74HC595
extern const int clockPin;

extern const int pinBC1;     
extern const int pinBCDIR;

void ArduinoKC89C72::mode_latch(){
    digitalWrite(pinBC1, HIGH);
    digitalWrite(pinBCDIR, HIGH);
}

void ArduinoKC89C72::mode_write(){
    digitalWrite(pinBC1, LOW);
    digitalWrite(pinBCDIR, HIGH);
}

void ArduinoKC89C72::mode_inactive(){
    digitalWrite(pinBC1, LOW);
    digitalWrite(pinBCDIR, LOW);    
}

void ArduinoKC89C72::write_data(unsigned char addr, unsigned char inputData)
{

  mode_inactive();
  //write address

  digitalWrite(latchPin, LOW);
  // shift out the bits:
  shiftOut(dataPin, clockPin, MSBFIRST, addr);

  //take the latch pin high so the LEDs will light up:
  digitalWrite(latchPin, HIGH);

  mode_latch();
  mode_inactive();

  //write data
  mode_write();

  digitalWrite(latchPin, LOW);
  // shift out the bits:
  shiftOut(dataPin, clockPin, MSBFIRST, inputData);

  //take the latch pin high so the LEDs will light up:
  digitalWrite(latchPin, HIGH);

  mode_inactive();
};