#include "main.h"

int main() {
    lcd.cls();
    chip.rfid_init();
    esp.baud(9600);
    servo.init();
    servo.write(0.1);

    lcd.printf("Hello World !");

    while(1){
      get_Sensor();
      if(state == 0){
        state0();
        wait(0.2);
      } else if (state == 1){
        state1();
        wait(0.2);

      }
    }
}

void get_Sensor(){
  //----- Update to server Here !----//

  esp.printf("%c:%d",'r',rain.get_digital());
  esp.printf("%c:%.1f",'t',temp.read_Ta());
  //----------------------------------------------//

}

bool check_id_rfid(uint8_t* id){
  bool check = false;

  //--------- Connect to Fire Base ---------//
  uint8_t master_id[4];

  uint8_t db_id[255]; // << Insert id form db here
  uint8_t len_id = 0; // << Size of id in firebase

  // Simulator Delete Here when True //
  master_id[0] = 0x8B;
  master_id[1] = 0x18;
  master_id[2] = 0x53;
  master_id[3] = 0x7F;

  // Check form master card //
  for(int8_t i = 0; i < 4;i++){
    if (id[i] != master_id[i]){
      break;
    }

    if(i == 3){
      check = true;
    }
  }

  if(check){
    return true;
  }

  // ----------------------------//

  // Check form db (fire base ) here//

  for(int8_t n_id = 0; n_id < len_id; n_id++){
    for(int8_t i = 0; i < 4;i++){
      if (id[i] != db_id[i]){
        break;
      }

      if(i == 3){
        check = true;
      }
    }
  }
  return check;
}

void state0(){
  lcd.cls();
  lcd.printf("Hello World !\n");
  lcd.printf("\n");
  lcd.printf("\n");
  lcd.printf("<<Click to set");

  get_Sensor();

  //---------------------------------//

  if(b1.read() == 1){
    while(b1.read()==1);
    state = 1;
    _state1 = 0;
  }

  if (chip.get_uid(data)){

    lcd.cls();
    if(check_id_rfid(data)){
      lcd.printf("Welcome to house ^w^ \n");
      lcd.printf("Rain : %d\n",rain.get_digital());
      lcd.printf("Temp : %.2f\n",temp.read_Ta());
      lcd.printf("\n");
      // ---------------- On Servo Here ------------//

      get_Sensor();
      wait(2);
      servo.write(0.3);
    } else {
      lcd.printf("Sorry! sir T^T\n");
      lcd.printf("You don't have permission!\n");

      get_Sensor();
      wait(1.5);
      servo.write(0.2);
    }
  }
}

void state1(){

  if(_state1 == 0){
    lcd.cls();
    lcd.printf("RFID SETTING MODE :>");
    lcd.printf("CLICK TO SETTING \n");
    lcd.printf("\n");
    lcd.printf("<<NEW   DELETE OLD>>");

    get_Sensor();
    wait(0.2);

    if(b1.read() == 1 ){
      while(b1.read()==1);
      _state1 = 1;
    }

    if(b2.read() == 1){
      while(b2.read() == 1);
      _state1 = 2;
    }
  }

  if(_state1 == 1){
    lcd.cls();
    lcd.printf("Plase scan  :>\n");
    lcd.printf("Member card here \n");

    get_Sensor();
    wait(0.2);

    if (chip.get_uid(data)){

      lcd.cls();

      if(check_id_rfid(data)){
        lcd.printf("Plase scan >>\n");
        lcd.printf("New Card here !: \n");
        lcd.printf("\n");
        lcd.printf("\n");

        get_Sensor();
        for(uint8_t a = 0; a<3;a++){
          wait(1);
          get_Sensor();
        }

        while(chip.get_uid(data) == false){
          get_Sensor();
        }

        // Insert New ID Card to fire base here !
        lcd.cls();
        lcd.printf("New Card >>\n");
        lcd.printf("Suscess !: \n");
        lcd.printf("\n");
        lcd.printf("\n");

        state = 0;
        _state1 = 0;

        get_Sensor();
        wait(2);
      } else {
        lcd.printf("Sorry! sir T^T\n");
        lcd.printf("You don't have \nPermission!\n");

        state = 0;
        _state1 = 0;

        get_Sensor();
        wait(1.5);
      }
    }

  } else if (_state1 == 2){
    lcd.cls();
    lcd.printf("Plase scan  :>\n");
    lcd.printf("Member card here \n");

    get_Sensor();
    wait(0.2);

    if (chip.get_uid(data)){

      lcd.cls();
      // ----- > Load ID form firebase to id

      if(check_id_rfid(data)){
        lcd.printf("Plase scan >>\n");
        lcd.printf("Old Card here !: \n");
        lcd.printf("\n");
        lcd.printf("\n");

        get_Sensor();
        for(uint8_t a = 0; a<3;a++){
          wait(1);
          get_Sensor();
        }

        while(chip.get_uid(data) == false){
          get_Sensor();
        }

        // Delete ID Card in fire base here !
        lcd.cls();
        lcd.printf("Delete Card >>\n");
        lcd.printf("Suscess !: \n");
        lcd.printf("\n");
        lcd.printf("\n");

        state = 0;
        _state1 = 0;

        get_Sensor();
        wait(2);
      } else {
        lcd.printf("Sorry! sir T^T\n");
        lcd.printf("You don't have \nPermission!\n");

        state = 0;
        _state1 = 0;

        get_Sensor();
        wait(1.5);
      }
    }
  }

  get_Sensor();


}
