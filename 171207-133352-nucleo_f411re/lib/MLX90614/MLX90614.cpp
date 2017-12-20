#include "MLX90614.h"

MLX90614::MLX90614(PinName _sda, PinName _scl, int delay) : mlx90614_i2c(_sda, _scl){
  _delay = delay;
}

float MLX90614::read_Ta(){
  return read_temperature(MLX90614_TA);
}

float MLX90614::read_Tobj(){
  return read_temperature(MLX90614_TOBJ1);
}

uint16_t MLX90614::read_3byte(char cmd)
{
  uint16_t result;
  char data[2];

  mlx90614_i2c.write(MLX90614_ADDR, &cmd, 1, 1);
  mlx90614_i2c.read(MLX90614_ADDR, data, 2, 0);

  wait_us(_delay);


  result = data[0] + (data[1]<<8);
  return result;
}

float MLX90614::read_temperature(char cmd){
  int data = read_3byte(cmd);

  return (((float)data * 2.0) -27315)/100.0;
}
