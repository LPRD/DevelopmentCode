#define DO 3
#define CS 10
#define SCK 11
#define TempPin A5

int streamdata[32];

int ipow(int base, int ex) // Power function for integers
{
    int base_o = base; // storing original base value
    while(ex > 1) // multiplies base by itself while exponent is greater than one; if exponent equals one the function will return the base
    {
        base *= base_o;
        ex--;
    }
    if(ex == 0) // returns 1 if exponent is zero (x^0 = 1 for all x)
    {
        return 1;
    }
    return base;
}

void setup() {
  // put your setup code here, to run once:
  pinMode(DO, OUTPUT);
  pinMode(CS, INPUT);
  pinMode(SCK, INPUT);
  pinMode(TempPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly
  for(int i = 0; i < 32; i++)
  {
    streamdata[i] = 0;
  }
  int tempdata = analogRead(TempPin)/8;
  for(int i = 6; i >= 0; i--)
  {
    if(tempdata%ipow(2,i+1) > 0 && ipow(2,i) <= tempdata)
    {
      streamdata[20+i] = 1;
      tempdata = tempdata%ipow(2,i);
    }
    else
    {
      streamdata[20+i] = 0;
    }
  }
  /*
  for(int i = 31; i >= 0; i--)
  {
    Serial.print(streamdata[i]);
  }
  Serial.println();
  */
  int i = 31;
  while(digitalRead(CS) == LOW && i >= 0)
  {
    delay(1);
    if(digitalRead(SCK) == LOW)
    {
      digitalWrite(DO, streamdata[i]);
      i--;
      delay(1);
      
    }
  }
  //delay(250);
  //Serial.println();
  //Serial.println("New Data");
}
