#include <Arduino.h>

#define DO 8
#define SCK 9

byte data[2];

void setup(){
  Serial.begin(9600);
  pinMode(DO, INPUT);
  pinMode(SCK, OUTPUT);
}

void loop(){
  while(!is_ready())  {}
  delay(8);
  data[1] = shiftIn(DO, SCK, MSBFIRST);
  delay(1);
  data[0] = shiftIn(DO, SCK, MSBFIRST);
  Serial.println(data[1]);
  Serial.println(data[0]);
  
}

bool is_ready() {
  return digitalRead(DO) == LOW;
}
