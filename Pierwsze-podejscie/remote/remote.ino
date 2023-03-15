#include <IRremote.h>
#include <IRremoteInt.h>

#define POWER 0x2FD48B7
#define U 0x2FD41BE
#define D 0x2FDC13E
#define R 0x2FD9867
#define L 0x2FDB847
#define VUP 0x2FD58A7
#define VDOWN 0x2FD7887
#define OK 0x2FD916E
#define BACK 0x2FD9B64
#define EXIT 0x2FD1AE5
#define HOME 0x2FD5BA4
#define YT 0x2FD05FA
#define NETFLIX 0x2FD54AB
#define POFF 0x1F00BAD
#define STANDBY 0xFFFFFFFF


IRsend irsend;

//const int RECV_PIN = 7;
//IRrecv irrecv(RECV_PIN);
//decode_results results;

void setup(){
  for(byte i = 2;i <= 10;i++){
    pinMode(i,INPUT);
  }
  pinMode(LED_BUILTIN,OUTPUT);
  
  Serial.begin(9600);
  irsend.setSendPin(A1);
  //irrecv.enableIRIn();
}

inline byte findState(){
  return digitalRead(10)*2+digitalRead(9);
}

byte findOnPin(){
  for(byte i = 2;i < 9;i++){
    if(digitalRead(i)){
      return i;
    }
  }
  return 0;
}

void loop(){
//  if (irrecv.decode(&results)){
//        Serial.println(results.value, HEX);
//        irrecv.resume();
//  }

  if(findState() == 0){
    digitalWrite(LED_BUILTIN,0);
    switch(findOnPin()){
      case 2:
      irsend.sendNEC(R, 32); //R
      Serial.println("R");
      delay(200);
      break;
      case 3:
      irsend.sendNEC(HOME, 32); //HOME
      Serial.println("BACK");
      delay(200);
      break;
      case 4:
      irsend.sendNEC(D, 32); //D
      Serial.println("D");
      delay(200);
      break;
      case 5:
      irsend.sendNEC(OK, 32); //OK
      Serial.println("OK");
      delay(200);
      break;
      case 6:
      irsend.sendNEC(U, 32); //U
      Serial.println("U");
      delay(200);
      break;
      case 7:
      irsend.sendNEC(L, 32); //L
      Serial.println("L");
      delay(200);
      break;
      case 8:
      irsend.sendNEC(BACK, 32); //BACK
      Serial.println("HOME");
      delay(200);
      break;
      default:
      digitalWrite(A1,0);
    }
  }else if(findState() == 1){
    digitalWrite(LED_BUILTIN,1);
    switch(findOnPin()){
      case 2:
      irsend.sendNEC(NETFLIX, 32); //NETFLIX
      Serial.println("NETFLIX");
      delay(200);
      break;
      case 3:
      irsend.sendNEC(POFF, 32); //POFF
      Serial.println("BACK");
      delay(200);
      break;
      case 4:
      irsend.sendNEC(VDOWN, 32); //VDOWN
      Serial.println("VDOWN");
      delay(200);
      break;
      case 5:
      irsend.sendNEC(POWER, 32); //POWER
      Serial.println("POWER");
      delay(200);
      break;
      case 6:
      irsend.sendNEC(VUP, 32); //VUP
      Serial.println("VUP");
      delay(200);
      break;
      case 7:
      irsend.sendNEC(YT, 32); //YT
      Serial.println("YT");
      delay(200);
      break;
      case 8:
      irsend.sendNEC(BACK, 32); //BACK
      Serial.println("EXIT");
      delay(200);
      break;
      default:
      digitalWrite(A1,0);
    }
  }
}

//|8||6||3|
//|7||5||2|
//| ||4|| |
//


//PROTOCOL - NEC
//Working remote:
//POWER - 2FD48B7
//U - 2FD41BE
//D - 2FDC13E
//L - 2FD9867
//R - 2FDB847
//VUP - 2FD58A7
//VDOWN - 2FD7887
//OK - 2FD916E
//BACK - 2FD9B64
//EXIT - 2FD1AE5
//HOME - 2FD5BA4
//YT - 2FD05FA
//NETFLIX - 2FD54AB
//STANDBY - FFFFFFFF
//===============
//Broken remote:
//POWER - 20250AF
//===============
