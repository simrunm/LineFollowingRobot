// Adafruit Motor shield library
// copyright Adafruit Industries LLC, 2009
// this code is public domain, enjoy!

#include <Adafruit_MotorShield.h>
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *motor = AFMS.getMotor(4);
int motorSpeed = 200;

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Motor test!");
  AFMS.begin();   

  // turn on motor
  motor->setSpeed(200);
 
  motor->run(RELEASE);
}

void loop() {
  Serial.print("tick");
  
  motor->run(FORWARD);
  motor->setSpeed(motorSpeed);  
  delay(100);
  
  Serial.print("tock");
  
  motor->run(BACKWARD);
  motor->setSpeed(motorSpeed);  
  delay(100);


  Serial.print("tech");
  motor->run(RELEASE);
  delay(1000);
}
