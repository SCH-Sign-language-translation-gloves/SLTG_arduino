#include <Arduino_LSM6DS3.h>

int flexpin_1 = A7; //센서와 연결된 아날로그 핀 설정
int flexpin_2 = A3;
int flexpin_3 = A2;
int flexpin_4 = A1;
int flexpin_5 = A0;

void setup() {
  Serial.begin(9600); // 시리얼 통신 속도를 9600로 설정.
  
  while (!Serial);
  pinMode(LED_BUILTIN, OUTPUT);
  
  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }
}

void loop() {
  float x, y, z;
  float gx, gy,gz;
  IMU.readAcceleration(x, y, z);
  IMU.readGyroscope(gx,gy,gz);  
 
  int f1 = analogRead(flexpin_1);  //센서값을 저장할 변수 설정
  int f2 = analogRead(flexpin_2); 
  int f3 = analogRead(flexpin_3);
  int f4 = analogRead(flexpin_4);
  int f5 = analogRead(flexpin_5);

  if (y>0 && z >0 && f1 <= 270 && f2 <= 300 && f3 <=270 && f4 <= 473 && f5 <=426){
    Serial.println("ㄱ");
    }
  else if(y<-0.3 && z < 0.3 && f1 <= 200 && f2 <= 255 && f3 <= 220 && f4 <= 313 && f5 <= 469){
   Serial.println("ㅎ");
  }
  else if(y<0 && z <0.2 && f1 <= 270 && f2 <= 300 && f3 <=270 && f4 <= 483 && f5 <=440){
    Serial.println("ㄴ");
    }
  else if(y<0 && z <0.2 && f1 <= 300 && f2 <= 350 && f3 <=445 && f4 <= 484 && f5 <=370){
    Serial.println("ㄷ");
    }
  else if(y<0 && z <0.3 && f1 <= 280 && f2 <= 470 && f3 <=470 && f4 <= 470 && f5 <=370){
    Serial.println("ㄹ");
    }

    else if(f1 <= 220 && f2 <= 240 && f3 <= 200 && f4 <= 296 && f5 <= 280){
   Serial.println("ㅍ");
  }
  else if(y<0 && z <0.8 && f1 <= 280 && f2 <= 300 && f3 <=230 && f4 <= 355 && f5 <=340){
    Serial.println("ㅁ");
    }

  else if(f1 <= 455 && f2 <= 500 && f3 <=445 && f4 > 380 && f5 <=300){
    Serial.println("ㅂ");
  }
  else if(x<0.4 && y<1 && z<1 && f1 <= 330 && f2 <= 350 && f3 <= 430 && f4 <= 455 && f5 <= 350){
   Serial.println("ㅅ");
  }
    else if(x < 0 && f1 <= 480 && f2 <= 460 && f3 <= 400 && f4 <= 370 && f5 <= 340){
   Serial.println("ㅇ");
    }
  else if(f1 <= 300 && f2 <= 370 && f3 <= 440 && f4 <= 488 && f5 <= 440){
   Serial.println("ㅈ");
  }
  else if(f1 <= 300 && f2 <= 470 && f3 <= 440 && f4 <= 488 && f5 <= 440){
   Serial.println("ㅊ");
  }
  else if(f1 <= 322 && f2 <= 397 && f3 <= 450 && f4 <= 360 && f5 <= 450){
   Serial.println("ㅋ");
  }
  else if(y<-0.2 && z < 0.5 && f1 <= 340 && f2 <= 487 && f3 <= 444 && f4 <= 490 && f5 <= 345){
   Serial.println("ㅌ");
  }
    else if(f1 <= 230 && f2 <= 290 && f3 <= 225 && f4 <= 313 && f5 <= 469){
   Serial.println("ㅎ");
  }
  
  else{
    Serial.println("None");
  }
    Serial.print(f1);
  Serial.print('\t');
  Serial.print(f2);
  Serial.print('\t');
  Serial.print(f3);
  Serial.print('\t');
  Serial.print(f4);
  Serial.print('\t');
  Serial.println(f5);
  delay(300);