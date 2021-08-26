#include <Wire.h>

int in1 = 2; 
int in2 = 3;
int in3 = 4; 
int in4 = 5; 
int enA = 10;
int enB = 11;
int blinkSpeed = 500;

void goForward(int speed=128);

void setup(){
    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT);
    pinMode(in3, OUTPUT);
    pinMode(in4, OUTPUT);
    pinMode(enB, OUTPUT);
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);
    goForward();
    Wire.begin(0x8);
    Wire.onReceive(receiveEvent);

    
}
void goForward(int speed=128){

    digitalWrite(in1,HIGH);
    digitalWrite(in2,LOW);
    digitalWrite(in3,HIGH);
    digitalWrite(in4,LOW);

    analogWrite(enB,speed);
    analogWrite(enA,speed);

}

void receiveEvent(int howmany){
  while(Wire.available()){
    char c = Wire.read();
    switch(c){
      case 0:
        blinkSpeed=1000;
        break;
      default:
        blinkSpeed=500;
        break;
    }
  }
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(blinkSpeed);
  digitalWrite(LED_BUILTIN, LOW);
  delay(blinkSpeed);

}