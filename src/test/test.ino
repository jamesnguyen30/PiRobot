#include <Wire.h>
#include <Servo.h>

int in1 = 2; 
int in2 = 4;
int in3 = 7; 
int in4 = 8; 
int enA = 6;
int enB = 11;
int blinkSpeed = 500;
int cameraServoPin= 3;
int wheelServoPin= 5;

int pos = 0;

void goForward(int speed=128);
void stop();
void turn(int position=90);

Servo cameraServo;
Servo wheelServo;


void setup(){
	pinMode(in1, OUTPUT);
	pinMode(in2, OUTPUT);
	pinMode(in3, OUTPUT);
	pinMode(in4, OUTPUT);
	pinMode(LED_BUILTIN, OUTPUT);
	digitalWrite(LED_BUILTIN, LOW);
	Wire.begin(0x8);
	Wire.onReceive(receiveEvent);

	int pos = 90;
	cameraServo.attach(cameraServoPin);
	wheelServo.attach(wheelServoPin);

	goForward();


}
void goForward(int speed=128){

	digitalWrite(in1,HIGH);
	digitalWrite(in2,LOW);
	digitalWrite(in3,HIGH);
	digitalWrite(in4,LOW);

	analogWrite(enB,speed);
	analogWrite(enA,speed);
	analogWrite(9,speed);
	analogWrite(6,speed);
	blinkSpeed = 500;

}

void stop(){
	digitalWrite(in1,LOW);
	digitalWrite(in2,LOW);
	digitalWrite(in3,LOW);
	digitalWrite(in4,LOW);
	analogWrite(enB,0);
	analogWrite(enA,0);
}

void turn(int pos = 90){
	wheelServo.write(pos);
}

void shake(int pos = 90){
	cameraServo.write(pos);
}

void receiveEvent(int howmany){
	while(Wire.available()){
		char c = Wire.read();
		switch(c){
			case 0:
				blinkSpeed=1000;
				stop();
				break;
			case 1: 
				goForward();
				break;
			case 2: 
				turn(pos);
				shake(pos);
				if(pos == 0){
					pos = 180;
				} else {
					pos = 0;
				}

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



	// for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
	//   cameraServo.write(pos);              // tell servo to go to position in variable 'pos'
	//   delay(15);                       // waits 15ms for the servo to reach the position
	// }
	// for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
	//   cameraServo.write(pos);              // tell servo to go to position in variable 'pos'
	//   delay(15);                       // waits 15ms for the servo to reach the position
	// }

}
