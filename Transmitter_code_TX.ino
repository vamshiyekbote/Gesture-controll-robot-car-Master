#include <SPI.h>       
#include "RF24.h"       
#include "Wire.h"       
#include "I2Cdev.h"     
#include "MPU6050.h"    


MPU6050 mpu;
int16_t ax, ay, az;
int16_t gx, gy, gz;

//Define packet for the direction (X axis and Y axis)
int data[2];

//Define object from RF24 library - 9 and 10 are a digital pin numbers to which signals CE and CSN are connected.
RF24 radio(9,10);

//Create a pipe addresses for the communicate                                    
const uint64_t pipe = 0xE8E8F0F0E1LL;

void setup(void){
  Serial.begin(9600);
  Wire.begin();
  mpu.initialize();              
  radio.begin();                    
  radio.openWritingPipe(pipe);   
}

void loop(void){
  
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  data[0] = map(ax, -17000, 17000, 300, 400 ); //Send X axis data
  data[1] = map(ay, -17000, 17000, 100, 200);  //Send Y axis data
  radio.write(data, sizeof(data));
}
