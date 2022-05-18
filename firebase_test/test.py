import firebase_admin
from firebase_admin import credentials
from firebase_admin import db
from matplotlib import pyplot as plt

#Firebase database 인증 및 앱 초기화
cred = credentials.Certificate('./arduino-app-b69fd-firebase-adminsdk-11dwf-c09ef584f0.json')
firebase_admin.initialize_app(cred,{
    'databaseURL' : 'https://arduino-app-b69fd-default-rtdb.firebaseio.com/'
})

while(1):
    accel_x = db.reference('senser_data').child('accel x').get()
    accel_y = db.reference('senser_data').child('accel y').get()
    accel_z = db.reference('senser_data').child('accel z').get()

    flex_1 = db.reference('senser_data').child('flex 1').get()
    flex_2 = db.reference('senser_data').child('flex 2').get()
    flex_3 = db.reference('senser_data').child('flex 3').get()
    flex_4 = db.reference('senser_data').child('flex 4').get()
    flex_5 = db.reference('senser_data').child('flex 5').get()

    zyro_x = db.reference('senser_data').child('zyro x').get()
    zyro_y = db.reference('senser_data').child('zyro y').get()
    zyro_z = db.reference('senser_data').child('zyro z').get()

    if float(zyro_x) >= 450.0:
        print('YEAH')

    else:
        print('SSIBAL')