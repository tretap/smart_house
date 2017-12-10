#include "FR_04.h"

FR_04::FR_04(PinName pin, float gain, int delay) : _pin(pin){
  _gain = gain;
  _delay = delay;
}

void FR_04::set_gain(float gain){
  _gain = gain;
}

void FR_04::set_waitUs_rData(int delay){
  _delay = delay;
}

float FR_04::get_analog(){
  float data;
  data = _pin.read() * 100;
  wait_us(_delay);

  return data;
}

bool FR_04::get_digital(){
  float data = get_analog();

  if (data <= _gain){
    return true;
  } else {
    return false;
  }
}
