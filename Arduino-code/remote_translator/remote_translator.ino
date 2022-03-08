#include <IRremote.h>

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
#define MUTE 0x2FD08F7

#define S_POWER 0x20250AF
#define S_U 0x202D02F
#define S_D 0x202708F
#define S_R 0x2028877
#define S_L 0x20208F7
#define S_VUP 0x202A857
#define S_VDOWN 0x20238C7
#define S_OK 0x202B04F
#define S_BACK 0x202E21D
#define S_EXIT 0x20230CF
#define S_HOME 0x20258A7
#define S_YT 0x20202FD
#define S_NETFLIX 0x202926D
#define S_MUTE 0x202F00F

#define POFF 0x202CA35

#define RECV_PIN 5
#define SEND_PIN 3
#define TVPP 4

IRsend irsend;

void setup(){
  Serial.begin(115200);
  irsend.setSendPin(SEND_PIN);

  pinMode(TVPP,OUTPUT);
}

bool tv = 1;

void loop(){
  if(Serial.available()){
        switch(Serial.read()){
          case(99):
          tv = !tv;
          digitalWrite(TVPP,tv);
          break;
          
          case(97):
          irsend.sendNEC(POWER, 32);
          break;

          case(108):
          irsend.sendNEC(U, 32);
          break;

          case(106):
          irsend.sendNEC(D, 32);
          break;

          case(105):
          irsend.sendNEC(R, 32);
          break;

          case(107):
          irsend.sendNEC(L, 32);
          break;
          
          case(103):
          irsend.sendNEC(VUP, 32);
          break;

          case(104):
          irsend.sendNEC(VDOWN, 32);
          break;

          case(109):
          irsend.sendNEC(OK, 32);
          break;

          case(110):
          irsend.sendNEC(BACK, 32);
          break;

          case(111):
          irsend.sendNEC(EXIT, 32);
          break;

          case(102):
          irsend.sendNEC(HOME, 32);
          break;

          case(100):
          irsend.sendNEC(YT, 32);
          break;

          case(101):
          irsend.sendNEC(NETFLIX, 32);
          break;

          case(98):
          irsend.sendNEC(MUTE, 32);
          break;
        }

  }
}
