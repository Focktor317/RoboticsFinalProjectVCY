#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

Adafruit_MPU6050 mpu;

RF24 radio(7, 8); // CE, CSN
const byte addresses[][6] = {"00001", "00002"};

const int num = 2;
int Array[num]; 

int GyX, GyY;

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


  // set gyro range to +- 2000 deg/s
  mpu.setGyroRange(MPU6050_RANGE_2000_DEG);

  // set filter bandwidth to 21 Hz
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  radio.begin();
  radio.openWritingPipe(addresses[1]); // 00002
  radio.openReadingPipe(1, addresses[0]); // 00001
  radio.setPALevel(RF24_PA_MIN);

  delay(100);
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

  GyX = g.gyro.x;
  GyY = g.gyro.y;

  Array[0] = GyX;
  Array[1] = GyY;
  radio.stopListening();
  radio.write(&Array, sizeof(Array));
  
  delay(500);
}
