#include <Telemetry.h>

//Define the period of data collection here
#define PERIOD 10
//#define DEBUG

//#define FUEL

//Define Analog Pins used
int pressurePinIn = 4;
int pressurePinOut = 5;
int potPinOxydizer = 1;
int potPinFuel = 0;
unsigned long int last_run_time = 0;

void setup() 
{
  Serial.begin (115200);
  pinMode (potPinOxydizer, INPUT);
  pinMode (potPinFuel, INPUT);
  pinMode (pressurePinIn, INPUT);
  pinMode (pressurePinOut, INPUT) ;
}

void loop() 
{
  if (millis() > last_run_time + PERIOD) 
  {
    last_run_time = millis ();
    
#ifdef DEBUG
   Serial.println (analogRead (pressurePinIn) * 5 /1024.);
   Serial.println (analogRead (pressurePinOut) * 5 /1024.);

#else
    double pressureIn = getPressure(pressurePinIn);
    double pressureOut = getPressure(pressurePinOut);
    double pressureDrop = pressureIn - pressureOut;
    
#ifdef FUEL
    int angleFuel = getAngleFuel(potPinFuel);
#else
    int angleOxydizer = getAngleOxydizer (potPinOxydizer);
#endif
    
    BEGIN_SEND
    SEND_ITEM(pressure_in,pressureIn);
    SEND_ITEM(pressure_out,pressureOut);
    SEND_ITEM(pressure_drop,pressureDrop);
    
#ifdef FUEL
    SEND_ITEM(angle, angleFuel);
#else
    SEND_ITEM(angle, angleOxydizer);
#endif

    END_SEND
#endif
  }
}

double getPressure (int pin) 
{
    double PSIG = (analogRead (pin)* 5/ 1024.) * 246.58 - 118.33;
    return PSIG;
} 

double getAngleOxydizer (int pin)
{
  double angle = fabs((analogRead(pin) * 5 /1024. ) * 180 / 3.13 - 154.25);
  return angle; 
}

double getAngleFuel (int pin)
{
  double angle = fabs((analogRead(pin) * 5 /1024. ) * 180 / 3.13 - 249.25);
  return angle; 
}


