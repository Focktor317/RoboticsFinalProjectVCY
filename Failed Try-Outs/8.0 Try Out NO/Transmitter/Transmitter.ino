#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <VirtualWire.h>
#include "Wire.h"       
#include "I2Cdev.h"     
#include "MPU6050.h"    

//Define variables for Gyroscope and Accelerometer data

MPU6050 mpu;
const int MPU=0x68; 
int16_t ax, ay, az;
int16_t gx, gy, gz;

int my_array[2];
int X,Y;

const int transmit_pin = 12;

void setup()
{
  Serial.begin(9600);
  Wire.begin();
  mpu.initialize();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);  
  Wire.write(0);    
  Wire.endTransmission(true);
    
  vw_set_tx_pin(transmit_pin);
  vw_setup(2000);   // Bits per sec
  
}

void loop()
{
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  X = map(ax, -17000, 17000, 0, 255 ); //Send X axis data
  Y = map(ay, -17000, 17000, 0, 255);  //Send Y axis data

  // send bytes. Here 6 bytes, that is 6 uint8 or 3 uint16
  vw_send((uint8_t *)my_array, sizeof(my_array));
  // wait for send to end
  vw_wait_tx();
  // Don't send too much the joystick values
  delay(200);

  Serial.print("Axis X = ");
  Serial.print(X);
  Serial.print("  ");
  Serial.print("Axis Y = ");
  Serial.println(Y);
}
