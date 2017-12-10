#include "MQ_2.h"

MQ_2::MQ_2(PinName pin, float gain, int delay) : _pin(pin){
  _gain = gain;
  _delay = delay;
}

void MQ_2::set_gain(float gain){
  _gain = gain;
}

void MQ_2::set_waitUs_rData(int delay){
  _delay = delay;
}

float MQ_2::get_analog(){
  float data;
  data = _pin.read() * 100;
  wait_us(_delay);

  return data;
}

bool MQ_2::get_digital(){
  float data = get_analog();

  if (data >= _gain){
    return true;
  } else {
    return false;
  }
}
