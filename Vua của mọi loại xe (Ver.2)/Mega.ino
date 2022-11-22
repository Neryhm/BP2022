#include "Mega_defines.h"
 
#define BT Serial3

// TCCR0B = TCCR0B & B11111000 | B00000010;
char cmd;
///--------------------Chuyển động của xe-------------
void Dung(){
   analogWrite(FrontENA,0);
   analogWrite(FrontENB,0);
   analogWrite(BackENA,0);
   analogWrite(BackENB,0);
   digitalWrite(FL1,1);
   digitalWrite(FL2,1);
   digitalWrite(FR1,1);
   digitalWrite(FR2,1);
   digitalWrite(BL1,1);
   digitalWrite(BL2,1);
   digitalWrite(BR1,1);
   digitalWrite(BR2,1);
 
   Serial.println('S');
}
void Tien(){
   analogWrite(FrontENA,180);
   analogWrite(FrontENB,180);
   analogWrite(BackENA,180);
   analogWrite(BackENB,180);
 
   digitalWrite(FL1,1);
   digitalWrite(FL2,0);
 
   digitalWrite(FR1,1);
   digitalWrite(FR2,0);

   digitalWrite(BL1,1);
   digitalWrite(BL2,0);
   
   digitalWrite(BR1,1);
   digitalWrite(BR2,0);

   Serial.println('F');
}
void Lui(){
   analogWrite(ENA,180);
   analogWrite(ENB,180);
 
   digitalWrite(M11,0);
   digitalWrite(M12,1);
 
   digitalWrite(M21,0);
   digitalWrite(M22,1);
   Serial.println('B');
}
void QuayTrai(){
   analogWrite(ENA,180);
   analogWrite(ENB,180);
 
   digitalWrite(M11,1);
   digitalWrite(M12,0);
 
   digitalWrite(M21,0);
   digitalWrite(M22,1);
   Serial.println('L');
}
void QuayPhai(){
   analogWrite(ENA,180);
   analogWrite(ENB,180);
 
   digitalWrite(M11,0);
   digitalWrite(M12,1);
 
   digitalWrite(M21,1);
   digitalWrite(M22,0);
   Serial.println('R');
}
void TienTrai(){
   analogWrite(ENA,230);
   analogWrite(ENB,47);
 
   digitalWrite(M11,1);
   digitalWrite(M12,0);
 
   digitalWrite(M21,1);
   digitalWrite(M22,0);
 
   Serial.println('1');
}
void TienPhai(){
   analogWrite(ENA,47);
   analogWrite(ENB,230);
 
   digitalWrite(M11,1);
   digitalWrite(M12,0);
 
   digitalWrite(M21,1);
   digitalWrite(M22,0);
 
   Serial.println('2');
}
void LuiTrai(){
   analogWrite(ENA,230);
   analogWrite(ENB,47);
 
   digitalWrite(M11,0);
   digitalWrite(M12,1);
 
   digitalWrite(M21,0);
   digitalWrite(M22,1);
 
   Serial.println('4');
}
void LuiPhai(){
   analogWrite(ENA,47);
   analogWrite(ENB,230);
 
   digitalWrite(M11,0);
   digitalWrite(M12,1);
 
   digitalWrite(M21,0);
   digitalWrite(M22,1);
 
   Serial.println('3');
}
//------------------------Chuyển động khi dò line--------------------
void TienLine(){
   analogWrite(ENA,120);
   analogWrite(ENB,120);
 
   digitalWrite(M11,1);
   digitalWrite(M12,0);
 
   digitalWrite(M21,1);
   digitalWrite(M22,0);
}
void TraiLine(){
   analogWrite(ENA,180);
   analogWrite(ENB,180);
 
   digitalWrite(M11,1);
   digitalWrite(M12,0);
 
   digitalWrite(M21,0);
   digitalWrite(M22,1);
}
void PhaiLine(){
   analogWrite(ENA,180);
   analogWrite(ENB,180);
 
   digitalWrite(M11,0);
   digitalWrite(M12,1);
 
   digitalWrite(M21,1);
   digitalWrite(M22,0);
}
//---------------------Doline2bongngungu---------------
void Doline1Bong(){
  byte trai = digitalRead(trai1)+digitalRead(trai2);
  byte phai = digitalRead(phai1)+digitalRead(phai2);
  //line detected by both
  if(digitalRead(trai)<digitalRead(phai)){ //chạm line bên trái
    TraiLine();
  }
  else if(digitalRead(trai)>digitalRead(phai)){ //chạm line bên trái
    PhaiLine();
  }
  else TienLine();
}

void DungDoline(){
  digitalWrite(trai1,LOW);
  digitalWrite(trai2,LOW);
  digitalWrite(phai1,LOW);
  digitalWrite(phai2,LOW);
  Dung();
}
 
//------------------------------------------
void pinModeSetup(){
  pinMode(FL1,OUTPUT);
  pinMode(FL2,OUTPUT);
  pinMode(FR1,OUTPUT);
  pinMode(FR2,OUTPUT);
  pinMode(BL1,OUTPUT);
  pinMode(BL2,OUTPUT);
  pinMode(BR1,OUTPUT);
  pinMode(BR2,OUTPUT);
  pinMode(FrontENA,OUTPUT);
  pinMode(FrontENB,OUTPUT);
  pinMode(BackENA,OUTPUT);
  pinMode(BackENB,OUTPUT);
 
  pinMode(left,INPUT);
  pinMode(right,INPUT);
}
//-----------------Đọc lệnh từ cmd và điều khiển động cơ-----
void ButtonControl(char cmd){
    switch(cmd){
    case 'F':  
      Tien();
      break;
    case 'B':  
       Lui();
      break;
    case 'L':  
      QuayTrai();
      break;
    case 'R':
      QuayPhai();
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

   
//----------------------------------------------
void setup() {
  Serial.begin(9600);
  BT.begin(9600);
  pinModeSetup();
}
 
void loop() {
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
}
