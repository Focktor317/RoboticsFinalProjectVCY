#include <Wire.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

const int pinCE = 7; 
const int pinCSN = 8; 
const uint64_t address = 0xB00B1E5000LL;

const int num = 2;
int Array[num]; 

const int MPU=0x68; 
int16_t GyX,GyY,GyZ;

void  setup();
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);  
  Wire.write(0);    
  Wire.endTransmission(true);
  Serial.begin(115200);
    
  wirelessSPI.begin();  
  wirelessSPI.setAutoAck(1);             
  wirelessSPI.enableAckPayload();        
  wirelessSPI.setRetries(5,15);        
  wirelessSPI.openWritingPipe(1,address);   
  wirelessSPI.stopListening();      
  wirelessSPI.printDetails();  
  
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

  Array[0] = GyX;
  Array[1] = GyY;

  Serial.println("Now sending data... "); 
   
   if (!wirelessSPI.write( &Array, sizeof(Array))){ 
      Serial.println("delivery failed"); 
      Serial.println();     
  }
  else { 
      Serial.println("Send successful.");
      Serial.println();
  }
   delay(1000);
}

// MPU6050 Gyroscope code --> https://projecthub.arduino.cc/Nicholas_N/647e6522-3f09-42d7-b7e5-503e5e5abecf
// NRF24L01 Connection --> https://www.electronicwings.com/arduino/nrf24l01-interfacing-with-arduino-uno
