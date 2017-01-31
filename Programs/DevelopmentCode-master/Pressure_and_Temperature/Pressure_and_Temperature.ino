#include <SPI.h>
#include "Adafruit_MAX31855.h"

#define PRESSURE_PIN 0
#define MAXDO 3
#define MAXCLK 4
#define MAXCS1 5 
#define MAXCS2 6
#define MAXCS3 7 
#define PERIOD 100

Adafruit_MAX31855 thermocouple_1(MAXCLK, MAXCS1, MAXDO);
Adafruit_MAX31855 thermocouple_2(MAXCLK, MAXCS2, MAXDO);
Adafruit_MAX31855 thermocouple_3(MAXCLK, MAXCS3, MAXDO);
unsigned long last_run_time = 0;


void setup() 
{
  while (!Serial); // wait for Serial on Leonardo/Zero, etc
  Serial.begin(9600);
  pinMode (PRESSURE_PIN, INPUT);
  delay (500); // wait for MAX chip to stabilize 
}

void loop() 
{
  if (millis () > last_run_time + PERIOD) 
  {
    last_run_time = millis ();
    /*Serial.print ("PSIG = ");
    Serial.println (getPressure(analogRead(PRESSURE_PIN)));
    //error message
    */
    if (isnan(getTemperature_1_Celsius()) || isnan(getTemperature_2_Celsius()) || isnan(getTemperature_3_Celsius()))
    {
      Serial.println ("Something wrong with thermocouple !");
    }
    else 
    {
      double CTemp = getTemperature_1_Celsius();
      Serial.print("C_1= ");
      Serial.println(CTemp); 
      CTemp = getTemperature_2_Celsius();
      Serial.print("C_2= ");
      Serial.println(CTemp); 
      CTemp = getTemperature_3_Celsius();
      Serial.print("C_3= ");
      Serial.println(CTemp); 
      //Serial.print ("F = ");
      //Serial.println (CTemp * 1.8 + 32);    
    }
  }
}

double getPressure (double reading) 
{
  double PSIG = getVDC(reading) * 246.58 - 118.33;
  return PSIG;
}

double getVDC (double reading) 
{
  double VDC = reading *5 / 1024;
  return VDC;  
}

double getInternalTemperature () 
{
  return thermocouple_1.readInternal();
}

double getTemperature_1_Celsius() 
{
  return thermocouple_1.readCelsius();
}

double getTemperature_2_Celsius() 
{
  return thermocouple_2.readCelsius();
}

double getTemperature_3_Celsius() 
{
  return thermocouple_3.readCelsius();
}



 

