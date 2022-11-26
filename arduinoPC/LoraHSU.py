import time
import serial
import os

os.system('"arduino-cli"')
os.system('"arduino-cli compile C:\\Users\\jessi\\git\\IoTTeamProject\\arduinoPC"')
os.system('"arduino-cli upload C:\\Users\\jessi\\git\\IoTTeamProject\\arduinoPC"')

# port : 앞에서 arduino ide에서 확인한 포트 이름을 입력합니다
# baudrate : 아두이노 setup함수에서 serial.begin에 사용된 값을 사용합니다
# 포트가 연결되면 보드가 껐다 켜집니다
# 초기화가 완료될 시간을 약간 기다려줍니다
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

path = data3.split("\\r\\n")

print(path[1])

result = path[1].replace("\\\\", "\\")
os.system(result)