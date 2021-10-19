#include <Adafruit_MotorShield.h>
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *leftMotor = AFMS.getMotor(2);
Adafruit_DCMotor *rightMotor = AFMS.getMotor(4);

// setup function to initialize hardware and software
int leftSensor = A0;
int rightSensor = A1;// analog pin used to connect the sharp sensor
int sensorLeft = 0;// variable to store the values from s
int sensorRight = 0;
int leftMotorSpeed = 0;
int rightMotorSpeed = 0;
int thresholdTape = 150;
int fastSpeed = 25;
int slowSpeed = 10;
int right_deg = 0;
int left_deg = 0;
int count = 0;
int isReady = 0;
//int userInput;
char receivedChar;
boolean newData = false;

void setup(){
  // start the serial port
  int long baudRate = 9600; // NOTE1: The baudRate for sending & receiving programs must match
  Serial.begin(baudRate);  // NOTE2: Set the baudRate to 115200 for faster communication
  Serial.begin(9600);           // set up Serial library at 9600 bps
  AFMS.begin(); 
}

void recvOneChar() {
    if (Serial.available() > 0) {
        receivedChar = Serial.read();
        newData = true;
    }
}

void showNewData() {
    if (newData == true) {
        Serial.println(receivedChar);
        newData = false;
    }
}

void steepLeft(){
 rightMotor->run(FORWARD);
 rightMotor->setSpeed(fastSpeed);   
}

void slowLeft(){
  rightMotor->run(FORWARD);
  leftMotor-> run(BACKWARD);
  rightMotor->setSpeed(fastSpeed); 
  leftMotor->setSpeed(slowSpeed);  
}

void steepRight(){
 leftMotor->run(BACKWARD);
 leftMotor->setSpeed(fastSpeed);   
}

void slowRight(){
  leftMotor->run(BACKWARD);
  rightMotor-> run(FORWARD);
  leftMotor->setSpeed(fastSpeed); 
  rightMotor->setSpeed(slowSpeed);  
}

void goStraight(){
  leftMotor->run(BACKWARD);
  rightMotor-> run(FORWARD);
  leftMotor->setSpeed(fastSpeed); 
  rightMotor->setSpeed(fastSpeed); 
}

void stopMotors(){
  leftMotor->run(RELEASE);
  rightMotor->run(RELEASE); 
}

void rightTurn(int right_deg){
  rightMotor-> run(FORWARD);
  rightMotor->setSpeed(right_deg); 
}

void leftTurn(int left_deg){
  leftMotor-> run(BACKWARD);
  leftMotor->setSpeed(left_deg); 
}

void loop() 
{ 
  
  if (receivedChar == "R"){ 
    isReady = 1;
   }
   if (receivedChar == "S"){
    isReady = 0;
    stopMotors();
   }
   if (isReady){
    sensorLeft = analogRead(leftSensor); // reading the value from the sensor
    sensorRight = analogRead(rightSensor); // reading the value from the sensor
    Serial.print(sensorLeft); // printing the value to serial prot
    Serial.print(" "); 
    Serial.println(sensorRight); // printing the value to serial prot
  
    // LEFT
    count += 1;
    if (sensorLeft >= thresholdTape && sensorRight <= thresholdTape){
      Serial.println("Left");    
      right_deg = 0;
      if (count % 20 == 0){
        left_deg += 1;
      }
  //    slowLeft();
      leftTurn(left_deg);
    }
    // STRAIGHT
    else if (sensorLeft >= thresholdTape && sensorRight >= thresholdTape){
      Serial.println("going straight");
      right_deg = 0;
      left_deg = 0;
      goStraight();
  //    stopMotors();
     }
     // RIGHT
     else if (sensorRight >= thresholdTape && sensorLeft <= thresholdTape){
      Serial.println("Right");
      left_deg = 0;
      if (count % 20 == 0){
         right_deg += 1;
       }
  //    slowRight();
      rightTurn(right_deg);
     }
   }
  
}
