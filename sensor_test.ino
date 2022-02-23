#include <Arduino_LSM6DS3.h>

int flexpin_1 = A7; //센서와 연결된 아날로그 핀 설정 A4, A5는 안됨.
int flexpin_2 = A3;
int flexpin_3 = A2;
int flexpin_4 = A1;
int flexpin_5 = A0;

void setup() {
  Serial.begin(9600); // 시리얼 통신 속도를 9600로 설정.
  while (!Serial);

  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");

    while (1);
  }
  Serial.print("Accelerometer sample rate = ");
  Serial.print(IMU.accelerationSampleRate());
  Serial.print("Gyroscope sample rate = ");
  Serial.print(IMU.gyroscopeSampleRate());
  Serial.println(" Hz");
  Serial.println();
  Serial.println("Acceleration in G's");
  Serial.println("X\tY\tZ");
  Serial.println("Gyroscope in degrees/second");
  Serial.println("X\tY\tZ");
}

void loop() {
  float x, y, z;
  float gx, gy,gz;
    
  int flexVal_1;  //센서값을 저장할 변수 설정
  int flexVal_2; 
  int flexVal_3;
  int flexVal_4;
  int flexVal_5;
    

  IMU.readAcceleration(x, y, z);

  Serial.print(x);
  Serial.print('\t');
  Serial.print(y);
  Serial.print('\t');
  Serial.println(z);


  IMU.readGyroscope(gx, gy,gz);

  Serial.print(gx);
  Serial.print('\t');
  Serial.print(gy);
  Serial.print('\t');
  Serial.println(gz);


  flexVal_1 = analogRead(flexpin_1);    // 센서로 부터 보내오는 값을 입력 받는다.(0-1023)
  Serial.print("sensor_1: ");
  Serial.println(flexVal_1);  // sensor:0000로 출력한다(0000값은 센서로 부터 읽어 온 값)

  flexVal_2 = analogRead(flexpin_2);
  Serial.print("sensor_2: ");
  Serial.println(flexVal_2); 

  flexVal_3 = analogRead(flexpin_3);
  Serial.print("sensor_3: ");
  Serial.println(flexVal_3); 

  flexVal_4 = analogRead(flexpin_4);
  Serial.print("sensor_4: ");
  Serial.println(flexVal_4); 

  flexVal_5 = analogRead(flexpin_5);
  Serial.print("sensor_5: ");
  Serial.println(flexVal_5); 

  Serial.println();
  delay(1000);
}
