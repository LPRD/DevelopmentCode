#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
  
Adafruit_BNO055 bno = Adafruit_BNO055(55);

void setup(void) 
{
  Serial.begin(9600);
  Serial.println("Sensor Test: Angular Velocity"); Serial.println("");
  
  /* Initialise the sensor */
  if(!bno.begin())
  {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }
  
  delay(1000);
}

float gyro[100];
int i=0;
long time0 = millis();
long timestep;

void loop(void) 
{
  i++;
  imu::Vector<3> gyroscope = bno.getVector(Adafruit_BNO055::VECTOR_GYROSCOPE);
  gyro[i] = gyroscope.x();      //may need to change x (to y or z) dep. on orientation
  
  /*
  Serial.print("X:  ");
  Serial.print(gyro[i]);
  Serial.println("");
  */
  
  /*
  Serial.print("\tY:  ");
  Serial.print(gyro(3));
  Serial.print("\tZ:  ");
  Serial.print(gyro(4));
  Serial.println("");
  */
  delay(2);
    if (i>=99){
      int s;
        for (s=1;s<=100;s++) {
          Serial.print("gyro [");
          Serial.print(s);
          Serial.print("]  =  ");
          Serial.println(gyro[s]);
          delay(200);
        }
        delay(10000);
      i = 0;
      //Serial.print("           i = ");
      //Serial.println(i);

      timestep = millis() - time0;
      Serial.print("timestep =  ");
      Serial.println(timestep);
      delay(1000);
      time0 = millis();
    }
}
