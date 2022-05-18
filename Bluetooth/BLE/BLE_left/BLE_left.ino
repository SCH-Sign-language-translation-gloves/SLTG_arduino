#include <ArduinoBLE.h>
#include <Arduino_LSM6DS3.h>

BLEService sensorService("354e8943-6cb2-4620-83f7-0b848eeaa76d");
//자이로(각속도)
BLEStringCharacteristic xSensorLevel("120d8460-76cc-4ad1-b3d7-ebdbf681ca38", BLERead | BLENotify,15);
BLEStringCharacteristic ySensorLevel("9dc7f95f-ec49-47c5-ad76-36af6293a5e4", BLERead | BLENotify,15);
BLEStringCharacteristic zSensorLevel("cef9bf69-6af9-43c9-a3b8-941881518666", BLERead | BLENotify,15);
//가속도
BLEStringCharacteristic axSensorLevel("86fef35c-b14a-4705-a901-3153c8f029b9", BLERead | BLENotify,15);
BLEStringCharacteristic aySensorLevel("99a8424c-0c9b-45c3-a702-c2c08012f762", BLERead | BLENotify,15);
BLEStringCharacteristic azSensorLevel("e0684334-3382-467c-bc3f-26ee1ee0b624", BLERead | BLENotify,15);
//Flex
BLEStringCharacteristic flex1Sensor("3627b31e-fd54-4fe5-8059-fb723ccfa54c", BLERead | BLENotify,15);
BLEStringCharacteristic flex2Sensor("ba63eb9d-129d-4024-9607-8108fdd9299b", BLERead | BLENotify,15);
BLEStringCharacteristic flex3Sensor("ab4a7f9e-00b4-4454-a22e-732236b2c1e1", BLERead | BLENotify,15);
BLEStringCharacteristic flex4Sensor("48ea1dcb-e94c-4158-89a1-c4a4d7265a4c", BLERead | BLENotify,15);
BLEStringCharacteristic flex5Sensor("368e79cc-5280-41dd-a0a4-575cc5385703", BLERead | BLENotify,15);

//flex sensor pin
int flexpin_5 = A7;
int flexpin_4 = A3;
int flexpin_3 = A2;
int flexpin_2 = A1;
int flexpin_1 = A0;

// last sensor data
float oldXLevel = 0;
float oldYLevel = 0;
float oldZLevel = 0;

float a_oldXLevel = 0;
float a_oldYLevel = 0;
float a_oldZLevel = 0;

int old_flex1 = 0;
int old_flex2 = 0;
int old_flex3 = 0;
int old_flex4 = 0;
int old_flex5 = 0;

long previousMillis = 0;

void setup() {
 Serial.begin(9600);
 
 while (!Serial);
 
 if (!IMU.begin()) {
  Serial.println("Failed to initialize IMU!");
  while (1);
 }
 
 if (!BLE.begin()) {
  Serial.println("starting BLE failed!");
  while (1);
 }

 BLE.setLocalName("Demo Gyroscope");
 BLE.setAdvertisedService(sensorService);
 sensorService.addCharacteristic(xSensorLevel);
 sensorService.addCharacteristic(ySensorLevel);
 sensorService.addCharacteristic(zSensorLevel);
 sensorService.addCharacteristic(axSensorLevel);
 sensorService.addCharacteristic(aySensorLevel);
 sensorService.addCharacteristic(azSensorLevel);
 sensorService.addCharacteristic(flex1Sensor);
 sensorService.addCharacteristic(flex2Sensor);
 sensorService.addCharacteristic(flex3Sensor);
 sensorService.addCharacteristic(flex4Sensor);
 sensorService.addCharacteristic(flex5Sensor);
 BLE.addService(sensorService);

 BLE.advertise();
 Serial.println("Bluetooth device active, waiting for connections...");
}

void updateGyroscopeLevel() {
 float x, y, z, ax, ay, az;
 
 if (IMU.gyroscopeAvailable() & IMU.accelerationAvailable()) {
  IMU.readGyroscope(x, y, z); // Gyro
  IMU.readAcceleration(ax, ay, az); // Acceleration
  int flex1 = analogRead(flexpin_1);  //센서값을 저장할 변수 설정
  int flex2 = analogRead(flexpin_2); 
  int flex3 = analogRead(flexpin_3);
  int flex4 = analogRead(flexpin_4);
  int flex5 = analogRead(flexpin_5);

 xSensorLevel.writeValue(String(x)+"\t"+String(y)+"\t"+String(z)+"\t"+String(ax)+"\t"+String(ay)+"\t"+String(az)+"\t"+String(flex1)+'\t'+String(flex2)+'\t'+String(flex3)+'\t'+String(flex4)+'\t'+String(flex5));

  if (x != oldXLevel) {
   oldXLevel = x;
  }
 if (y != oldYLevel) {
  oldYLevel = y;
 }
 if (z != oldZLevel) {
  oldZLevel = z;
  }
 Serial.print("Gyro :");
 Serial.print(x);
 Serial.print('\t');
 Serial.print(y);
 Serial.print('\t');
 Serial.println(z);
 }
}
 
 void updateAccelerationLevel() {
 float ax, ay, az;
 
 if (IMU.accelerationAvailable()) {
  IMU.readAcceleration(ax, ay, az);

   if (ax != a_oldXLevel) {
  a_oldXLevel = ax;
   }
  
   if (ay != a_oldYLevel) {
    a_oldYLevel = ay;
   }
  
   if (az != a_oldZLevel) {
    a_oldZLevel = az;
   }
  Serial.print("Acceleration :");
  Serial.print(ax);
  Serial.print('\t');
  Serial.print(ay);
  Serial.print('\t');
  Serial.println(az);
  }
 }
 void updateflexsensor(){
  int flex1 = analogRead(flexpin_1);  //센서값을 저장할 변수 설정
  int flex2 = analogRead(flexpin_2); 
  int flex3 = analogRead(flexpin_3);
  int flex4 = analogRead(flexpin_4);
  int flex5 = analogRead(flexpin_5);
  
  if (flex1 != old_flex1) {
  old_flex1 = flex1;
   }
  
  if (flex2 != old_flex2) {
  old_flex2 = flex2;
   }
  
  if (flex3 != old_flex3) {
  old_flex3 = flex3;
   }
   
  if (flex4 != old_flex4) {
  old_flex4 = flex4;
   }
   
  if (flex5 != old_flex5) {
  old_flex5 = flex5;
   }
  
  Serial.print("flex :");
  Serial.print(flex1);
  Serial.print('\t');
  Serial.print(flex2);
  Serial.print('\t');
  Serial.print(flex3);
  Serial.print('\t');
  Serial.print(flex4);
  Serial.print('\t');
  Serial.println(flex5);
  
 }
 
 void loop() {
 BLEDevice central = BLE.central();
 if (central) {
  Serial.print("Connected to central: ");
  Serial.println(central.address());

  while (central.connected()) {
   //long currentMillis = millis();
   updateGyroscopeLevel();
   updateAccelerationLevel();
   updateflexsensor();
   delay(300);
  }

  Serial.print("Disconnected from central: ");
  Serial.println(central.address());
 }
}
