#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN
// const byte addresses[][6] = {"00001", "00002"};
const byte address[6] = "00001";

int gotArray[2];

void setup() {
  Serial.begin(9600);
  radio.begin();
  // radio.openWritingPipe(addresses[0]); // 00001
  // radio.openReadingPipe(1, addresses[1]); // 00002
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}

void loop() {
  // delay(5);
  // radio.startListening();
  
  if ( radio.available()) {
    while (radio.available()) {
      radio.read(&gotArray, sizeof(gotArray));
      Serial.print("Received array: ");

      for (byte i=0; i<2; i++){
        Serial.println(gotArray[i]);
      }
      Serial.println();
    }
  }
}
