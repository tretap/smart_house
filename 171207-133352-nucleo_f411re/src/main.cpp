#include "main.h"

int main() {
    lcd.cls();
    lcd.printf("Hello World !\n");
    lcd.printf("INDOOR SYS...\n");
    lcd.printf("START IN 5 S");
    wait(5);
    pull_data();

    while(1){
      get_Sensor();

      if(state == 0){
        state0();
      } else if (state == 1){
        state1();
      } else if (state == 2){
        state2();
      } else if (state == 3){
        state3();
      }
    }
}

void clear_buffer(){
  while(esp.readable()){
    esp.getc();
  }
}

void get_data(char* data_server, char print_command){
  uint8_t count = 0;
  lcd.cls();
  lcd.printf("LOADING ... \n");
  lcd.printf("Connect To server\n");
  lcd.printf("Mode : %c\n",print_command);
  lcd.printf("\n");
  pc.printf("DEBUG %c:",print_command);
  while(1){
    if (esp.readable()){
      char data_c = esp.getc();

      if (data_c == '\n'){
        lcd.cls();
        pc.printf("\n",data_c);
        return ;
      } else {
        pc.printf("%c",data_c);
        data_server[count] = data_c;
        count = count + 1;
      }
    } else {
      if (print_command == 'A' or print_command == 'a' ){
        esp.printf("%c1\n",print_command);
        wait_ms(50);
      } else {
        esp.printf("%c\n",print_command);
        wait_ms(50);
      }
    }
  }
}

void get_Sensor(){
  //check_alert();


  esp.printf("B:%.1f\n",temp.read_Ta());
  wait_ms(70);
  esp.printf("b:%.1f\n",gas.get_analog());
  wait_ms(70);

}

void pull_data(){

  clear_buffer();
  esp.printf("R\n");

  char data_rain[2];
  get_data(data_rain,'R');
  rain_s = data_rain[0];
  pc.printf("%c\n",rain_s);
  //rain_s = '0';

  clear_buffer();
  esp.printf("T\n");

  char data_temp[4];
  get_data(data_temp,'T');
  sscanf(data_temp, "%f" ,&temp_outside);
  pc.printf("%f\n",temp_outside);
  //temp_outside = 0.0;

  clear_buffer();
  esp.printf("A1\n");

  char gas_data_for_alert[4];
  get_data(gas_data_for_alert,'A');
  sscanf(gas_data_for_alert, "%f", &gas_alert);
  pc.printf("%f\n",gas_alert);
  //gas_alert = 0.0;

  clear_buffer();
  esp.printf("a1\n");

  char rain_data_for_alert[4];
  get_data(rain_data_for_alert,'a');
  sscanf(rain_data_for_alert, "%d", &rain_alert);
  //rain_alert = 0;
}

void check_alert(){
  if (gas_alert <= temp.read_Ta()){

    lcd.cls();
    lcd.printf("GAS ALERT !!");
    lcd.printf("ALERT ! ! !\n");
    lcd.printf("ALERT ! ! !\n");
    lcd.printf("<Click To close>");
    wait_us(1);

    buzzer = 1;
    while(b1.read() == 0 and b2.read() == 0 and b3.read() == 0);
    buzzer = 0;
  }

  if (rain_alert == 1){
    if(rain_s == '1'){
      buzzer = 1;
      wait(1);
    }
  }
}


void state0(){
  lcd.cls();
  lcd.printf("GAS : %.2f PC.\n",gas.get_analog());
  lcd.printf("ENTER TO SETTING\n");
  lcd.printf("\n");
  lcd.printf("<|PRE   NEXT|>");
  wait_us(1);

  if(b1.read() == 1){
    while(b1.read() == 1){
      get_Sensor();
    }
    state = 2;
    pull_data();
  }
  if (b2.read() == 1){
    while(b2.read() == 1){
      get_Sensor();
    }
    state = 1;
    pull_data();
  }
  if (b3.read() == 1){
    while(b3.read() == 1){
      get_Sensor();
    }
    state = 3;
    pull_data();
  }
}

void state1(){
  lcd.cls();
  lcd.printf("IN : %.1f PC.\n",temp.read_Ta());
  lcd.printf("Out : %.1f PC.\n",temp_outside);// << Update Here
  lcd.printf("\n");
  lcd.printf("<|PRE   NEXT|>");
  wait_us(1);

  if(b1.read() == 1){
    while(b1.read() == 1){
      get_Sensor();
    }
    state = 0;
    pull_data();
  }
  if (b2.read() == 1){
    while(b2.read() == 1){
      get_Sensor();
    }
    state = 2;
    pull_data();
  }
}

void state2(){

  lcd.cls();
  lcd.printf("RAIN : %c\n",rain_s);
  lcd.printf("ALERT: %d\n",rain_alert); // Pull statue alert form firebase
  lcd.printf("\n");
  lcd.printf("<|PRE  ");
  wait_us(1);

  if(b3.read() == 1){
    while(b3.read() == 1){
      get_Sensor();
    }

    if(rain_alert == 0){
      for(int i =0; i <5;i++){
        esp.printf("a0:1\n");
        wait_ms(50);
      }
    }
    if (rain_alert == 1){
      for(int i =0; i <5;i++){
        esp.printf("a0:0\n");
        wait_ms(50);
      }
    }
  }

  if(b1.read() == 1){
    while(b1.read() == 1){
      get_Sensor();
    }
    state = 1;
    pull_data();
  }
  if (b2.read() == 1){
    while(b2.read() == 1){
      get_Sensor();
    }
    state = 2;
    pull_data();
  }

}

void state3(){
  lcd.cls();
  lcd.printf("OMG !!!!\n");
  lcd.printf("GAS SETTING MODE"); //*edit Pull Data Here !
  lcd.printf("\n");
  lcd.printf("<|-1   +1|>");
  wait_us(1);

  if(b1.read() == 1){
    while(b1.read() == 1){
      get_Sensor();
    }

    for(int i =0; i <5;i++){
      esp.printf("A0:%f\n",gas_alert-1.0);
      wait_ms(50);
    }
    gas_alert = gas_alert-1.0;
  }

  if(b2.read() == 1){
    while(b2.read() == 1){
      get_Sensor();
    }

    for(int i =0; i <5;i++){
      esp.printf("A0:%f\n",gas_alert+1.0);
      wait_ms(50);
    }
    gas_alert = gas_alert+1.0;
  }

  if(b3.read() == 1){
    while(b3.read() == 1){
      get_Sensor();
    }

    state = 0;
    pull_data();
  }

}
