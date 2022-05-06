#include <ArduinoBLE.h>
#include <Arduino_LSM6DS3.h>

BLEService sensorService("66df5109-edde-4f8a-a5e1-02e02a69cbd5");
//자이로(각속도)
BLEStringCharacteristic xSensorLevel("741c12b9-e13c-4992-8a5e-fce46dec0bff", BLERead | BLENotify,15);
BLEStringCharacteristic ySensorLevel("baad41b2-f12e-4322-9ba6-22cd9ce09832", BLERead | BLENotify,15);
BLEStringCharacteristic zSensorLevel("5748a25d-1834-4c68-a49b-81bf3aeb2e50", BLERead | BLENotify,15);
//가속도
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
 BLE.addService(sensorService);

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
  axSensorLevel.writeValue(String(ax));
  a_oldXLevel = ax;
   }
  
   if (ay != a_oldYLevel) {
    aySensorLevel.writeValue(String(ay));
    a_oldYLevel = ay;
   }
  
   if (az != a_oldZLevel) {
    azSensorLevel.writeValue(String(az));
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
 
 void loop() {
 BLEDevice central = BLE.central();
 if (central) {
  Serial.print("Connected to central: ");
  Serial.println(central.address());

  while (central.connected()) {
   //long currentMillis = millis();
   updateGyroscopeLevel();
   updateAccelerationLevel();
   delay(300);
  }

  Serial.print("Disconnected from central: ");
  Serial.println(central.address());
 }
}
