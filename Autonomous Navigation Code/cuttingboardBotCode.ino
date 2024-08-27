/*
   https://www.youtube.com/watch?v=6TB0F_7SZHg
*/

#include <Servo.h>

//right motor
int in1 = 10;
int in2 = 9;
int enA = 3;

//left motor
int in3 = 7;
int in4 = 6;
int enB = 5;

//ultrasonic sensor pins
int trigPin = 13;
int echoPin = 12;
int maxDist = 150; //maximum sensing distance (objects further than this distance are ignored)
int stopDist = 50; //minimum distance from an object to stop in cm
float timeOut = 2*(maxDist+10)/100/340*1000000; //maximum time to wait for a return signal

//Servo control variable
Servo servoLook;

void setup() {

  servoLook.attach(11); //assigning the servo pin.

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  stopMove();
}

void loop() {

  servoLook.write(90); //servo is looking straight ahead
  delay(750); 
  int distance = getDistance();
  if(distance >= stopDist) //if there are no objects within the stopping distance, move forward.
  {
    analogWrite(enA, 75);
    analogWrite(enB, 75);
    moveForward();
  }
  while(distance >= stopDist)
  {
    distance = getDistance();
    delay(250);
  }
  stopMove();
  int turnDir = checkDirection();
  Serial.print(turnDir);
  switch (turnDir)
  {
    case 0:
      moveFast();
      turnLeft(200);
      break;
    case 1:
      moveFast();
      turnLeft(400);
      break;
    case 2:
      moveFast();
      turnRight(200);
      break;  
  }
}

void moveFast()
{
  analogWrite(enA, 100);
  analogWrite(enB, 100);
}

void moveForward()
{
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void stopMove()
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

void turnLeft(int duration)
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  delay(1000);  
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

void turnRight(int duration)
{
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  delay(1000);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

int getDistance()
{
  long pulseTime;
  int distance;

  //clearing the trigpin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  //Setting the trig pin to high
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  //Reading the echoPin
  pulseTime = pulseIn(echoPin, HIGH, timeOut);
  //calculating distance
  distance = (float)pulseTime * 340 / 2 / 10000;
  return distance;
  Serial.print("Distance:");
  Serial.print(distance);
}

int checkDirection()
{
  int distances [2] = {0,0};                                    //Left and right distances
  int turnDir = 1;                                              //Direction to turn, 2 left, 1 reverse, 0 right
  servoLook.write(180);                                         //Turn servo to look left
  delay(500);
  distances [0] = getDistance();                                //Get the left object distance
  servoLook.write(0);                                           //Turn servo to look right
  delay(1000);
  distances [1] = getDistance();                                //Get the right object distance
  if (distances[0]>=200 && distances[1]>=200)                   //If both directions are clear, turn left
    turnDir = 0;
  else if (distances[0]<=stopDist && distances[1]<=stopDist)    //If both directions are blocked, turn around
    turnDir = 1;
  else if (distances[0]>=distances[1])                          //If left has more space, turn left
    turnDir = 2;
  else if (distances[0]<distances[1])                           //If right has more space, turn right
    turnDir = 0;
  return turnDir;
}

