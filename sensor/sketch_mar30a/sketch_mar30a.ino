#include <SoftwareSerial.h>

int RX=3;
int TX=2;
SoftwareSerial bluetooth(RX, TX);
 
void setup(){
  Serial.begin(9600);
  bluetooth.begin(9600);
}
 
void loop(){
  if (bluetooth.available()) {
    Serial.write(bluetooth.read());
  }
  if (Serial.available()) {
    bluetooth.write(Serial.read());
  }
}
