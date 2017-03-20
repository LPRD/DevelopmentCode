#include <SPI.h>
#include "Adafruit_MAX31855.h"

#define MAXDO 24
#define MAXCS 43
#define MAXCLK 22
#define PERIOD 100

Adafruit_MAX31855 thermocouple(MAXCLK, MAXCS, MAXDO);
unsigned long last_run_time = 0;


void setup() {
  while (!Serial); // wait for Serial on Leonardo/Zero, etc
  Serial.begin(9600);
  delay (500); // wait for MAX chip to stabilize 
}

void loop() {
  if (millis () > last_run_time + PERIOD) {
    last_run_time = millis ();
    //error message
    if (isnan(getTemperatureCelsius())) {
      Serial.println ("Something wrong with thermocouple !");
    }
    else {
      Serial.print("C = ");
      double CTemp = getTemperatureCelsius ();
      Serial.println(CTemp); 
    }
  }
}

double getInternalTemperature () {
  return thermocouple.readInternal ();
}

double getTemperatureCelsius () {
  return thermocouple.readCelsius();
}



 

