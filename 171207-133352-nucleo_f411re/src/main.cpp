#include "main.h"

int main() {
  // put your setup code here, to run once:
  pc.printf("Hello Welcome To Test! Programs\n");
  servo.init();

  while(1) {
    // put your main code here, to run repeatedly:

    wait(1.0);
    servo.write(0.5);


    wait(1.0);
    servo.write(1.0);


    wait(1.0);
    servo.write(0.0);


  }
}
