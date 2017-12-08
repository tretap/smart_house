#ifndef FR_04_H
//---------------------------------------//

/*
  Create By Trethep Promwiset {7 December 2017}
*/

#define FR_04_H
#include <mbed.h>

class FR_04{
public:
  FR_04(PinName pin, float gain, int delay);

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
