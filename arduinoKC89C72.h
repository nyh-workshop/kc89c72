#ifndef ARDUINOKC89C72_H
#define ARDUINOKC89C72_H

#include "kc89c72.h"

class ArduinoKC89C72 : public KC89C72
{
public:
  void write_data(unsigned char addr, unsigned char inputData);
private:
  void mode_latch();
  void mode_write();
  void mode_inactive();  
};

#endif
