


// setup function to initialize hardware and software
int leftSensor = A0;
int rightSensor = A1;// analog pin used to connect the sharp sensor
int sensorValue1 = 0;// variable to store the values from s
int sensorValue2 = 0;

void setup(){
  // start the serial port
  int long baudRate = 9600;    // NOTE1: The baudRate for sending & receiving programs must match
  Serial.begin(baudRate);     // NOTE2: Set the baudRate to 115200 for faster communication
}

void loop() 
{  
  sensorValue1 = analogRead(leftSensor); // reading the value from the sensor
  sensorValue2 = analogRead(rightSensor); // reading the value from the sensor
  Serial.print(sensorValue1); // printing the value to serial prot
  Serial.print(" "); 
  Serial.println(sensorValue2); // printing the value to serial prot
  delay(500); // a delay so that there is not too much data
 
}
