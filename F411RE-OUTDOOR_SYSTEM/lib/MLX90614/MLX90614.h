#ifndef MLX90614_H
//---------------------------------------//

/*
  Create By Trethep Promwiset {7 December 2017}
*/

#define MLX90614_H
// RAM
#define MLX90614_TA      0x06  // Ambient Temperature
#define MLX90614_TOBJ1   0x07  // Object Temperature 1
// EEPROM
#define MLX90614_ADDR    0x5A << 1  // I2C Address


#include <mbed.h>

class MLX90614{
public:
  MLX90614(PinName _sda, PinName _scl, int delay);

  float read_Ta();
  float read_Tobj();

private:
  I2C mlx90614_i2c;
  int _delay;

  uint16_t read_3byte(char cmd);
  float read_temperature(char cmd);
};

//---------------------------------------//
#endif
