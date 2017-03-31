#include <Telemetry.h>

//Define the period of data collection here
#define PERIOD 10
//#define DEBUG

#define PRESSURE_CALIBRATION_FACTOR 246.58
#define ANGLE_CALIBRATION_FACTOR 57.5
#define PRESSURE_OFFSET 118.33
#define ANGLE_OFFSET_OXYDIZER 154.25
#define ANGLE_OFFSET_FUEL 249.25

//Define Analog Pins used
int pressurePinIn = 5;
int pressurePinOut = 4;
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
    
    int angleFuel = getAngleFuel(potPinFuel);
    int angleOxydizer = getAngleOxydizer (potPinOxydizer);
    
    BEGIN_SEND
    SEND_ITEM(pressure_in,pressureIn);
    SEND_ITEM(pressure_out,pressureOut);
    SEND_ITEM(pressure_drop,pressureDrop);
    
    SEND_ITEM(fuel_angle, angleFuel);
    SEND_ITEM(oxygen_angle, angleOxydizer);

    END_SEND
#endif
  }
}

double getPressure (int pin) 
{
    double PSIG = (analogRead (pin)* 5/ 1024.) * PRESSURE_CALIBRATION_FACTOR - PRESSURE_OFFSET;
    return PSIG;
} 

double getAngleOxydizer (int pin)
{
  double angle = fabs((analogRead(pin) * 5 /1024. ) * ANGLE_CALIBRATION_FACTOR - ANGLE_OFFSET_OXYDIZER);
  return angle; 
}

double getAngleFuel (int pin)
{
  double angle = fabs((analogRead(pin) * 5 /1024. ) * ANGLE_CALIBRATION_FACTOR - ANGLE_OFFSET_FUEL);
  return angle; 
}


