#ifndef RFID_H
//---------------------------------------//
/*
  Create By Trethep Promwiset {9 December 2017}
  but use other library T^T.
*/

#define RFID_H

#include <MFRC522.h>
#include <mbed.h>

class RFID{
public:
  RFID(PinName _mosi, PinName _miso, PinName _clk, PinName _cs, PinName _rst);

  void rfid_init();
  bool get_uid(uint8_t* data);

private:
  MFRC522 rfid_chip;
};

//---------------------------------------//
#endif
