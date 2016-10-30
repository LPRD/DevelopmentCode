//Define the period of data collection here
#define PERIOD 1000

//Define Analog Pin used
int potPin = 1;
unsigned long int last_run_time = 0;
void setup() 
{
  Serial.begin (9600);
  pinMode (potPin, OUTPUT);

}

void loop() 
{
  if (millis() > last_run_time + PERIOD) 
  {
  last_run_time = millis ();
  Serial.print ("Vout: ");
  Serial.println (getVout(potPin));
  Serial.print ("Angle (Degrees): ");
  Serial.println (getAngle(potPin));
  }
}

int getDAC (int potPin) 
{
  int DAC = analogRead (potPin); 
  return DAC;
}

double getVout (int potPin)
{
 double Vout = getDAC(potPin) * 5 / 1024. ;
 return Vout;
}

double getAngle (int potPin)
{
  double angle = getVout(potPin) * 180 / 3.13;
  return angle; 
}
