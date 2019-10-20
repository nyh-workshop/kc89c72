// Basic KC89C72 (Clone of GI AY-3-8910) test. 
// Thanks to Matio Klingemann for the AY-3-8910 sketch: https://github.com/Quasimondo/Arduino-Sketches/tree/master/AY-3-8910%20Sound%20Chip/Quarzless%20Control
//

#include "arduinoKC89C72.h"

//Pin connected to Data in (DS) of 74HC595
const int dataPin = 5;
//Pin connected to latch pin (ST_CP) of 74HC595
const int latchPin = 6;
//Pin connected to clock pin (SH_CP) of 74HC595
const int clockPin = 7;

const int pinBC1 =  13;     
const int pinBCDIR =  12;

// 2mz clock pin
const int freqOutputPin = 11;   // OC2A output pin for ATmega328 boards

const int prescale  = 1;
const int ocr2aval  = 3; 
const float period    = 2.0 * prescale * (ocr2aval+1) / (F_CPU/1.0e6);
const float freq      = 1.0e6 / period;

void init2MhzClock()
{
    // Set Timer 2 CTC mode with no prescaling.  OC2A toggles on compare match
    //
    // WGM22:0 = 010: CTC Mode, toggle OC 
    // WGM2 bits 1 and 0 are in TCCR2A,
    // WGM2 bit 2 is in TCCR2B
    // COM2A0 sets OC2A (arduino pin 11 on Uno or Duemilanove) to toggle on compare match
    //
    TCCR2A = ((1 << WGM21) | (1 << COM2A0));

    // Set Timer 2  No prescaling  (i.e. prescale division = 1)
    //
    // CS22:0 = 001: Use CPU clock with no prescaling
    // CS2 bits 2:0 are all in TCCR2B
    TCCR2B = (1 << CS20);

    // Make sure Compare-match register A interrupt for timer2 is disabled
    TIMSK2 = 0;
    // This value determines the output frequency
    OCR2A = ocr2aval;
}

ArduinoKC89C72 aKC;

void setup() {
  // put your setup code here, to run once:
  //init pins
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(pinBC1, OUTPUT);
  pinMode(pinBCDIR, OUTPUT);
  pinMode(freqOutputPin, OUTPUT);

  init2MhzClock();

  aKC.set_mix(1,1,1,0,0,0);
  aKC.note_chA(0);
  aKC.note_chB(0);
  aKC.note_chC(0);
  aKC.setNoisePeriod(0x07);
  aKC.chA_setVol(0x0f, 1);
  aKC.chB_setVol(0x0f, 1);
  aKC.chC_setVol(0x0f, 1);

  aKC.setEnvelope(0,1,1,0, 0x3300);
  aKC.note_chA(69);
  aKC.note_chB(66);
  aKC.note_chC(62);
}

void loop() {
  // put your main code here, to run repeatedly:

}
