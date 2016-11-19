#include <Telemetry.h>

//Define the period of data collection here
#define PERIOD 10
#define DEBUG

//Define Analog Pins used
int pressurePinIn = 0;
int pressurePinOut = 1;
int potPin = 2;
unsigned long int last_run_time = 0;

void setup() 
{
  Serial.begin (115200);
  pinMode (potPin, INPUT);
  pinMode (pressurePinIn, INPUT);
  pinMode (pressurePinOut, INPUT) ;
}

void loop() 
{
  if (millis() > last_run_time + PERIOD) 
  {
    last_run_time = millis ();
    
#ifdef DEBUG
    Serial.println (getVout(pressurePinIn));
    //Serial.println (getPressure(pressurePinIn ));
    Serial.println (getVout(pressurePinOut));
    //Serial.println (getPressure(pressurePinOut));
#endif

    double pressureIn = getPressure(pressurePinIn);
    double pressureOut = getPressure(pressurePinOut);
    double pressureDrop = pressureIn - pressureOut;
    double angle = getAngle(potPin);

    BEGIN_SEND
    SEND_ITEM(pressure_in,pressureIn);
    SEND_ITEM(pressure_out,pressureOut);
    SEND_ITEM(pressure_drop, pressureDrop);
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
    double PSIG = getVout(pressurePin) * 246.58 - 118.33;
    return PSIG;
} 
