#include <ESP32Servo.h>
#include <DabbleESP32.h>

//Declare object for 4 Servo Motors  
Servo Servo_0;
Servo Servo_1;
Servo Servo_3;
Servo Gripper;

//initial angle  for servo
int angle = 0;
int angleStep = 2;

//Servo1
int baseA = 80;
//Servo2
int elbowB = 0;
//Servo3
int shoulderC = 0;
//Servo4
int gripD = 0;

bool Robot = false;
bool Stops = false;

void setup() {
  Serial.begin(115200); //Serial Monitor for Debugging
  Dabble.begin("Company 7");       //set bluetooth name of your device

  //Declare the pins to which the Servo Motors are connected to 
  Servo_0.attach(17);
  Servo_1.attach(4);
  Servo_3.attach(18);
  Gripper.attach(22);

  //Write the servo motors to initial position 
  Servo_0.write(90);
  Servo_1.write(0);
  Servo_3.write(0);
  Gripper.write(0);
}

void loop() {
  Dabble.processInput();
  Robot = true; 
  if (Robot == true) { 
    arm();
  }
}

// MANIPULATOR
void arm() { //Function to read the Analog value form POT and map it to Servo value
  int a = GamePad.getAngle();
  int b = GamePad.getRadius();
    //FORWARD
  if (a > 60 && a < 120 || GamePad.isUpPressed()) {
    shoulderC = shoulderC + angleStep;
    Servo_1.write(shoulderC);
    if(shoulderC>=90)
    {
      shoulderC = 90;
      Servo_1.write(shoulderC);
    }
    delay(20);
    Serial.println("Up");
  }
    //BACKWARD
  else if (a > 240 && a < 300 || GamePad.isDownPressed()) {
    shoulderC = shoulderC - angleStep;
    Servo_1.write(shoulderC);
    if(shoulderC<=0)
    {
      shoulderC = 0;
      Servo_1.write(shoulderC);
    }
    delay(20);
    Serial.println("Down");
  }
    //LEFT
  else if (a > 150 && a < 210 || GamePad.isLeftPressed()) {
    baseA = baseA + angleStep;
    Servo_0.write(baseA);
    if(baseA>=180)
    {
      baseA = 180;
      Servo_0.write(baseA);
    }
    delay(20);
    Serial.println("Left");
  }
    //RIGHT
  else if (a > 330 || a < 30 && b != 0 || GamePad.isRightPressed()) {
    baseA = baseA - angleStep;
    Servo_0.write(baseA);
    if(baseA<=0)
    {
      baseA = 0;
      Servo_0.write(baseA);
    }
    delay(20);
    Serial.println("Right");
  }
  //UP DOWN
  else if (GamePad.isTrianglePressed()) {
    elbowB = elbowB + angleStep;
    Servo_3.write(elbowB);
    if(elbowB>=90)
    {
      elbowB = 90;
      Servo_3.write(elbowB);
    }
    delay(20);
    Serial.println("Triangle");
  }
  else if (GamePad.isCrossPressed()) {
    elbowB = elbowB - angleStep;
    Servo_3.write(elbowB);
    if(elbowB<=0)
    {
      elbowB = 0;
      Servo_3.write(elbowB);
    }
    delay(20);
    Serial.println("Cross");
  }
  //Gripper
  else if (GamePad.isCirclePressed()) {
    gripD = gripD + angleStep;
    Gripper.write(gripD);
    if(gripD>=90)
    {
      gripD = 90;
      Gripper.write(gripD);
    }
    delay(20);
    Serial.println("Circle");
  }
  else if (GamePad.isSquarePressed()) {
    gripD = gripD - angleStep;
    Gripper.write(gripD);
    if(gripD<=0)
    {
      gripD = 0;
      Gripper.write(gripD);
    }
    delay(20);
    Serial.println("Square");
  }
  else if (GamePad.isStartPressed()) {
    Reset();
  }
}

void Reset() {
  Servo_0.write(90);
  Servo_1.write(0);
  Servo_3.write(0);
  Gripper.write(0);
}