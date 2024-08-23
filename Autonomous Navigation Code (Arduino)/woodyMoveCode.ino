/*
        Arduino Brushless Motor Control
     by Dejan, https://howtomechatronics.com
*/

#include <Servo.h>

Servo CH1;     // create servo object to control the ESC
Servo CH2;

//ultasonic sensor 1
int trigOne = 2;
int echoOne = 3;
//ultasonic sensor 2
int trigTwo = 4;
int echoTwo = 5;
//ultasonic sensor 3
int trigThree = 7;
int echoThree = 6;
//ultasonic sensor 4
int trigFour = 12;
int echoFour = 11;

int distanceOne;
int distanceTwo;

//side sensors
int distanceThree;
int distanceFour;

void setup() {
  pinMode(trigOne, OUTPUT);
  pinMode(echoOne, INPUT);
  pinMode(trigTwo, OUTPUT);
  pinMode(echoTwo, INPUT);
  pinMode(trigThree, OUTPUT);
  pinMode(echoThree, INPUT);
  pinMode(trigFour, OUTPUT);
  pinMode(echoFour, INPUT);

  // Attach the ESC on pin 9
  CH1.attach(9,1000,2000); // (pin, min pulse width, max pulse width in microseconds) 
  CH2.attach(10,1000,2000);
  Serial.begin(9600);
}

void stp() {
  CH1.write(90);    // Send the signal to the ESC
  CH2.write(90);    // Send the signal to the ESC
}
void fwd(){
  CH1.write(125);    // Send the signal to the ESC, original = 140
  CH2.write(90);    // Send the signal to the ESC
}

void rev(){
  CH1.write(40);    // Send the signal to the ESC
  CH2.write(90);    // Send the signal to the ESC
}

void right(){
  CH1.write(90);    // Send the signal to the ESC
  CH2.write(140);    // Send the signal to the ESC  
}
void left(){
  CH1.write(80);    // Send the signal to the ESC
  CH2.write(30);    // Send the signal to the ESC
}


void loop() {
  Obstacle();
}

void Obstacle() {
  distanceOne = ultrasonicOne();
  distanceTwo = ultrasonicTwo();
  distanceThree = ultrasonicThree();
  distanceFour = ultrasonicFour();
  
  if (distanceOne <= 23 or distanceTwo <= 23 or distanceThree <= 18 or distanceFour <= 18) {
    stp();
    delay(800);

    if (distanceThree <= 18){
      left();
      delay(400);
    }
    if (distanceFour <= 18){
      right();
      delay(400);
    }

    if (distanceOne <= 23 or distanceTwo <= 23) {
      rev();
      delay(200);
      right();
      delay(400);
    }

    distanceOne = ultrasonicOne();
    distanceTwo = ultrasonicTwo();
    distanceThree = ultrasonicThree();
    distanceFour = ultrasonicFour();
  } else {
    fwd();
  }
}

//ultrasonic sensor distance reading function
int ultrasonicOne() {
  digitalWrite(trigOne, LOW);
  delayMicroseconds(4);
  digitalWrite(trigOne, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigOne, LOW);
  long tOne = pulseIn(echoOne, HIGH);
  long cmOne = tOne / 29 / 2; //time convert distance
  return cmOne;
}

int ultrasonicTwo() {
  digitalWrite(trigTwo, LOW);
  delayMicroseconds(4);
  digitalWrite(trigTwo, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigTwo, LOW);
  long tTwo = pulseIn(echoTwo, HIGH);
  long cmTwo = tTwo / 29 / 2; //time convert distance
  return cmTwo;
}

int ultrasonicThree() {
  digitalWrite(trigThree, LOW);
  delayMicroseconds(4);
  digitalWrite(trigThree, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigThree, LOW);
  long tThree = pulseIn(echoThree, HIGH);
  long cmThree = tThree / 29 / 2; //time convert distance
  return cmThree;
}

int ultrasonicFour() {
  digitalWrite(trigFour, LOW);
  delayMicroseconds(4);
  digitalWrite(trigFour, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigFour, LOW);
  long tFour = pulseIn(echoFour, HIGH);
  long cmFour = tFour / 29 / 2; //time convert distance
  return cmFour;
}
