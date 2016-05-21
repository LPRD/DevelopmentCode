#include<Servo.h>
Servo servo1;
Servo servo2;

//Offsets to make servos align vertically at exactly v=90
//servo2 uses half its range of motion with same input as servo1
int servo1Offset=8;
int servo2Offset=94;
int v=90;
int increment=10;


void setup() {
  pinMode(1,OUTPUT);
  servo1.attach(9);         //analog pin 0
  servo2.attach(10);
  Serial.begin(19200);
  Serial.println("  Ready");
}

void loop() {

  if ( Serial.available()) {
    char ch = Serial.read();

    switch(ch) {
      case '0'...'9':
        v = (ch - '0') * 20;
        servo1.write(v + servo1Offset);
        servo2.write((v-90)/2 + servo2Offset);
        break;
      case 's':
        v = v-increment;
        if (v<0)
          {
            v=0;
          }
        servo1.write(v + servo1Offset);
        servo2.write((v-90)/2 + servo2Offset);
        break;
      case 'w':
        v = v+increment;
        if (v>180)
          {
            v=180;
          }
        servo1.write(v + servo1Offset);
        servo2.write((v-90)/2 + servo2Offset);
        break;
    }
  }

}
