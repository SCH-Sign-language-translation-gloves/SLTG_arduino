#Operation interval detection

import firebase_admin
from firebase_admin import credentials
from firebase_admin import db
import numpy as np

# import matplotlib.pyplot as plt
# from matplotlib.animation import FuncAnimation

#Firebase database 인증 및 앱 초기화
cred = credentials.Certificate('./arduino-app-b69fd-firebase-adminsdk-11dwf-c09ef584f0.json')
firebase_admin.initialize_app(cred,{
    'databaseURL' : 'https://arduino-app-b69fd-default-rtdb.firebaseio.com/'
})

#데이터베이스 데이터 가져오기
accel_x = db.reference('sensor_data').child('accel x').get()
accel_y = db.reference('sensor_data').child('accel y').get()
accel_z = db.reference('sensor_data').child('accel z').get()

flex_1 = db.reference('sensor_data').child('flex 1').get()
flex_2 = db.reference('sensor_data').child('flex 2').get()
flex_3 = db.reference('sensor_data').child('flex 3').get()
flex_4 = db.reference('sensor_data').child('flex 4').get()
flex_5 = db.reference('sensor_data').child('flex 5').get()

gyro_x = db.reference('sensor_data').child('zyro x').get()
gyro_y = db.reference('sensor_data').child('zyro y').get()
gyro_z = db.reference('sensor_data').child('zyro z').get()

#firebase에서 받은 데이터들을 다차원배열로 넣기
fire_list = [accel_x, accel_y, accel_z, gyro_x, gyro_y, gyro_z, flex_1, flex_2, flex_3, flex_4, flex_5]

#문자열로 받은 데이터들(fire_list)에서 각속도, 가속도 센서 데이터들만 float로 바꿔주기 위한 코드
sensor_list = []
for i in range(6):
    N = []
    for j in range(len(fire_list)):
        N.append(float(fire_list[i][j]))
    sensor_list.append(N)

#문자열로 받은 데이터들(fire_list)에서 flex센서 데이터들만 int로 바꿔주기 위한 코드
for a in range(6, 11):
    N = []
    for j in range(len(fire_list)):
        N.append(int(fire_list[a][j]))
    sensor_list.append(N)

# gyro_x 데이터 sensor_list[3]
# 동작 구간만 리스트에 저장.
interval_data = [[],[],[],[],[],[],[],[],[],[],[]]
count = 0
for i in range(len(sensor_list[3])): #section_list의 크기만큼 for문 동작
    if sensor_list[3][i] >= 22.0: #gyro_x가 일정 수치보다 크거나 같으면 카운드 +1
         count += 1
    if count == 1: #count가 1이면 데이터를 g_list에 저장
        for j in range(len(interval_data)):
            interval_data[j].append(sensor_list[j][i])
    elif count == 2: #count가 2면 마지막 데이터 g_list에 넣고 break
        break

#지화 모드 시 final_data에 있는 각각의 센서값들의 평균을 구하는 코드
final_data = [[],[],[],[],[],[],[],[],[],[],[]]
for f in range(6): #각 배열의 0번째 값 삭제(시작 값)
    interval_data[f].pop(0)
    final_data[f].append(round(np.mean(interval_data[f]), 2))

#flex센서들은 평균을 구하고 int로 자료형 변환을 시켜주기
for t in range(6, 11):
    interval_data[t].pop(0)
    final_data[t].append(int(np.mean(interval_data[t])))
print(final_data)

dir = db.reference()
dir.update({'입력된 센싱값 평균': final_data[0] + final_data[1] + final_data[2] + final_data[3] + final_data[4] + final_data[5]
 + final_data[6] + final_data[7] + final_data[8] + final_data[9] + final_data[10]})


#실시간 그래프를 그리는 코드
#def animate(i):
#    plt.cla()
#    plt.plot(f_list, 'g', linewidth = 0.5)
# 
#ani = FuncAnimation(plt.gcf(), animate, interval = 500)
#
#plt.tight_layout()
#plt.show()