#include <AFMotor.h>
#include <Arduino.h>
#define BT Serial3
#define trai1 47
#define trai2 45
#define phai1 43
#define phai2 41
AF_DCMotor motor1(1); 
AF_DCMotor motor2(2); 
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);

char cmd;

void setup() {       
  Serial.begin(9600);
  BT.begin(9600);

  pinMode(trai1,INPUT);
  pinMode(trai2,INPUT);
  pinMode(phai1,INPUT);
  pinMode(phai2,INPUT);
}
//CONTROL
void Tien(){
  motor1.setSpeed(240); //Define maximum velocity
  motor1.run(FORWARD); //rotate the motor clockwise
  motor2.setSpeed(240); //Define maximum velocity
  motor2.run(FORWARD); //rotate the motor clockwise
  motor3.setSpeed(255);//Define maximum velocity
  motor3.run(FORWARD); //rotate the motor clockwise
  motor4.setSpeed(255);//Define maximum velocity
  motor4.run(FORWARD); //rotate the motor clockwise
  Serial.println('f');
}
void Lui(){
  motor1.setSpeed(255); //Define maximum velocity
  motor1.run(BACKWARD); //rotate the motor anti-clockwise
  motor2.setSpeed(255); //Define maximum velocity
  motor2.run(BACKWARD); //rotate the motor anti-clockwise
  motor3.setSpeed(255); //Define maximum velocity
  motor3.run(BACKWARD); //rotate the motor anti-clockwise
  motor4.setSpeed(255); //Define maximum velocity
  motor4.run(BACKWARD); //rotate the motor anti-clockwise
  Serial.println('b');
}
void Phai(){
  motor1.setSpeed(160); //Define maximum velocity
  motor1.run(BACKWARD); //rotate the motor anti-clockwise
  motor2.setSpeed(160); //Define maximum velocity
  motor2.run(BACKWARD); //rotate the motor anti-clockwise
  motor3.setSpeed(160); //Define maximum velocity
  motor3.run(FORWARD);  //rotate the motor clockwise
  motor4.setSpeed(160); //Define maximum velocity
  motor4.run(FORWARD);  //rotate the motor clockwise
  Serial.println('r');
}
void Trai(){
  motor1.setSpeed(160); //Define maximum velocity
  motor1.run(FORWARD); //rotate the motor clockwise
  motor2.setSpeed(160); //Define maximum velocity
  motor2.run(FORWARD); //rotate the motor clockwise
  motor3.setSpeed(160); //Define maximum velocity
  motor3.run(BACKWARD); //rotate the motor anti-clockwise
  motor4.setSpeed(160); //Define maximum velocity
  motor4.run(BACKWARD); //rotate the motor anti-clockwise
  Serial.println('l');
}
void TienTrai(){
  motor1.setSpeed(255); //Define maximum velocity
  motor1.run(FORWARD); //rotate the motor clockwise
  motor2.setSpeed(255); //Define maximum velocity
  motor2.run(FORWARD); //rotate the motor clockwise
  motor3.setSpeed(80); //Define maximum velocity
  motor3.run(FORWARD); //rotate the motor anti-clockwise
  motor4.setSpeed(80); //Define maximum velocity
  motor4.run(FORWARD); //rotate the motor anti-clockwise
  Serial.println('1');
}
void TienPhai(){
  motor1.setSpeed(50); //Define maximum velocity
  motor1.run(FORWARD); //rotate the motor clockwise
  motor2.setSpeed(50); //Define maximum velocity
  motor2.run(FORWARD); //rotate the motor clockwise
  motor3.setSpeed(255); //Define maximum velocity
  motor3.run(FORWARD); //rotate the motor anti-clockwise
  motor4.setSpeed(255); //Define maximum velocity
  motor4.run(FORWARD); //rotate the motor anti-clockwise
  Serial.println('2');
}
void LuiPhai(){
  motor1.setSpeed(255); //Define maximum velocity
  motor1.run(BACKWARD); //rotate the motor clockwise
  motor2.setSpeed(255); //Define maximum velocity
  motor2.run(BACKWARD); //rotate the motor clockwise
  motor3.setSpeed(102); //Define maximum velocity
  motor3.run(BACKWARD); //rotate the motor anti-clockwise
  motor4.setSpeed(102); //Define maximum velocity
  motor4.run(BACKWARD); //rotate the motor anti-clockwise
 
  Serial.println('3');
}
void LuiTrai(){
  motor1.setSpeed(102); //Define maximum velocity
  motor1.run(BACKWARD); //rotate the motor clockwise
  motor2.setSpeed(102); //Define maximum velocity
  motor2.run(BACKWARD); //rotate the motor clockwise
  motor3.setSpeed(255); //Define maximum velocity
  motor3.run(BACKWARD); //rotate the motor anti-clockwise
  motor4.setSpeed(255); //Define maximum velocity
  motor4.run(BACKWARD); //rotate the motor anti-clockwise
  Serial.println('4');
}
//RELEASE
void Dung(){
  motor1.setSpeed(0); //Define minimum velocity
  motor1.run(RELEASE); //stop the motor when release the button
  motor2.setSpeed(0); //Define minimum velocity
  motor2.run(RELEASE); //rotate the motor clockwise
  motor3.setSpeed(0); //Define minimum velocity
  motor3.run(RELEASE); //stop the motor when release the button
  motor4.setSpeed(0); //Define minimum velocity
  motor4.run(RELEASE); //stop the motor when release the button
  Serial.println('s');
}
//RECEIVE DATA
void ButtonControl(char cmd){
    switch(cmd){
    case 'F':  
      Tien();
      break;
    case 'B':  
    Lui();
      break;
    case 'L':
      Trai();
      break;
    case 'R':
      Phai();
      break;
    case '1':
      TienTrai();
      break;
    case '2':
      TienPhai();
      break;
    case '3':
      LuiPhai();
      break;
    case '4':
      LuiTrai();
      break;
    }
}

//LINE FOLLOWING
void Doline1Bong(){
  //byte trai = digitalRead(trai1)+digitalRead(trai2);
  //byte phai = digitalRead(phai1)+digitalRead(phai2);
  //line detected by both
  if(digitalRead(trai2)>digitalRead(phai1)){ 
    Trai();
  }
  else if(digitalRead(trai2)<digitalRead(phai1)){
    Phai();
  }
  else Tien();
}
void DungDoline(){
  digitalWrite(trai1,LOW);
  digitalWrite(trai2,LOW);
  digitalWrite(phai1,LOW);
  digitalWrite(phai2,LOW);
  Dung();
}

void loop(){
  if (BT.available()>0){
    cmd=BT.read();
    ButtonControl(cmd);
  } else Dung();
  bool autoMode=0;
  if(cmd=='A') autoMode=1;
  while(autoMode==1){ 
    cmd=BT.read();
    if(cmd=='X'){
      DungDoline();
      autoMode=0;
      break;
    }
    Doline1Bong();
  }
  // Serial.print(digitalRead(trai1));Serial.print(" ");
  // Serial.print(digitalRead(trai2));Serial.print("  ");
  // Serial.print(digitalRead(phai1));Serial.print(" ");
  // Serial.print(digitalRead(phai2));Serial.println();
  // TEST+HIỆU CHỈNH TỐC ĐỘ; CHỈNH FORWARD BACKWARD ở 4 hướng chéo cho phù hợp
}
