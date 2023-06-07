#include <VirtualWire.h>
#include<Wire.h>

const int MPU=0x68; 
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;
const int transmit_pin = 12;

int my_array[2];
int X, Y;

bool test = false;

// Waarden opslaan
unsigned int Hval, Vval, Kval;
uint8_t valArray[2];
unsigned int gebruiker = 2000 * 0;

void setup() {
  // Begin Seriele monitor
  if (test) Serial.begin(9600);
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);  
  Wire.write(0);    
  Wire.endTransmission(true);
    
  vw_set_tx_pin(transmit_pin);
  vw_setup(2000);   // Bits per sec
}

void loop(){

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

  X = map(GyX, -17000, 17000, 0, 255 ); //Send X axis data
  Y = map(GyY, -17000, 17000, 0, 255);  //Send Y axis data

  my_array[0] = X;
  my_array[1] = Y;

  int buflen = sizeof(my_array);
  
  // send bytes. Here 6 bytes, that is 6 uint8 or 3 uint16
  vw_send((uint8_t *)my_array, buflen);
  // wait for send to end
  vw_wait_tx();
  // Don't send too much the joystick values
  delay(200);
  
  if (test) {
    toonWaarden();
    delay(50);
  }
  
}

void toonWaarden() {
  Serial.print ("  "); 
  Serial.print (X);
  Serial.print ("  --  "); 
  Serial.print (Y);
}
