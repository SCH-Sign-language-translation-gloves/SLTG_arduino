#include <ArduinoBLE.h>
#include <Arduino_LSM6DS3.h>

BLEService sensorService("66df5109-edde-4f8a-a5e1-02e02a69cbd5");
BLEStringCharacteristic xSensorLevel("741c12b9-e13c-4992-8a5e-fce46dec0bff", BLERead | BLENotify,15);
BLEStringCharacteristic ySensorLevel("baad41b2-f12e-4322-9ba6-22cd9ce09832", BLERead | BLENotify,15);
BLEStringCharacteristic zSensorLevel("5748a25d-1834-4c68-a49b-81bf3aeb2e50", BLERead | BLENotify,15);

// last sensor data
float oldXLevel = 0;
float oldYLevel = 0;
float oldZLevel = 0;
long previousMillis = 0;


void setup() {
 Serial.begin(9600);
 
 while (!Serial);
 
 if (!IMU.begin()) {
  Serial.println("Failed to initialize IMU!");
  while (1);
 }
 
 pinMode(LED_BUILTIN, OUTPUT);
 
 if (!BLE.begin()) {
  Serial.println("starting BLE failed!");
  while (1);
 }

 BLE.setLocalName("Demo Gyroscope");
 BLE.setAdvertisedService(sensorService);
 sensorService.addCharacteristic(xSensorLevel);
 sensorService.addCharacteristic(ySensorLevel);
 sensorService.addCharacteristic(zSensorLevel);
 BLE.addService(sensorService);

 BLE.advertise();
 Serial.println("Bluetooth device active, waiting for connections...");
}

void loop() {
 BLEDevice central = BLE.central();
 if (central) {
  Serial.print("Connected to central: ");
  Serial.println(central.address());
  digitalWrite(LED_BUILTIN, HIGH);

  while (central.connected()) {
   //long currentMillis = millis();
   updateGyroscopeLevel();
   delay(300);
  }

  digitalWrite(LED_BUILTIN, LOW);
  Serial.print("Disconnected from central: ");
  Serial.println(central.address());
 }
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
