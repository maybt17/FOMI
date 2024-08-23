/*
        Arduino Brushless Motor Control
     by Dejan, https://howtomechatronics.com
        Obstacle Avoiding Robot
     by Michael Klements, The DIY Life, YouTube
        How to make an obstacle avoiding robot with three ultrasonic sensors
     by srituhobby, https://srituhobby.com

*/

#include <Servo.h>

Servo CH1;     // create servo object to control the ESC
Servo CH2;

int trig1 = 2;
int echo1 = 3;
int trig2 = 6;
int echo2 = 5;
int maxDist = 500;
int stopDist = 300;

long pulseTime1;
long pulseTime2;

int duration1;
int duration2;
int distance1;
int distance2;

float timeOut = 2*(maxDist+10)/100/340*1000000;   //Maximum time to wait for a return signal

//90 for stp, fwd, and rev means to follow suit of CH1
//90 for left and right means to follow suit of CH2 
//This is because CH2 controls turning and CH1 controls forwards and backwards. If chanel two is getting more power it's
//assuming it's turning and vice versa for CH1 forward/backwards.
//above 90 = forwards for CH1 (180 <-- full power forwards)
//below 90 = backwards for CH1 (50 is slower than 0 <-- 0 is full power backwards)

//without battery on, just arduino pwr from computer, max is 270
//30 prolly stopping distance

void setup() {

  //Serial.begin(9600);

  // Attach the ESC on pin 9
  CH1.attach(9,1000,2000); // (pin, min pulse width, max pulse width in microseconds) 
  CH2.attach(10,1000,2000);
  Serial.begin(9600);

  //ultrasonic #1
  pinMode(trig1,OUTPUT);                           //Assign ultrasonic sensor pin modes
  pinMode(echo1,INPUT);

  //ultrasonic #2
  pinMode(trig2,OUTPUT);                           //Assign ultrasonic sensor pin modes
  pinMode(echo2,INPUT);
}

void stp() {
  CH1.write(90);    // Send the signal to the ESC
  CH2.write(90);    // Send the signal to the ESC
}

void fwd(){
  CH1.write(140);    // Send the signal to the ESC
  CH2.write(90);    // Send the signal to the ESC
}

void rev(){
  CH1.write(40);    // Send the signal to the ESC
  CH2.write(90);    // Send the signal to the ESC
}

void left(){
  CH1.write(90);    // Send the signal to the ESC
  CH2.write(130);    // Send the signal to the ESC  
}
void right(){
  CH1.write(90);    // Send the signal to the ESC
  CH2.write(40);    // Send the signal to the ESC
}


int sensorONE()
{
  digitalWrite(trig1, LOW);
  delayMicroseconds(1000);

  //Setting the trip pin to high
  digitalWrite(trig1, HIGH);
  delayMicroseconds(10); //On for 10 microseconds, so trig is sending out its stuff
  digitalWrite(trig1, LOW);

  //Reads the echoPin, returns the sound wave travel time in microseconds
  pulseTime1 = pulseIn(echo1, HIGH);         //Measure the time for the pulse to return
  duration1 = pulseTime1 * 0.034/2; 
  return duration1;
}

int sensorTWO()
{
  digitalWrite(trig2, LOW);
  delayMicroseconds(1000);

  //Setting the trip pin to high
  digitalWrite(trig2, HIGH);
  delayMicroseconds(10); //On for 10 microseconds, so trig is sending out its stuff
  digitalWrite(trig2, LOW);

  //Reads the echoPin, returns the sound wave travel time in microseconds
  pulseTime2 = pulseIn(echo2, HIGH);         //Measure the time for the pulse to return
  duration2 = pulseTime2 * 0.034/2; 
  return duration2;
}

void loop() {     
  distance1 = sensorONE();
  //distance2 = sensorTWO();

  //Serial.print("Distance1:");
  //Serial.println(sensorONE());

  //Serial.print("Distance2:");
  //Serial.println(sensorTWO());
          
  if(distance1 > stopDist) //&& distance2 > stopDist)                      //If there are no objects within the stopping distance, move forward
  {
    fwd();

  } while(distance1 > stopDist) //&& distance2 > stopDist)                    //Keep checking the object distance until it is within the minimum stopping distance
  {
    distance1 = sensorONE();
    //distance2 = sensorTWO();  
    delay(250);
  }

  if(distance1 <= stopDist) //or distance2 <= stopDist)
  {
    stp();
    delay(2000);
  } while (distance1 <= stopDist) //or distance2 <= stopDist)
  {
    distance1 = sensorONE();
    //distance2 = sensorTWO();  
    delay(250);
  }
  
}


/*
void avoidObstacles(){
  // Avoid any objects
  if ((distance_leftctr < limit) && (distance_rightctr < limit)){
 
    // Switch back and forth
    if (right_or_left) {
      rightAvoid();
    }
    else {
      leftAvoid();
    }
    right_or_left = !(right_or_left);
  }
  else if((distance_left < limit) || (distance_leftctr < limit)) {
    rightAvoid();
  }
  else if((distance_right < limit) || (distance_rightctr < limit)) {
    leftAvoid();
  }
  else {
    calculateHeadingError();
 
    // Correct the heading if needed
    if (abs(heading_error) <= abs(heading_threshold)){
        goForward();
    }
    else {
      correctHeading();
      goForward();
    }
    // Check to see if we have crossed the tape
    readIRSensor();
    delay(50);
  }
}
*/
 