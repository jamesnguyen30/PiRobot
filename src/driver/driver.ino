#include <Wire.h>

int in1 = 2; 
int in2 = 3;
int in3 = 4; 
int in4 = 5; 
int enA = 10;
int enB = 11;

int i = 0;
int diff = 100;

int blinkSpeed = 1000;

void stop();
void goForward(int speed=128);
void goBackward(int speed = 128);

void setup(){
    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT);
    pinMode(in3, OUTPUT);
    pinMode(in4, OUTPUT);
    pinMode(enB, OUTPUT);
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);
    stop();
    // goForward();

    Wire.begin(0x8);
    Wire.onReceive(receiveEvent);
    
}
void stop(){
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
	blinkSpeed = 1000;
}

void goForward(int speed=128){

    digitalWrite(in1,HIGH);
    digitalWrite(in2,LOW);
    digitalWrite(in3,HIGH);
    digitalWrite(in4,LOW);

    analogWrite(enB,speed);
    analogWrite(enA,speed);
	blinkSpeed = 500;

}

void goBackward(int speed = 128){
    digitalWrite(in1,LOW);
    digitalWrite(in2,HIGH);
    digitalWrite(in3,LOW);
    digitalWrite(in4,HIGH);

    analogWrite(enB,speed);
    analogWrite(enA,speed);
}

void receiveEvent(int howmany){
  while(Wire.available()){
    char c = Wire.read();
    switch(c){
      case 0:
        stop();
        break;
      case 1:
        goForward();
        break;
      case 2:
        goBackward();
        break;
      default:
        stop();
        break;
    }
  }
}


void loop(){
	digitalWrite(LED_BUILTIN, HIGH);
	delay(blinkSpeed);
	digitalWrite(LED_BUILTIN, LOW);
	delay(blinkSpeed);
	
}

