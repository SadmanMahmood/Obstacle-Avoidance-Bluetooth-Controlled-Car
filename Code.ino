//---------OOBSTACLE AVOIDANCE BLUETOOTH CONTROLLED CAR-----------
//-------------CODE CREATED BY SADMAN MAHMOOD----------------------
//-----------------------01/06/2020-------------------------------
//-----------------https://github.com/SadmanMahmood----------------
//-----------------Email : MAPLESADMAN@GMAIL.COM-------------------



#include <SoftwareSerial.h>
//Declaring the Bluetooth pins
SoftwareSerial Bluetooth(0, 1);

const int motorPin1 = 5;          //IN2  connect to pin 5 of Arduino
const int motorPin2 = 6;          //IN1  connect to pin 6 of Arduino
const int motorPin3 = 10;         //IN3  connect to pin 10 of Arduino
const int motorPin4 = 9;          //IN4  connect to pin 9 of Arduino
const int trigPin = 4;            // trig pin of SONAR SENSOR
const int echoPin = 2;            // echo pin of SONAR SENSOR
const int buzzerPin = 3;          //Connecet the buzzer pin to pin 3 of ARDUINO

String dataIn = "";
long duration, distance;

void setup() {

  delay (random(500,2000));
  Serial.begin(9600);
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode (buzzerPin, OUTPUT);

  //Starting the Bluetooth SERIAL COMMUNICATION
  Bluetooth.begin(9600);
  Bluetooth.setTimeout(1);
  delay(20);
}

void loop() {
  //Measuring distance with SONAR SENSOR
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);  
  digitalWrite(trigPin, HIGH);    
  delayMicroseconds(10);
  duration = pulseIn(echoPin, HIGH); // receive reflected waves
  distance = duration / 58.2;   // convert to distance
  delay(10);
 
  if(Serial.available() > 0){
     dataIn = Bluetooth.readString();

  //To move the car FORWARD
  if (dataIn.startsWith("F")){   
    analogWrite(motorPin1, 0);
    analogWrite(motorPin2, 255);
    analogWrite(motorPin3, 255);
    analogWrite(motorPin4, 0);
    }
  //To move the car BACKWARD
  if (dataIn.startsWith("B")){
    analogWrite(motorPin1, 255);
    analogWrite(motorPin2, 0);
    analogWrite(motorPin3, 0);
    analogWrite(motorPin4, 255);
  }
  //To move the car RIGHT
  if (dataIn.startsWith("R")){
    analogWrite(motorPin1, 0);
    analogWrite(motorPin2, 255);
    analogWrite(motorPin3, 0);
    analogWrite(motorPin4, 255);
  }
   //To move the car LEFT
  if (dataIn.startsWith("L")){
    analogWrite(motorPin1, 255);
    analogWrite(motorPin2, 0);
    analogWrite(motorPin3, 255);  
    analogWrite(motorPin4, 0);
  }
   //To STOP the car
   if (dataIn.startsWith("S")){
    analogWrite(motorPin1, 0);
    analogWrite(motorPin2, 0);
    analogWrite(motorPin3, 0);
    analogWrite(motorPin4, 0);
  }
  //Taking ACTIONS according to the distance
  if (distance < 30){
    tone (buzzerPin, 500, 1000);
  }
  if (distance < 25){
    tone (buzzerPin, 1000, 1000);  
  }
  if (distance < 20){
    tone (buzzerPin, 2000, 1000);
  }
  if (distance < 18){
    tone (buzzerPin, 2000, 1000);
    analogWrite(motorPin1, 0);
    analogWrite(motorPin2, 0);
    analogWrite(motorPin3, 0);
    analogWrite(motorPin4, 0);
    delay(2000);

     if (dataIn.startsWith("B")){
      analogWrite(motorPin1, 255);
      analogWrite(motorPin2, 0);
      analogWrite(motorPin3, 0);
      analogWrite(motorPin4, 255);
    }
  
    if (dataIn.startsWith("R")){
      analogWrite(motorPin1, 0);
      analogWrite(motorPin2, 255);
      analogWrite(motorPin3, 0);
      analogWrite(motorPin4, 255);
    }
  
    if (dataIn.startsWith("L")){
      analogWrite(motorPin1, 255);
      analogWrite(motorPin2, 0);
      analogWrite(motorPin3, 255);  
      analogWrite(motorPin4, 0);
    }
  
     if (dataIn.startsWith("S")){
      analogWrite(motorPin1, 0);
      analogWrite(motorPin2, 0);
      analogWrite(motorPin3, 0);
      analogWrite(motorPin4, 0);
    }
  

  }
     }

}
