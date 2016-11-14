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
  Serial.print ("Pressure Drop: ");
  Serial.println (getPressure(pressurePinIn) - getPressure(pressurePinOut));
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
    double PSIG = getVout(pressurePin) * 251.28 - 106.14;
    return PSIG;
} 
