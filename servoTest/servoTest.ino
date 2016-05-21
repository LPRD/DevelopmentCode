#include<Servo.h>
Servo servo1;
Servo servo2;

//Add back in limits to servo angle before use
//Remove these for use in code where the variables already exist
float x =  0.06;            //accelerometer
float y = -0.97;
float z =  0.04;
float gyro_x = 0.001;       //gyroscope
float gyro_y = 0.060;
float gyro_z = 0.001;
//new variables after this point

float roll = gyro_y;        //assumed axis of rotation (from last flight)
float rollTarget = 0;       //desired angular rotation
float rollTol = 0.02;

//Offsets to make servos align vertically at exactly v=90
//servo2 uses half its range of motion with same input as servo1
int servo1Offset =  8;
int servo2Offset = 94;
int v = 90;
int increment = 2;

long time1;
long time2=millis();
long loopTime;


void setup() {
  pinMode(1,OUTPUT);
  servo1.attach(9);         //analog pin 0
  servo2.attach(10);
  Serial.begin(19200);
  Serial.println("  Ready");
  servo1.write(v + servo1Offset);
  servo2.write((v-90)/2 + servo2Offset);
  delay(1000);
}

void loop() {  
                //  time1 = millis();
                //  if ( Serial.available() ) {
                //    char ch = Serial.read();
  roll = gyro_y;
  if (roll>rollTarget+rollTol) {
        v = v-increment;    //servo rotates CW
        if (v<0) {
          v=0;
        }
 //       Serial.println(  v);
        servo1.write(v + servo1Offset);
        servo2.write((v-90)/2 + servo2Offset);
  }
  if (roll<rollTarget-rollTol) {
        v = v+increment;    //servo rotates CCW
        if (v>180) {
          v=180;
        }
  //      Serial.println(  v);
        servo1.write(v + servo1Offset);
        servo2.write((v-90)/2 + servo2Offset);
  }
                //  time2 = millis();
                //  loopTime = time2 - time1;
                //  Serial.println(      loopTime);
  delay(200);           //to simulate time spent running other code
  
}
