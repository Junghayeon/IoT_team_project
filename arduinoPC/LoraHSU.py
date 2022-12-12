import time
import serial
import os

os.system('"arduino-cli"')
# 해당 경로명은 LoraHSU_PCarduino.ino 파일의 경로명으로 재설정
os.system('"arduino-cli compile C:\\Users\\jessi\\git\\IoTTeamProject\\arduinoPC"')
os.system('"arduino-cli upload C:\\Users\\jessi\\git\\IoTTeamProject\\arduinoPC"')

# port : 로라가 보내준 데이터에서 포트번호 확인
# baudrate : 아두이노 setup함수에서 serial.begin에 사용된 값을 사용
arduino = serial.Serial(port = "COM12", baudrate = 9600)
time.sleep(1)

# 시리얼에 test string을 보냄
arduino.write(b"no info")
# 잠시 대기
time.sleep(1)
data1 = arduino.read_all()

arduino.close()

data2 = str(data1)
data3 = str(data2[0:500])

# 읽어온 경로명 가공하기
path = data3.split("\\r\\n")
path1 = str(path).split("g")

result = path[1].replace("\\\\", "\\")
final_result = path1[1].replace("'","")

# 해당 경로명에서 파일 열기
os.system(final_result)