#include "Uno_defines.h"
#include <SoftwareSerial.h>
SoftwareSerial SerialBT(RXpin,TXpin);

char cmd;

  void buttonSetup(){
    pinMode(Tien, INPUT_PULLUP);
    pinMode(Lui, INPUT_PULLUP);
 
    pinMode(QuayPhai, INPUT_PULLUP);
    pinMode(QuayTrai, INPUT_PULLUP);

    pinMode(AutoMode,INPUT_PULLUP);
    pinMode(StopAutoMode,INPUT_PULLUP);

  }
 

void setup() {
  Serial.begin(9600);
  SerialBT.begin(9600);
  buttonSetup();
 
}
void ButtonRead(){
  bool F=digitalRead(Tien);
  bool B=digitalRead(Lui);
  bool L=digitalRead(QuayTrai);
  bool R=digitalRead(QuayPhai);
    if (!F&&B&&L&&R){
      cmd = 'F';
      SerialBT.write(cmd);
      Serial.println('f');
    }
    if (F&&!B&&L&&R){
      cmd = 'B';
      SerialBT.write(cmd);
      Serial.println('b');
    }
 
    if (F&&B&&L&&!R){
      cmd = 'R';
      SerialBT.write(cmd);
      Serial.println('r');
    }
 
    if (F&&B&&!L&&R){
      cmd = 'L';
      SerialBT.write(cmd);
      Serial.println('l');
    }                  
    if(digitalRead(AutoMode)==0){
      cmd= 'A';
      SerialBT.write(cmd);
      Serial.println("AutoMode ON!");
    }
    if(digitalRead(StopAutoMode)==0){
      cmd= 'X';
      SerialBT.write(cmd);
      Serial.println("AutoMode OFF!");
    }
    if (!F&&B&&!L&&R){
      cmd = '1';
      SerialBT.write(cmd);
      Serial.println('1');
    }
    if (!F&&B&&L&&!R){
      cmd = '2';
      SerialBT.write(cmd);
      Serial.println('2');
    }
    if (F&&!B&&L&&!R){
      cmd = '3';
      SerialBT.write(cmd);
      Serial.println('3');
    }
    if (F&&!B&&!L&&R){
      cmd = '4';
      SerialBT.write(cmd);
      Serial.println('4');
    }
}

void loop(){
  ButtonRead();
}



 