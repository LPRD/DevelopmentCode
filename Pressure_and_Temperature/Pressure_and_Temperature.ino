#include <SPI.h>
#include "Adafruit_MAX31855.h"

#define PRESSURE_PIN 0
#define MAXDO 3
#define MAXCS 4 
#define MAXCLK 5
#define PERIOD 100

Adafruit_MAX31855 thermocouple(MAXCLK, MAXCS, MAXDO);
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
  Serial.print ("PSIG = ");
  Serial.println (getPressure(analogRead(PRESSURE_PIN)));
  //error message
  if (isnan(getTemperatureCelsius()))
  {
    Serial.println ("Something wrong with thermocouple !");
  }
  else 
  {
    Serial.print("C = ");
    double CTemp = getTemperatureCelsius ();
    Serial.println(CTemp); 
    Serial.print ("F = ");
    Serial.println (CTemp * 1.8 + 32);    
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
  return thermocouple.readInternal ();
}

double getTemperatureCelsius () 
{
  return thermocouple.readCelsius();
}



 

