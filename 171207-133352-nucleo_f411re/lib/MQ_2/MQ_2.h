#ifndef MQ_2_H
//---------------------------------------//
/*
  Create By Trethep Promwiset {7 December 2017}
*/

#define MQ_2_H
#include <mbed.h>

class MQ_2{
public:
  MQ_2(PinName pin, float gain, int delay);

  void set_gain(float gain);
  void set_waitUs_rData(int delay);

  float get_analog();
  bool get_digital();

private:
  AnalogIn _pin;

  float _gain;
  int _delay;
};

//---------------------------------------//
#endif
