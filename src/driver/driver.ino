#include <Wire.h>
#include <Servo.h>

int in1 = 2; 
int in2 = 3;
int in3 = 4; 
int in4 = 5; 
int enA = 10;
int enB = 11;

int blinkSpeed = 500;
int cameraServoPin= 6;
int wheelServoPin= 9;

Servo cameraServo;
Servo wheelServo;

int i = 0;
int diff = 100;

void stop();
void goForward(int speed=128);
void goBackward(int speed = 128);
void moveCameraServo(int position = 90);
void moveWheelServoe(int position = 90);

void setup(){
	pinMode(in1, OUTPUT);
	pinMode(in2, OUTPUT);
	pinMode(in3, OUTPUT);
	pinMode(in4, OUTPUT);
	pinMode(enA, OUTPUT);
	pinMode(enB, OUTPUT);
	pinMode(LED_BUILTIN, OUTPUT);
	digitalWrite(LED_BUILTIN, LOW);
	int pos = 180;
	cameraServo.attach(cameraServoPin);
	wheelServo.attach(wheelServoPin);
	
	cameraServo.write(pos);
	wheelServo.write(pos);

	Wire.begin(0x8);
	Wire.onReceive(receiveEvent);
	
	goForward();

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
	blinkSpeed = 200;
}

void goBackward(int speed = 128){
	digitalWrite(in1,LOW);
	digitalWrite(in2,HIGH);
	digitalWrite(in3,LOW);
	digitalWrite(in4,HIGH);

	analogWrite(enB,speed);
	analogWrite(enA,speed);
	blinkSpeed = 500;
}

void moveCameraServo(int position = 90){
	cameraServo.write(position);
	
}
void moveWheelServoe(int position = 90){
	wheelServo.write(position);
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

