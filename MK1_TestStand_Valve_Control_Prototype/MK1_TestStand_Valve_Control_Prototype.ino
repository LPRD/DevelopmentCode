/* This program is designed to automatically operate the MK1 Test Stand Control Valves.
 */

 // 564 = kClosed
 // 194 = kOpen

#define oControlOpenRelay 31 // define open and close relays
#define oControlCloseRelay 30
#define kControlOpenRelay 46
#define kControlCloseRelay 47

#define oSafetySwitch 48 // define safety switches
#define kSafetySwitch 49

#define kPOT A2 // define Oxygen and Kerosene valve Potentiometers
#define oPOT A3

#define openButton 34 // define buttons to operate system
#define closeButton 36

#define ANGLE_CALIBRATION_FACTOR 57.5
#define ANGLE_OFFSET_OXYDIZER 154.25
#define ANGLE_OFFSET_FUEL 249.25

int openButtonState = 0;
int closeButtonState = 0;

void openValvesTo(double kSet, double oSet)
{
  bool kOpen = false; // state of valves
  bool oOpen = false;
  
    while(!kOpen || !oOpen)
   // while(!kOpen)
  {
   double kValue = analogRead(kPOT); // read in the POT values as this loops
   double oValue = analogRead(oPOT);

   double kDegrees = ((((analogRead(kPOT) * 5 /1024. ) * ANGLE_CALIBRATION_FACTOR - ANGLE_OFFSET_FUEL)) * -1) - 90;
   double oDegrees = ((((analogRead(oPOT) * 5 /1024. ) * ANGLE_CALIBRATION_FACTOR - ANGLE_OFFSET_OXYDIZER)) * -1) + 90;

   //double kVoltage = (float)kValue * 5.0 / 1023;
   //double kDegrees = (kVoltage * 370) / 5.0;


    //Serial.println(kDegrees);
    Serial.println(oDegrees);

    if(abs(kDegrees - kSet)/kSet >= 0.02 && !kOpen) // check to see if the current value of kValve is less than the set value
    {
      digitalWrite(kControlOpenRelay, HIGH);
      digitalWrite(kControlCloseRelay, HIGH);
      //Serial.println(kValue);
      //Serial.println("Opening K Valve");
    } /* else if(kValue > kSet)
    {
      digitalWrite(kControlOpenRelay, HIGH);
      digitalWrite(kControlCloseRelay, HIGH);
    } */ else
    {
      digitalWrite(kControlOpenRelay, LOW);
      digitalWrite(kControlCloseRelay, LOW);
      //Serial.println("K Valve OPEN");
      kOpen = true;
    }

    if(abs(oDegrees - oSet)/oSet >= 0.02 && !oOpen) // check to see if the current value of oValve is less than the set value
    {
      digitalWrite(oControlOpenRelay, HIGH);
      digitalWrite(oControlCloseRelay, HIGH);
      //Serial.println(oValue);

      //Serial.println("Opening O Valve");
    } /* else if(oValue > oSet)
    {
      digitalWrite(oControlOpenRelay, HIGH);
      digitalWrite(oControlCloseRelay, HIGH);
    } */ else
    {
      digitalWrite(oControlOpenRelay, LOW);
      digitalWrite(oControlCloseRelay, LOW);
      //Serial.println("O Valve OPEN");
      oOpen = true;
    }
  }

  digitalWrite(kControlOpenRelay, LOW);
  digitalWrite(kControlCloseRelay, LOW);
  digitalWrite(oControlOpenRelay, LOW);
  digitalWrite(oControlCloseRelay, LOW);
}

void closeValves()
{
  bool kClosed = false; // state of valves
  bool oClosed = false;

  double kValue = 0;
  double oValue = 0;

  while(!kClosed || !oClosed)
  //while(!kClosed)
  {
    
    kValue = analogRead(kPOT); // read in POT values of the valves
    oValue = analogRead(oPOT);

    double kDegrees = ((((analogRead(kPOT) * 5 /1024. ) * ANGLE_CALIBRATION_FACTOR - ANGLE_OFFSET_FUEL)) * -1) - 90;
    double oDegrees = ((((analogRead(oPOT) * 5 /1024. ) * ANGLE_CALIBRATION_FACTOR - ANGLE_OFFSET_OXYDIZER)) * -1) + 90;



    if(kValue < 564)
    //if(abs(kDegrees - 0)/0 >= 0.02)
    {
      digitalWrite(kControlOpenRelay, HIGH);
      digitalWrite(kControlCloseRelay, LOW);
      //Serial.println("Closing K Valve");
    } else
    {
      digitalWrite(kControlOpenRelay, LOW);
      digitalWrite(kControlCloseRelay, LOW);
      //Serial.println("K Valve CLOSED");
      kClosed = true;
    }

    if(oValue < 920)
    //if(abs(kDegrees - (-15))/(-15) >= 0.02)
    {
      digitalWrite(oControlOpenRelay, HIGH);
      digitalWrite(oControlCloseRelay, LOW);
      Serial.println(oValue);
      //Serial.println("Closing O Valve");
    } else
    {
      digitalWrite(oControlOpenRelay, LOW);
      digitalWrite(oControlCloseRelay, LOW);
      //Serial.println("O Valve CLOSED");
      oClosed = true;
    }

    
  }

  digitalWrite(kControlOpenRelay, LOW);
  digitalWrite(kControlCloseRelay, LOW);
  digitalWrite(oControlOpenRelay, LOW);
  digitalWrite(oControlCloseRelay, LOW);
}

void setup() {

  digitalWrite(kControlOpenRelay, LOW);
  digitalWrite(kControlCloseRelay, LOW);
  digitalWrite(oControlOpenRelay, LOW);
  digitalWrite(oControlCloseRelay, LOW);

  digitalWrite(oSafetySwitch, LOW);
  digitalWrite(kSafetySwitch, LOW);

  pinMode(kControlOpenRelay, OUTPUT);
  pinMode(kControlCloseRelay, OUTPUT);
  pinMode(oControlOpenRelay, OUTPUT);
  pinMode(oControlCloseRelay, OUTPUT);

  pinMode(oSafetySwitch, OUTPUT);
  pinMode(kSafetySwitch, OUTPUT);

  pinMode(openButton, INPUT);
  pinMode(closeButton, INPUT);

  Serial.begin(9600); // Serial used for debug
  

}

void loop() {

  bool isOpen = false; // state of valves

  openButtonState = digitalRead(openButton); //read the button states during loop
  closeButtonState = digitalRead(closeButton);



  if(openButtonState == HIGH)
  {
    openValvesTo(90, 45); // k and o valve set positions
    isOpen = true;
  }

  if(closeButtonState == HIGH)
  {
    closeValves();
    isOpen = false;
  }

  

}
