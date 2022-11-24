#include<SoftwareSerial.h>

void setup()
{
    Serial.begin(9600);
}

void loop()
{

    String path = "C:\\Users\\jessi\\Desktop\\HSU\\14.pdf";

    Serial.println(path);

    // 만약 시리얼에 읽을 데이터가 있다면...
    if(Serial.available())
    {
      // 시리얼에서 읽어온 데이터를 다시 시리얼로 출력
        Serial.write(Serial.read());
    }
}
