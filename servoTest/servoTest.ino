#include<Servo.h>
Servo servo1;
Servo servo2;

// Remove these for use in code where the variables already exist
float x =  0.06;            // accelerometer
float y = -0.97;
float z =  0.04;
float gyro_x = 0.001;       // gyroscope
float gyro_y = 0.060;
float gyro_z = 0.001;
float moi = 0.0075;         // kg*m^2
float vel = 10.1;           // m/s
// new variables after this point

int numFins=2;
float finArea = .0096;      // m^2
float I = 0.0075;           // kg*m^2


float roll = gyro_y;        // assumed axis of rotation (from last flight)
float rollTarget = 0;       // desired angular rotation
float rollTol = 0.00;
float rollDif;
float Kp = 800;
float Ki = 0;
float Kd = 0;
float gyro_inc=-.002;

//Offsets to make servos align vertically at exactly v=90
int servo1Offset = 8;
int servo2Offset = 8;
int v = 90;
int vMax=30;


void setup() {
  pinMode(1,OUTPUT);
  servo1.attach(9);         // analog pin 0
  servo2.attach(10);
  Serial.begin(19200);
  Serial.println("  Ready");
  servo1.write(v + servo1Offset);
  servo2.write(v + servo2Offset);
  delay(1000);              // remove for final use
}


void loop() {
  roll = gyro_y;
  rollDif = roll - rollTarget;
  
  if (abs(rollDif)>rollTol) {
        v=90 + Kp*rollDif;
        if (v>90+vMax) {
            v=90+vMax;
        }
        else if (v<90-vMax) {
            v=90-vMax;
          }
        servo1.write(v + servo1Offset);
        servo2.write(v + servo2Offset);
  }
  
  // simulates effect of stabilizing
  if (gyro_y+gyro_inc < -.06  ||  gyro_y+gyro_inc > .06) {
    gyro_inc=-gyro_inc;
  }
  else {
    gyro_y = gyro_y + gyro_inc;
  }
  
  delay(20);           // simulate time spent running other code
}
