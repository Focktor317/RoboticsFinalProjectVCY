#include <VirtualWire.h>

// Left & Right motor pins
const int IN1 = 2;    
const int IN2 = 3;    
const int IN3 = 4;     
const int IN4 = 5;    

const int receive_pin = 11;

// save values
int my_array[2];


void setup()
{
  Serial.begin(9600); 
  
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  vw_set_rx_pin(receive_pin);
  vw_setup(2000);

  vw_rx_start();
}

void loop()
{
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;

  int i;
  
  if (vw_get_message(buf, &buflen)) {
    for (i = 0; i < buflen; i++) {
      Serial.print(buf[i], HEX);
    }
    memcpy(my_array, buf, buflen);
  }

  // else{
    // Serial.println("connection is fucked");
  // }
  
  if (my_array[1] < 80) { //Reverse
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);

    }

    if (my_array[1] > 145) {//forward
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
    }

    if (my_array[0] > 155) {//right turn
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
    }

    if (my_array[0] < 80) {//left turn
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
    }

    if (my_array[0] > 100 && my_array[0] < 170 && my_array[1] > 80 && my_array[1] < 130) { //stop car
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, LOW);
    }
    
  // Serial.print("X: ");
  // Serial.print(my_array[0]);
  // Serial.print("    ");
  // Serial.print("Y: ");
  // Serial.print(my_array[1]);
  // Serial.print("\n");
}
 
