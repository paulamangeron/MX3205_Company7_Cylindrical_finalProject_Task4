#include <IRremote.hpp>
int IRPin = 11;
int motorPin11 = 7, motorPin12 = 6, motorPin21 = 5, motorPin22 = 4;
int ena1 = 8, ena2 = 9;

IRrecv IR(irpin);
decode_results results;

void setup(){
  IR.enableIRIn();

  pinMode(motorPin11, OUTPUT);
  pinMode(motorPin12, OUTPUT);
  pinMode(motorPin21, OUTPUT);
  pinMode(motorPin22, OUTPUT);
  pinMode(ena1, OUTPUT);
  pinMode(ena2, OUTPUT);
  Serial.begin(115200);
}


void forward(){
  analogWrite(ena1, 220);
  analogWrite(ena2, 160);
  digitalWrite(motorPin11, HIGH);
  digitalWrite(motorPin12, LOW);
  digitalWrite(motorPin21, HIGH);
  digitalWrite(motorPin22, LOW);
}

void reverse(){
  analogWrite(ena1, 220);
  analogWrite(ena2, 160);
  digitalWrite(motorPin11, LOW);
  digitalWrite(motorPin12, HIGH);
  digitalWrite(motorPin21, LOW);
  digitalWrite(motorPin22, HIGH);
}

void left(){
  analogWrite(ena1, 140);
  analogWrite(ena2, 140);
  digitalWrite(motorPin11, HIGH);
  digitalWrite(motorPin12, LOW);
  digitalWrite(motorPin21, LOW);
  digitalWrite(motorPin22, HIGH);
}

void right(){
  analogWrite(ena1, 140);
  analogWrite(ena2, 140);
  digitalWrite(motorPin11, LOW);
  digitalWrite(motorPin12, HIGH);
  digitalWrite(motorPin21, HIGH);
  digitalWrite(motorPin22, LOW);
}

void stop(){
  analogWrite(ena1, 220);
  analogWrite(ena2, 160);
  digitalWrite(motorPin11, LOW);
  digitalWrite(motorPin12, LOW);
  digitalWrite(motorPin21, LOW);
  digitalWrite(motorPin22, LOW);
}

void loop(){
  if(IR.decode()){
    //movement
    if (IR.decodedIRData.decodedRawData == 0xE718FF00){
      forward();
    }
    else if (IR.decodedIRData.decodedRawData == 0xAD52FF00){
      reverse();
    }
    else if (IR.decodedIRData.decodedRawData == 0xF708FF00){
      left();
    }
    else if (IR.decodedIRData.decodedRawData == 0xA55AFF00){
      right();
    }
    else if (IR.decodedIRData.decodedRawData == 0xE31CFF00){
      stop();
    }
    else{
      stop();
    }
    IR.resume();
  }
}