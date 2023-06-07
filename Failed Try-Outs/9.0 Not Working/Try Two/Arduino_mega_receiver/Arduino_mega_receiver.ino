#include <SPI.h> 
#include <nRF24L01.h> 
#include <RF24.h> 

const int pinCE = 8; 
const int pinCSN = 7; 
int gotArray[2]; 

RF24 wirelessSPI(pinCE, pinCSN);  
const uint64_t pAddress = 0xB00B1E5000LL;  

void setup()   
{
 Serial.begin(9600);  
 wirelessSPI.begin();  
 wirelessSPI.setAutoAck(1);             
 wirelessSPI.enableAckPayload();        
 wirelessSPI.setRetries(5,15);        
 wirelessSPI.openReadingPipe(1,pAddress);   
 wirelessSPI.startListening();      
 wirelessSPI.printDetails();     
}

void loop()  
{   
  while(wirelessSPI.available()){ 
    wirelessSPI.read( &gotArray, sizeof(gotArray) ); 
    Serial.print("Recieved array:"); 
    for (byte i=0; i<2; i++){
      Serial.println(gotArray[i]);
    }
    Serial.println();
   }
  
 delay(100);    
}
