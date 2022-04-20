void setup() // 1. 
{ 

  pinMode(8, OUTPUT); 
// 2. 8번 핀을 출력으로 설정합니다. 
} 

void loop() // 3. 
{ 
  digitalWrite(8, HIGH); // 4. HIGH: 전압이 5V(아두이노 보드 전압)로 설정됩니다. 
  delay(1000); // 5. 1000ms동안 대기합니다. 1000ms=1초 
  //digitalWrite(8, LOW); // 6. LOW: 전압이 0V로 설정됩니다. 
  delay(1000); }
