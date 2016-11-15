#include <Telemetry.h>

//Define the period of data collection here
#define PERIOD 1000

//Define Analog Pins used
int pressurePinIn = 0;
int pressurePinOut = 1;
int potPin = 2;
unsigned long int last_run_time = 0;

void setup() 
{
  Serial.begin (9600);
  pinMode (potPin, INPUT);
  pinMode (pressurePinIn, INPUT);
  pinMode (pressurePinOut, INPUT) ;
}

void loop() 
{
  if (millis() > last_run_time + PERIOD) 
  {
    last_run_time = millis ();
    double pressureDrop = getPressure(pressurePinIn) - getPressure(pressurePinOut);
    double angle = getAngle(potPin);

    BEGIN_SEND
    SEND_ITEM(pressure, pressureDrop)
    SEND_ITEM(angle, angle);
    END_SEND
  }
}

int getDAC (int potPin) 
{
  int DAC = analogRead (potPin); 
  return DAC;
}

double getVout (int pin)
{
 double Vout = getDAC(pin) * 5 / 1024. ;
 return Vout;
}

double getAngle (int potPin)
{
  double angle = fabs(getVout(potPin) * 180 / 3.13 - 157.25);
  return angle; 
}


double getPressure (int pressurePin) 
{
    double PSIG = getVout(pressurePin) * 251.28 - 106.14;
    return PSIG;
} 
