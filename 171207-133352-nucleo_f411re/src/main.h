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
DigitalIn b1(D3); // Pre
DigitalIn b2(D4); // Next
DigitalIn b3(D6); // Enter

DigitalOut buzzer(D9);

MLX90614 temp(D5, D7, 300);
MQ_2 gas(A4, 30, 1);

// I2C Communication
I2C i2c_lcd(D14, D15); // SDA, SCL
TextLCD_I2C lcd(&i2c_lcd, 0x3F<<1, TextLCD::LCD20x4);  // I2C bus, PCF8574 Slaveaddress, LCD Type
//---------------------//

uint8_t state = 0;

// ALERT VARIABLE //
char rain_s = 0;
float temp_outside = 0;
float gas_alert = 0;
int rain_alert = 0;

void get_data(char* data_server, char print_command);
void clear_buffer();

void get_Sensor();
void pull_data();
void check_alert();

void state0();
void state1();
void state2();
void state3();
