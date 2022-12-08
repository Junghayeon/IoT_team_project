#include <SoftwareSerial.h>
#include "SNIPE.h"
#define TXpin 11
#define RXpin 10
#define BT_TX 6
#define BT_RX 5
#define ATSerial Serial

String lora_app_key="11 22 33 44 55 66 77 88 99 aa bb cc dd ee ff 00";

SoftwareSerial BT_Serial(BT_RX,BT_TX);
SNIPE SNIPE(ATSerial);
SoftwareSerial DebugSerial(RXpin,TXpin);


void setup() {
  // put your setup code here, to run once:
  BT_Serial.begin(9600);
  ATSerial.begin(115200);

  while(ATSerial.read()>=0){}
  while(!ATSerial);

  DebugSerial.begin(115200);
  
  if (!SNIPE.lora_init()) {
    DebugSerial.println("SNIPE LoRa Initialization Fail!");
    while (1);
  }
  if (!SNIPE.lora_setAppKey(lora_app_key)) {
    DebugSerial.println("SNIPE LoRa app key value has not been changed");
  }  
 
  if (!SNIPE.lora_setFreq(LORA_CH_1)) {
    DebugSerial.println("SNIPE LoRa Frequency value has not been changed");
  }
  if (!SNIPE.lora_setSf(LORA_SF_7)) {
    DebugSerial.println("SNIPE LoRa Sf value has not been changed");
  }
  if (!SNIPE.lora_setRxtout(5000)) {
    DebugSerial.println("SNIPE LoRa Rx Timout value has not been changed");
  }  
  DebugSerial.println("Lora Initialization");

  }
int count=3;
int hall=0,cnt=0,port=0;
String str;

void loop() {
  if(BT_Serial.available()>0){
      DebugSerial.println("bt success");
      char buf=(char)BT_Serial.read();
      str+=buf;
      DebugSerial.println(str);
   if(buf=='>'){
     if(SNIPE.lora_send(str)){
       DebugSerial.println("send success");
       DebugSerial.print(str);
       delay(20000);
     }
   }
  }


}
