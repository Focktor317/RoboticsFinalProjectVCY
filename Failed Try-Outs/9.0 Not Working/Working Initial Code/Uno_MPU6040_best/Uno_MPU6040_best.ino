#include <Wire.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>


// Gyroscope

const int MPU=0x68; 
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;

void  setup(){
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);  
  Wire.write(0);    
  Wire.endTransmission(true);
  Serial.begin(115200);

}
void  loop(){
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);  
  Wire.endTransmission(false);
  Wire.requestFrom(MPU,12,true);  
   
  GyX=Wire.read()<<8|Wire.read();  
  GyY=Wire.read()<<8|Wire.read();  
  GyZ=Wire.read()<<8|Wire.read();  
  
  Serial.print("Gyroscope: ");
  Serial.print("X  = "); Serial.print(GyX);
  Serial.print(" | Y = "); Serial.print(GyY);
  Serial.print(" | Z = "); Serial.println(GyZ);
  Serial.println(" ");
  delay(333);
}

// MPU6050 Gyroscope code --> https://projecthub.arduino.cc/Nicholas_N/647e6522-3f09-42d7-b7e5-503e5e5abecf
// NRF24L01 Connection --> https://www.electronicwings.com/arduino/nrf24l01-interfacing-with-arduino-uno
