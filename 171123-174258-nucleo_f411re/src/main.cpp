
#include "mbed.h"

I2C i2c(D14,D15);   //sda,scl
Serial pc(USBTX,USBRX);  //serial usb config

char a[5];

int main()
{
  int p1,p2,p3;          //to store adc high and low and PEC(packet error correction)
  int ch=0,temp_val;     //to store temparature value
  i2c.frequency(20000);  //I2C frequency 20000hz (20khz)


  while(1){

  do{                               //loop repeat if repeated start codition is not acknowledge

                      do{            //loop repeat if device ram address(reg address where the Tobj value present) condition is not acknowledge



                                  do{                       //loop repeat if device address acdition is not acknowledge
                                       pc.printf("add\t");
                                         i2c.stop();          //stop i2c if not ack

                                    wait(0.2);
                                  i2c.start();                  //start I2C
                                        ch=i2c.write(0x5A << 1);     //device address of mlxIRtemprature sensorwith write condition
                                      } while(ch==0);          //wait for ack
                                  pc.printf("ACK1\t");

                                  ch=i2c.write(0x07);          //device ram address where Tobj value is present
                       } while(ch==0);                          //wait for ack
                      pc.printf("ACK2\t");



                         i2c.start();                         //repeat start
                         ch=i2c.write(0x01);                  //device address with read condition
        }while(ch==0);                                          //wait for ack
         pc.printf("ACK3\t");
         p1=i2c.read(1);                            //Tobj low byte
        p2=i2c.read(1);                               //Tobj heigh byte
        p3=i2c.read(0);                                //PEC
        i2c.stop();                                 //stop condition

                                                            //degree centigrate conversion
     temp_val=((((p2&0x007f)<<8)+p1)*0.02)-0.01;
     temp_val=temp_val-273;



   wait(1.0);


   pc.printf("rx val1 is %d\n",p1);
  pc.printf("rx val2 is %d\n",p2);
   pc.printf("rx val3 is %d\n",p3);
  pc.printf("temp val is %d\n",temp_val);


  wait(2.0);



  }



  return 0;
}
