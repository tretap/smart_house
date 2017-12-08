#include <mbed.h>
#include <FR_04.h>
#include <MQ_2.h>
#include <MQ995.h>
#include <MLX90614.h>

Serial pc(USBTX,USBRX);
MLX90614 temp(D14, D15, 300);
MQ995 servo(D3);
