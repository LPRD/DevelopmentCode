#include <SPI.h>
#include "Adafruit_MAX31855.h"
#include "HX711.h"

#define PRESSURE_PIN 0
#define MAXDO 3
#define MAXCS 4 
#define MAXCLK 5
#define PERIOD 100
#define calibration_factor 20400.0 //This value is obtained using the SparkFun_HX711_Calibration sketch
#define DOUT  6
#define CLK  7

Adafruit_MAX31855 thermocouple(MAXCLK, MAXCS, MAXDO);
HX711 scale(DOUT, CLK);
unsigned long last_run_time = 0;


void setup() 
{
  while (!Serial); // wait for Serial on Leonardo/Zero, etc
  Serial.begin(9600);
   scale.set_scale(calibration_factor); //This value is obtained by using the SparkFun_HX711_Calibration sketch
  scale.tare();  //Assuming there is no weight on the scale at start up, reset the scale to 0
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
  Serial.print("Force Reading: ");
  Serial.print(scale.get_units(), 1); //scale.get_units() returns a float
  Serial.println(" lbs"); //You can change this to kg but you'll need to refactor the calibration_factor
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



 

