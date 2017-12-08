#include "MQ995.h"

MQ995::MQ995(PinName _pin) : MQ995_pin(_pin){
  //Pass
}

void MQ995::init(){
  MQ995_pin.period_ms(20);
  write(0.0);
}

void MQ995::write(float percent){
  if(percent < 0.0 or percent > 1.0){
    return;
  }

  int pulsewidth_us =  percent* (servo_max_us - servo_min_us)  + servo_min_us;
  MQ995_pin.pulsewidth_us(pulsewidth_us);
}
