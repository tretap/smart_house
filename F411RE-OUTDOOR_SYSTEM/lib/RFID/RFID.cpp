#include "RFID.h"

RFID::RFID(PinName _mosi, PinName _miso, PinName _clk, PinName _cs, PinName _rst) : rfid_chip(_mosi,_miso,_clk,_cs,_rst){
}

void RFID::rfid_init(){
  rfid_chip.PCD_Init();
}

bool RFID::get_uid(uint8_t* data){
  if (rfid_chip.PICC_IsNewCardPresent())
   {
     if (rfid_chip.PICC_ReadCardSerial())
     {
       for (uint8_t i = 0; i < 4; i++)
       {
         data[i] = rfid_chip.uid.uidByte[i];
       }

       return true;
     }
   }
   return false;
}
