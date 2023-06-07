#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include "SPI.h" 
#include "RF24.h" 
#include "nRF24L01.h" 
#define CE_PIN 7 
#define CSN_PIN 8 
#define INTERVAL_MS_TRANSMISSION 250 

RF24 radio(CE_PIN, CSN_PIN); 
const byte address[6] = "00001"; 
//NRF24L01 buffer limit is 32 bytes (max struct size) 
struct payload { 
   float data1; 
   float data2; 
}; 
payload payload; 

Adafruit_MPU6050 mpu;

void setup(void) {
  Serial.begin(115200);

  // Try to initialize!
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");

  // set accelerometer range to +-8G
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);

  // set gyro range to +- 500 deg/s
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);

  // set filter bandwidth to 21 Hz
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  radio.begin(); 
   //Append ACK packet from the receiving radio back to the transmitting radio 
   radio.setAutoAck(false); //(true|false) 
   //Set the transmission datarate 
   radio.setDataRate(RF24_250KBPS); //(RF24_250KBPS|RF24_1MBPS|RF24_2MBPS) 
   //Greater level = more consumption = longer distance 
   radio.setPALevel(RF24_PA_MAX); //(RF24_PA_MIN|RF24_PA_LOW|RF24_PA_HIGH|RF24_PA_MAX) 
   //Default value is the maximum 32 bytes 
   radio.setPayloadSize(sizeof(payload)); 
   //Act as transmitter 
   radio.openWritingPipe(address); 
   radio.stopListening(); 
}

void loop() {
  /* Get new sensor events with the readings */
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  Serial.print("Rotation X: ");
  Serial.print(g.gyro.x);
  Serial.print(", Y: ");
  Serial.print(g.gyro.y);
  Serial.print(", Z: ");
  Serial.print(g.gyro.z);
  Serial.println(" rad/s");

  Serial.println("");
  payload.data1 = g.gyro.x; 
   payload.data2 = g.gyro.y; 
   radio.write(&payload, sizeof(payload)); 
   Serial.print("Data1:"); 
   Serial.println(payload.data1); 
   Serial.print("Data2:"); 
   Serial.println(payload.data2); 
   Serial.println("Sent"); 
   delay(INTERVAL_MS_TRANSMISSION);
}

// -6 most
