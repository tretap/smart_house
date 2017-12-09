#include <mbed.h>

#include <FR_04.h>
#include <MQ_2.h>

#include <MQ995.h>
//#include <MFRC522.h>
#include <RFID.h>
#include <MLX90614.h>
#include "TextLCD.h"

Serial pc(USBTX,USBRX);

//MLX90614 temp(D14, D15, 300);
//MFRC522 chip(D11, D12, D13, D10, D9);
//RFID chip(D11, D12, D13, D10, D9);
//MQ995 servo(D3);


// I2C Communication
I2C i2c_lcd(D14, D15); // SDA, SCL
TextLCD_I2C lcd(&i2c_lcd, 0x27<<1, TextLCD::LCD20x4);  // I2C bus, PCF8574 Slaveaddress, LCD Type
