#include <NewPing.h>
#include <Servo.h> 

#define TRIG_PIN A4 
#define ECHO_PIN A5 
#define MAX_DISTANCE 200 
NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE); 
Servo myservo;   

boolean goesForward=false;
int distance = 100;
int speedSet = 0;

//Motor A
const int motorPin1  = 11;  
const int motorPin2  = 10;  

//Motor B
const int motorPin3  = 6; 
const int motorPin4  = 5;  

//left & right dist
int distanceR = 0;
int distanceL =  0;

void setup() {

  myservo.attach(9);  
  myservo.write(120); 
  delay(2000);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
}

void loop() { 
  if (distance<=30){
    moveStop();
    delay(300);
    moveBackward();
    delay(300);
    moveStop();
    delay(200);
    distance = lookRight();
    delay(200);
    distance = lookLeft();
    delay(200);
    if(distanceL<=distanceR){
      turnRight();
      moveStop();
    }
    else{
      turnLeft();
      moveStop();
    }
    
  }else{
    moveForward();
  }
  distance = readPing();
}
int lookRight()
{
    myservo.write(50); 
    delay(500);
    int distance = readPing();
    delay(100);
    myservo.write(120); 
    return distance;
}

int lookLeft()
{
    myservo.write(170); 
    delay(500);
    int distance = readPing();
    delay(100);
    myservo.write(120); 
    return distance;
}



void moveStop() {
    analogWrite(motorPin1, 0);
    analogWrite(motorPin2, 0);
    analogWrite(motorPin3, 0);
    analogWrite(motorPin4, 0);
  } 
  
void moveForward(){
  
    analogWrite(motorPin1, 180);
    analogWrite(motorPin2, 0);
    analogWrite(motorPin3, 180);
    analogWrite(motorPin4, 0);
    calc();
}
void moveBackward() {
    
    analogWrite(motorPin1, 0);
    analogWrite(motorPin2, 180);
    analogWrite(motorPin3, 0);
    analogWrite(motorPin4, 180);   
  
}  
void turnRight() {
    analogWrite(motorPin1, 180);
    analogWrite(motorPin2, 0);
    analogWrite(motorPin3, 0);
    analogWrite(motorPin4, 180);    
    delay(300);
    moveForward();      
  
} 
 
void turnLeft() {
  analogWrite(motorPin1, 0);
    analogWrite(motorPin2, 180);   
 analogWrite(motorPin3, 180);
    analogWrite(motorPin4, 0);     
  delay(300);
   moveForward();
}  
int readPing() { 
  delay(70);
  int cm = sonar.ping_cm();
  if(cm==0)
  {
    cm = 250;
  }
  return cm;
}
void calc(){
  distance = readPing();
  delay(50);
  distance = readPing();
  delay(50);
  distance = readPing();
  delay(10);
  if(distance<=30){
    moveStop();
    delay(300);
    moveBackward();
    delay(300);
    moveStop();
    delay(300);
    distance = lookRight();
    delay(100);
    distance = lookLeft();
    delay(100);
    if(distanceL<=distanceR){
      turnRight();
      moveStop();
    }
    else{
      turnLeft();
      moveStop();
    }
    
  }else{
    moveForward();
  }
}

