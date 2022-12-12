#include <SoftwareSerial.h>
#include "SNIPE.h"
#define TXpin 11
#define RXpin 10
#define ATSerial Serial
#define oncodes 0x4C82

#include <IRremote.h>

//16byte hex key
String lora_app_key = "11 22 33 44 55 66 77 88 99 aa bb cc dd ee ff 00";  

SoftwareSerial DebugSerial(RXpin,TXpin);
SNIPE SNIPE(ATSerial);

IRsend irsend; //적외선 송신

void setup() {
  pinMode(13, OUTPUT); //적외선 송신 핀
  
  ATSerial.begin(115200);

  // put your setup code here, to run once:
  while(ATSerial.read()>= 0) {}
  while(!ATSerial);

  DebugSerial.begin(115200);

  /* SNIPE LoRa Initialization */
  if (!SNIPE.lora_init()) {
    DebugSerial.println("SNIPE LoRa Initialization Fail!");
    while (1);
  }

  /* SNIPE LoRa Set Appkey */
  if (!SNIPE.lora_setAppKey(lora_app_key)) {
    DebugSerial.println("SNIPE LoRa app key value has not been changed");
  }
  
  /* SNIPE LoRa Set Frequency */
  if (!SNIPE.lora_setFreq(LORA_CH_1)) {
    DebugSerial.println("SNIPE LoRa Frequency value has not been changed");
  }

  /* SNIPE LoRa Set Spreading Factor */
  if (!SNIPE.lora_setSf(LORA_SF_7)) {
    DebugSerial.println("SNIPE LoRa Sf value has not been changed");
  }

  /* SNIPE LoRa Set Rx Timeout 
   * If you select LORA_SF_12, 
   * RX Timout use a value greater than 5000  
  */
  if (!SNIPE.lora_setRxtout(5000)) {
    DebugSerial.println("SNIPE LoRa Rx Timout value has not been changed");
  }  
    
  DebugSerial.println("SNIPE LoRa PingPong Test");
}

void loop() {
  // put your main code here, to run repeatedly:
  
  String str=SNIPE.lora_recv(); //로라 데이터 전송받기
  delay(300);
  
  //데이터 가공하는 코드: str1=건물번호, str2=강의실번호, str3=컴퓨터 포트번호, str4=파일 경로명
  int first=str.indexOf("|");
  int second=str.indexOf("|",first+1);
  int third=str.indexOf("|",second+1);
  int length=str.length();
  String str1=str.substring(0,first);
  String str2=str.substring(first+1,second);
  String str3=str.substring(second+1,third);
  String str4=str.substring(third+1,length);
  Serial.println("haha");
  Serial.println(str1);
  Serial.println(str2);
  Serial.println(str3);
  Serial.println(str4);
  
  //코드 실행부분
  //str1=="해당 로라가 있는 건물번호"
  //str2=="해당 로라가 있는 강의실 번호"
  if( (str1=="2")&&(str2=="3") == 1){ //건물번호가 2이고 강의실번호가 3이면 실행
    //activation codes
   
    irsend.sendNEC(oncodes, 32);

    }

  delay(100);

}
