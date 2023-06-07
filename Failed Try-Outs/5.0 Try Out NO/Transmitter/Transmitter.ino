#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include "Wire.h"       
#include "I2Cdev.h"     
#include "MPU6050.h"    

#include <RH_ASK.h>
#include <SPI.h>

//Define variables for Gyroscope and Accelerometer data

MPU6050 mpu;
int16_t ax, ay, az;
int16_t gx, gy, gz;

const uint64_t pipeOut = 0xE8E8F0F0E1LL; 

RF24 radio(7, 8); //  CN and CSN  pins of nrf

struct MyData {
  byte X;
  byte Y;
};

int my_array[2];

MyData data;

RH_ASK driver;

void setup()
{
  Serial.begin(9600);
  Wire.begin();
  mpu.initialize();
  if (!driver.init())
         Serial.println("init failed");
}

void loop()
{
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  data.X = map(ax, -17000, 17000, 0, 255 ); //Send X axis data
  data.Y = map(ay, -17000, 17000, 0, 255);  //Send Y axis data

  my_array[0] = data.X;
  my_array[1] = data.Y;

  // radio.write(&data, sizeof(MyData));
  driver.send((uint8_t *)my_array, sizeof(my_array));
  driver.waitPacketSent();
  delay(1000);

  Serial.print("Axis X = ");
  Serial.print(data.X);
  Serial.print("  ");
  Serial.print("Axis Y = ");
  Serial.println(data.Y);
}
