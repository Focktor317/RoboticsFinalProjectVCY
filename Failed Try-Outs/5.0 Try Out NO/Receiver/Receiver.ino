#include <VirtualWire.h>


const int IN1 = 2;    
const int IN2 = 3;    
const int IN3 = 4;     
const int IN4 = 5; 

int my_array[2];

int dataX;
int dataY;

void setup()
{

  Serial.begin(9600);
  Serial.println("setup");

  vw_setup(2000);  // Bits per sec
  vw_rx_start();       // Start the receiver PLL running

  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
}

void loop()
{
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;


    memcpy(my_array, buf, buflen);

    // int i;
    // for (i = 0; i < buflen; i++)

    dataX       =  my_array[0];
    dataY       =  my_array[1];

    Serial.print("X: ");
    Serial.print(dataX);
    Serial.print("    ");
    Serial.print("Y: ");
    Serial.print(dataY);
    Serial.print("\n");

  if (dataY < 80) { //Reverse
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);

    }

  if (dataY > 145) {//forward
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
    }

  if (dataX > 155) {//right turn
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
    }

    if (dataX < 80) {//left turn
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
    }

    if (dataX > 100 && dataX < 170 && dataY > 80 && dataY < 130) { //stop car
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, LOW);
    }
    
  delay (1000);
  Serial.println("");
  digitalWrite(13, false);

}
