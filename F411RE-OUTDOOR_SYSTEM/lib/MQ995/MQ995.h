#ifndef MQ995_H
//---------------------------------------//
/*
  Create By Trethep Promwiset {7 December 2017}
*/
#include <mbed.h>

#define servo_max_us 1900
#define servo_min_us 600

class MQ995{
public:
  MQ995(PinName _pin);

  void init();
  void write(float percent);

private:
  PwmOut MQ995_pin;
};

//---------------------------------------//
#endif
