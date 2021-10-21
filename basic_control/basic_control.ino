#include <Adafruit_MotorShield.h>
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *leftMotor = AFMS.getMotor(2);
Adafruit_DCMotor *rightMotor = AFMS.getMotor(4);

// Setup function to initialize hardware and software
const int leftSensor = A0; // analog pin used to connecting to the left sensor
const int rightSensor = A1; // analog pin used to connecting to the right sensor
int sensorLeft = 0; // storing value from left sensor
int sensorRight = 0; // storing value from right sensor
int leftMotorSpeed = 0; // left motor speed
int rightMotorSpeed = 0; // right motor speed
int thresholdTape = 150; // If the sensor reading is higher than the threshold, then its on the sensor
const int fastSpeed = 25; // fast motor speed
int right_deg = 0; // variable for controlling steepness of right turns
int left_deg = 0; // variable for controlling steepness of left turns
int loop_count = 0; // loop iteration
const int mod_value = 20; // value determining how often the turn changes
int isReady = 0; // 0 or 1 to determine if the robot is not ready or ready
char receivedChar; // value received from python
boolean newData = false;

void setup(){
  // start the serial port
  int long baudRate = 9600;  // NOTE1: The baudRate for sending & receiving programs must match
  Serial.begin(baudRate);    // NOTE2: Set the baudRate to 115200 for faster communication
  Serial.begin(9600);        // set up Serial library at 9600 bps
  AFMS.begin(); 
}

void recvOneChar() {
  // Receiving a character from serial
    if (Serial.available() > 0) {
        receivedChar = Serial.read();
        newData = true;
    }
}

void showNewData() {
  // Checking if new data has been received
    if (newData == true) {
        Serial.println(receivedChar);
        newData = false;
    }
}

void leftTurn(int left_deg){
  // turn left with the steepness controlled by the input left_deg
  leftMotor-> run(BACKWARD);
  leftMotor->setSpeed(left_deg); 
}

void goStraight(){
  // go straight
  leftMotor->run(BACKWARD);
  rightMotor-> run(FORWARD);
  leftMotor->setSpeed(fastSpeed); 
  rightMotor->setSpeed(fastSpeed); 
}

void rightTurn(int right_deg){
  // turn left with the steepness controlled by the input left_deg
  rightMotor-> run(FORWARD);
  rightMotor->setSpeed(right_deg); 
}

void stopMotors(){
  // stop the motors
  leftMotor->run(RELEASE);
  rightMotor->run(RELEASE); 
}

void loop() 
{
  recvOneChar();
  // if R is received from the serial moniter, then the robot will run
  if (receivedChar == 'R'){ 
    isReady = 1;
  }
  // if S is received from the serial moniter, then the robot will stop
  if (receivedChar == 'S'){
    isReady = 0;
    stopMotors();
  }
  if (isReady){
    sensorLeft = analogRead(leftSensor); // reading the value from the sensor
    sensorRight = analogRead(rightSensor); // reading the value from the sensor
    Serial.print(sensorLeft); // printing the value to serial port
    Serial.print(" "); 
    Serial.println(sensorRight); // printing the value to serial port
     
    loop_count += 1;
    // LEFT TURN: Right sensor on tape, left sensor not
    if (sensorLeft >= thresholdTape && sensorRight <= thresholdTape){
      Serial.println("Left");    
      right_deg = 0; // making the right wheel stop
      // if the robot continues to enter this statement, then increase the sharpness of the left turn
      if (loop_count % mod_value == 0){
        left_deg += 1;
      }
      leftTurn(left_deg);
    }
    // STRAIGHT
    // both sensors are on the tape
    else if (sensorLeft >= thresholdTape && sensorRight >= thresholdTape){
      Serial.println("going straight");
      right_deg = 0;
      left_deg = 0;
      goStraight();
     }
     // RIGHT TURN: Left sensor on tape, right sensor not
     else if (sensorRight >= thresholdTape && sensorLeft <= thresholdTape){
      Serial.println("Right");
      left_deg = 0; // making the left wheel stop
       // if the robot continues to enter this statement, then increase the sharpness of the right turn
      if (loop_count % mod_value == 0){
         right_deg += 1;
       }
      rightTurn(right_deg);
     }
   }
  
}
