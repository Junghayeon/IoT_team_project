#include <SoftwareSerial.h>
#include "SNIPE.h"
#define TXpin 11
#define RXpin 10
#define BT_TX 6
#define BT_RX 5
#define ATSerial Serial

String lora_app_key="11 22 33 44 55 66 77 88 99 aa bb cc dd ee ff 00";
//SoftwareSerial DebugSerial(RXpin,TXpin);

SoftwareSerial BT_Serial(BT_RX,BT_TX);
SNIPE SNIPE(ATSerial);
char path[50]; //파일경로
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  BT_Serial.begin(9600);
  }
int count=3;
int hall=0,cnt=0,port=0;
String str;
void loop() {
    //Serial.println(" started");
  // put your main code here, to run repeatedly:
  if(BT_Serial.available()>0){
  
    if(count==3){
      hall=BT_Serial.parseInt();
      Serial.print("hall: ");
      Serial.println(hall);
    }
    else if(count==2){
      cnt=BT_Serial.parseInt();
      Serial.print("cnt= ");
      Serial.println(cnt);
    }
    else if(count==1){
      port=BT_Serial.parseInt();
      Serial.print("port= ");
      Serial.println(port);
    }
    else if(count<=0){
      char buf=(char)BT_Serial.read();
      str+=buf;
      Serial.println(str);
    }

    count--;    
    Serial.println("\n");
    
  }
  /*
    Serial.print("receive data: ");
    Serial.print(hall);
    Serial.print(count);
    Serial.print(str);
    */
  /*
  if(BT_Serial.available()>0){
    //receiveData=BT_Serial.read();
    //Serial.print("receive ddata: ");
    //Serial.println(receiveData);

    Serial.print(BT_Serial.read());
  }
  */
}
