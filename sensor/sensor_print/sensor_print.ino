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

  if (y>0 && z >0 && f1 <= 364 && f2 <= 338 && f3 <=245 && f4 <= 463 && f5 <=513){
    Serial.println("ㄱ");
    }
    else if (y < 0 && x < 0.1 && z <0.2 && f1 <= 282 && f2 <= 298 && f3 <=203 && f4 <= 288 && f5 <=381){
    Serial.println("ㅁ");
    }
      
    else if (y < -0.23 && z < -0.23 &&f1 <= 295 && f2 <= 304 && f3 <=198 && f4 <= 273 && f5 <=471){
    Serial.println("ㅎ");
    }
  else if (y<0 && z<-0.08 && f1 <= 357 && f2 <= 328 && f3 <=235 && f4 <= 459 && f5 <=527){
    Serial.println("ㄴ");
    }
  else if (0.3 < x<= 1 && y <= -0.09 && z <= 0.07 &&f1 <= 424 && f2 <= 339 && f3 <=360 && f4 <= 502 && f5 <=427){
    Serial.println("ㄷ");
    }
  else if (x<-0.03&& y<-0.08 && z>0 && f1 <= 313 && f2 <= 291 && f3 <=199 && f4 <= 310 && f5 <=363){
    Serial.println("ㅍ");
    }      

  else if (x<1 && z<0 && y<0 && f1 <= 420 && f2 <= 488 && f3 <=360 && f4 <= 490 && f5 <=427){
    Serial.println("ㄹ");
    }
      
  else if (f1 <= 548 && f2 <= 488 && f3 <=313 && f4 <= 378 && f5 <=483){
    Serial.println("ㅇ");
    }

    
  else if (x<0.12 && y < -0.6 && f1 <= 554 && f2 <= 505 && f3 <=411 && f4 <= 506 && f5 <=429){
    Serial.println("ㅂ");
    }  
  else if (x < 1 && f1 <= 346 && f2 <= 318 && f3 <=396 && f4 <= 464 && f5 <=407){
    Serial.println("ㅅ");
    }

   else if (f1 <= 341 && f2 <= 384 && f3 <=360 && f4 <= 313 && f5 <=517){
    Serial.println("ㅋ");
    }  


  else if (f1 <= 408 && f2 <= 430 && f3 <=398 && f4 <= 465 && f5 <=521){
    Serial.println("ㅈ");
    }  
  else if (f1 <= 463 && f2 <= 481 && f3 <=392 && f4 <= 490 && f5 <=537){
    Serial.println("ㅊ");
    }  

  else if (f1 <= 432 && f2 <= 489 && f3 <=394 && f4 <= 487 && f5 <=456){
    Serial.println("ㅌ");
    }  

  //모음 if 문 
 if (x < 0.51 && y< -0.83 && 0.08<z<0.26 && f1 <= 380 && f2 <= 349 && f3 <=223 && f4 <= 472 && f5 <=462){
    Serial.println("ㅏ");
    } 
  else if (f1 <= 417 && f2 <= 347 && f3 <=391 && f4 <= 481 && f5 <=429){
    Serial.println("ㅑ");
    } 
  else if (x<0.85 && y< -0.56 && z<0.08 &&f1 <= 385 && f2 <= 343 && f3 <=218 && f4 <= 485 && f5 <=447){
    Serial.println("ㅓ");
    }
  else if (f1 <= 412 && f2 <= 346 && f3 <=377 && f4 <= 486 && f5 <=427){
    Serial.println("ㅕ");
    }
  else if (x>0 && y< 0 && z<0 && f1 <= 386 && f2 <= 350 && f3 <=219 && f4 <= 472 && f5 <=452){
    Serial.println("ㅗ");
    }
  else if (f1 <= 409 && f2 <= 355 && f3 <=386 && f4 <= 475 && f5 <=452){
    Serial.println("ㅛ");
    }
  else if (f1 <= 400 && f2 <= 365 && f3 <=237 && f4 <= 474 && f5 <=485){
    Serial.println("ㅜ");
    }
  else if (f1 <= 416 && f2 <= 384 && f3 <=318 && f4 <= 468 && f5 <=454){
    Serial.println("ㅠ");
    }
  else if (f1 <= 412 && f2 <= 372 && f3 <=255 && f4 <= 490 && f5 <=474){
    Serial.println("ㅡ");
    }
  else if (f1 <= 524 && f2 <= 391 && f3 <=237 && f4 <= 296 && f5 <=459){
    Serial.println("ㅣ");
    }
  else if (f1 <= 432 && f2 <= 489 && f3 <=394 && f4 <= 487 && f5 <=456){
    Serial.println("ㅒ");
    }
  else if (f1 <= 533 && f2 <= 367 && f3 <=232 && f4 <= 467 && f5 <=458){
    Serial.println("ㅐ");
    }
  else if (f1 <= 540 && f2 <= 363 && f3 <=228 && f4 <= 473 && f5 <=454){
    Serial.println("ㅔ");
    }
  else if (f1 <= 541 && f2 <= 374 && f3 <=316 && f4 <= 484 && f5 <=448){
    Serial.println("ㅖ");
    }
  else if (f1 <= 536 && f2 <= 344 && f3 <=217 && f4 <= 458 && f5 <=452){
    Serial.println("ㅚ");
    }
  else if (f1 <= 432 && f2 <= 489 && f3 <=394 && f4 <= 487 && f5 <=456){
    Serial.println("ㅙ");
    }
  else if (f1 <= 525 && f2 <= 378 && f3 <=217 && f4 <= 461 && f5 <=456){
    Serial.println("ㅟ");
    }
  else if (f1 <= 432 && f2 <= 489 && f3 <=394 && f4 <= 487 && f5 <=456){
    Serial.println("ㅢ");
    } 

  else {Serial.println("None");}
  

  delay(1000);
}
