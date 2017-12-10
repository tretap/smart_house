#include <mbed.h>

#include <FR_04.h>
#include <MQ_2.h>

#include <MQ995.h>
//#include <MFRC522.h>
#include <RFID.h>
#include <MLX90614.h>
#include "TextLCD.h"

Serial pc(USBTX,USBRX);
Serial esp(D8, D2);
DigitalIn b1(D3);
DigitalIn b2(D4);

FR_04 rain(A1, 98, 1);
MLX90614 temp(D5, D7, 300);
RFID chip(D11, D12, D13, D10, D9);
MQ995 servo(D6);


// I2C Communication
I2C i2c_lcd(D14, D15); // SDA, SCL
TextLCD_I2C lcd(&i2c_lcd, 0x27<<1, TextLCD::LCD20x4);  // I2C bus, PCF8574 Slaveaddress, LCD Type
//---------------------//

uint8_t data[4];
uint8_t state = 0;
uint8_t _state1 = 0;

void get_Sensor();
bool check_id_rfid(uint8_t* id);

void state0();
void state1();
