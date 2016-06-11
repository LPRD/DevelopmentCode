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
float vel = 10.1;           // m/s
// new variables after this point

float roll = gyro_y;        // assumed axis of rotation (from last flight)
float rollTarget = 0;       // desired angular rotation
float rollTol = 0.00;
float rollProp;
float rollInt;
float rollDer;
float Kp = 200;
float Ki = 6000;
float Kd = -0.12;

// sample data
float gyro_10= .010;
float gyro_9 = .010;
float gyro_8 = -.030;
float gyro_7 = -.030;
float gyro_6 = -.030;
float gyro_5 = .000;
float gyro_4 = .000;
float gyro_3 = .050;
float gyro_2 = .050;
float gyro_1 = .050;
float gyro_0 = .000;
float dataTime = .001;      // time between data (assuming interrupts)

// Offsets to make servos align vertically at exactly v=90
int servo1Offset = 8;
int servo2Offset = 8;
int v = 90;
int vMax = 12;              // max angular deflection (avoids stall)


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
  // Proportional
  //roll = gyro_y;
  roll = (gyro_1 + gyro_2)/2;   // averaging helpful for instantaneous errors
  rollProp = roll - rollTarget;

  // Integrated
  rollInt = (gyro_1+gyro_2+gyro_3+gyro_4+gyro_5 - rollTarget*5) * dataTime*5;

  // Derivative
  rollDer = (gyro_1 - gyro_3)/(dataTime*3);  // just enough to average instantaneous errors
  
  if (abs(rollProp)>=rollTol) {
        v = 90 + Kp*rollProp + Ki*rollInt + Kd*rollDer;
        
        if (v>90+vMax) {
            v = 90 + vMax;
        }
        else if (v<90-vMax) {
            v = 90 - vMax;
        }
        servo1.write(v + servo1Offset);
        servo2.write(v + servo2Offset);
        

        Serial.print  ("  90");
        Serial.print  ("  +  ");
        Serial.print  (Kp*rollProp);
        Serial.print  ("  +  ");
        Serial.print  (Ki*rollInt);
        Serial.print  ("  +  ");
        Serial.print  (Kd*rollDer);
        Serial.print  ("  =  ");
        Serial.println(v);
  }

  // simulates changing gyro data - cycles through positions
  gyro_0  = gyro_10;    // temporary storage variable
  gyro_10 = gyro_9;
  gyro_9 = gyro_8;
  gyro_8 = gyro_7;
  gyro_7 = gyro_6;
  gyro_6 = gyro_5;
  gyro_5 = gyro_4;
  gyro_4 = gyro_3;
  gyro_3 = gyro_2;
  gyro_2 = gyro_1;
  gyro_1 = gyro_0;
  delay(300);

  
  delay(20);           // simulates time spent running other code
}
