#include <Wire.h>

int in1 = 2; 
int in2 = 3;
int in3 = 4; 
int in4 = 5; 
int enA = 10;
int enB = 11;
int relay = 7;

int i = 0;
int diff = 100;

void stop();
void goForward(int speed=255);
void goBackward(int speed = 255);

void setup(){
    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT);
    pinMode(in3, OUTPUT);
    pinMode(in4, OUTPUT);
    pinMode(enB, OUTPUT);
    pinMode(relay, OUTPUT);
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);
    stop();
    // goForward();

    Wire.begin(0x8);
    Wire.onReceive(receiveEvent);

    digitalWrite(relay,HIGH);
    
}
void stop(){
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);

}

void goForward(int speed=255){

    digitalWrite(in1,HIGH);
    digitalWrite(in2,LOW);
    digitalWrite(in3,HIGH);
    digitalWrite(in4,LOW);

    analogWrite(enB,speed);
    analogWrite(enA,speed);

}

void goBackward(int speed = 255){
    digitalWrite(in1,LOW);
    digitalWrite(in2,HIGH);
    digitalWrite(in3,LOW);
    digitalWrite(in4,HIGH);

    analogWrite(enB,speed);
    analogWrite(enA,speed);
}

void turnLeft(int speed = 255){
    digitalWrite(in1,HIGH);
    digitalWrite(in2,LOW);
    digitalWrite(in3,LOW);
    digitalWrite(in4,HIGH);

    analogWrite(enB,speed);
    analogWrite(enA,speed);
}

void turnRight(int speed = 255){
    digitalWrite(in1,LOW);
    digitalWrite(in2,HIGH);
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
        stop();
        // digitalWrite(LED_BUILTIN, LOW);
        break;
      case 1:
        goForward();
        break;
      case 2:
        goBackward();
        break;
      case 3:
        turnRight();
        break;
      case 4:
        turnLeft();
        break;
      default:
        stop();
        break;
    }
  }
}


void loop(){
//  stop();
//  goForward(255);
}
