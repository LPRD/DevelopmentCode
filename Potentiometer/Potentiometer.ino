//Define the period of data collection here
#define PERIOD 1000

//Define Analog Pins used
int pressurePinKerosene = 0;
int pressurePinOxygen = 1;
int potPin = 2;
unsigned long int last_run_time = 0;
void setup() 
{
  Serial.begin (9600);
  pinMode (potPin, INPUT);
  pinMode (pressurePinOxygen, INPUT);
  pinMode (pressurePinKerosene, INPUT) ;
}

void loop() 
{
  if (millis() > last_run_time + PERIOD) 
  {
  last_run_time = millis ();
  Serial.print ("Pressure Kerosene ");
  Serial.println (getPressure (pressurePinKerosene));
  Serial.print ("Pressure Oxygen ");
  Serial.println (getPressure (pressurePinOxygen));
  Serial.print ("Angle (Degrees): ");
  Serial.println (getAngle(potPin));
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
  double angle = getVout(potPin) * 180 / 3.13;
  return angle; 
}


double getPressure (int pressurePin) 
{
    double PSIG = getVout(pressurePin) * 246.58 - 118.33;
    return PSIG;
} 
