#include <ArduinoBLE.h>
#include <Arduino_LSM6DS3.h>

BLEService sensorService("66df5109-edde-4f8a-a5e1-02e02a69cbd5");
BLEStringCharacteristic xSensorLevel("741c12b9-e13c-4992-8a5e-fce46dec0bff", BLERead | BLENotify,15);
BLEStringCharacteristic ySensorLevel("baad41b2-f12e-4322-9ba6-22cd9ce09832", BLERead | BLENotify,15);
BLEStringCharacteristic zSensorLevel("5748a25d-1834-4c68-a49b-81bf3aeb2e50", BLERead | BLENotify,15);
BLEStringCharacteristic axSensorLevel("3aae57bc-efe5-4a17-8f24-f610b1b985e5", BLERead | BLENotify,15);
BLEStringCharacteristic aySensorLevel("7ad8f8f6-2da4-45a1-adbd-ab5a83351426", BLERead | BLENotify,15);
BLEStringCharacteristic azSensorLevel("7cac39b1-89e0-47be-aaf4-30277f05d763", BLERead | BLENotify,15);

// last sensor data
float oldXLevel = 0;
float oldYLevel = 0;
float oldZLevel = 0;

float a_oldXLevel = 0;
float a_oldYLevel = 0;
float a_oldZLevel = 0;

long previousMillis = 0;
const int ledPin = LED_BUILTIN;

int flexpin_1 = A7; //센서와 연결된 아날로그 핀 설정
int flexpin_2 = A3;
int flexpin_3 = A2;
int flexpin_4 = A1;
int flexpin_5 = A0;

void setup() {
  //Serial.begin(9600); // 시리얼 통신 속도를 9600로 설정.
  Serial.begin(115200);
  while (!Serial);
  pinMode(LED_BUILTIN, OUTPUT);
  
  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }
   // begin initialization
   if (!BLE.begin()) {
    Serial.println("starting BLE failed!");
    while (1);
  }

 BLE.setLocalName("SLTG_BLE_test");
 BLE.setAdvertisedService(sensorService);
 sensorService.addCharacteristic(xSensorLevel);
 sensorService.addCharacteristic(ySensorLevel);
 sensorService.addCharacteristic(zSensorLevel);
 sensorService.addCharacteristic(axSensorLevel);
 sensorService.addCharacteristic(aySensorLevel);
 sensorService.addCharacteristic(azSensorLevel);
 
 BLE.addService(sensorService);
 xSensorLevel.writeValue(String(0));
 ySensorLevel.writeValue(String(0));
 zSensorLevel.writeValue(String(0));
 axSensorLevel.writeValue(String(0));
 aySensorLevel.writeValue(String(0));
 azSensorLevel.writeValue(String(0));
 BLE.advertise();
 Serial.println("Bluetooth device active, waiting for connections...");
}

void updateGyroscopeLevel() {
 float x, y, z;
 
 if (IMU.gyroscopeAvailable()) {
  IMU.readGyroscope(x, y, z);

   if (x != oldXLevel) {
  xSensorLevel.writeValue(String(x));
  oldXLevel = x;
   }
  
   if (y != oldYLevel) {
    ySensorLevel.writeValue(String(y));
    oldYLevel = y;
   }
  
   if (z != oldZLevel) {
    zSensorLevel.writeValue(String(z));
    oldZLevel = z;
   }
  
   Serial.print(x);
   Serial.print('\t');
   Serial.print(y);
   Serial.print('\t');
   Serial.println(z);
   }
}

void updateAccelerationLevel() {
 float x, y, z;
 
 if (IMU.accelerationAvailable()) {
  IMU.readAcceleration(x, y, z);

   if (x != a_oldXLevel) {
  axSensorLevel.writeValue(String(x));
  a_oldXLevel = x;
   }
  
   if (y != a_oldYLevel) {
    aySensorLevel.writeValue(String(y));
    a_oldYLevel = y;
   }
  
   if (z != a_oldZLevel) {
    azSensorLevel.writeValue(String(z));
    a_oldZLevel = z;
   }
  
   Serial.print(x);
   Serial.print('\t');
   Serial.print(y);
   Serial.print('\t');
   Serial.println(z);
   }
}

void loop() {
  float x, y, z;
  float gx, gy,gz;
  IMU.readAcceleration(x, y, z);
  IMU.readGyroscope(gx,gy,gz);  
  
  
  BLEDevice central = BLE.central();
  if (central) {
    Serial.print("Connected to central: ");
    Serial.println(central.address());
    digitalWrite(LED_BUILTIN, HIGH);
    
  while (central.connected()) {
     updateGyroscopeLevel();
     updateAccelerationLevel();
     delay(300);
   }
  digitalWrite(LED_BUILTIN, LOW);
  Serial.print("Disconnected from central: ");
  Serial.println(central.address());
  }
}
