#include <Adafruit_MotorShield.h>
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *leftMotor = AFMS.getMotor(2);
Adafruit_DCMotor *rightMotor = AFMS.getMotor(4);

// Setup function to initialize hardware and software
const int leftSensor = A0;
const int rightSensor = A1;// analog pin used to connect the sharp sensor
int sensorLeft = 0;// variable to store the values from s
int sensorRight = 0;
int leftMotorSpeed = 0;
int rightMotorSpeed = 0;
int thresholdTape = 150;
const int fastSpeed = 25;
int right_deg = 0;
int left_deg = 0;
int loop_count = 0;
const int mod_value = 20;
int isReady = 0;
char receivedChar;
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
  leftMotor-> run(BACKWARD);
  leftMotor->setSpeed(left_deg); 
}

void goStraight(){
  leftMotor->run(BACKWARD);
  rightMotor-> run(FORWARD);
  leftMotor->setSpeed(fastSpeed); 
  rightMotor->setSpeed(fastSpeed); 
}

void rightTurn(int right_deg){
  rightMotor-> run(FORWARD);
  rightMotor->setSpeed(right_deg); 
}

void stopMotors(){
  leftMotor->run(RELEASE);
  rightMotor->run(RELEASE); 
}

void loop() 
{
  recvOneChar();
  if (receivedChar == 'R'){ 
    isReady = 1;
  }
  if (receivedChar == 'S'){
    isReady = 0;
    stopMotors();
  }
  if (isReady){
    sensorLeft = analogRead(leftSensor); // reading the value from the sensor
    sensorRight = analogRead(rightSensor); // reading the value from the sensor
    Serial.print(sensorLeft); // printing the value to serial prot
    Serial.print(" "); 
    Serial.println(sensorRight); // printing the value to serial prot
     
    loop_count += 1;
    // LEFT TURN: Right sensor on tape, left sensor not
    if (sensorLeft >= thresholdTape && sensorRight <= thresholdTape){
      Serial.println("Left");    
      right_deg = 0;
      if (loop_count % mod_value == 0){
        left_deg += 1;
      }
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
     // RIGHT TURN: Left sensor on tape, right sensor not
     else if (sensorRight >= thresholdTape && sensorLeft <= thresholdTape){
      Serial.println("Right");
      left_deg = 0;
      if (loop_count % mod_value == 0){
         right_deg += 1;
       }
      rightTurn(right_deg);
     }
   }
  
}
