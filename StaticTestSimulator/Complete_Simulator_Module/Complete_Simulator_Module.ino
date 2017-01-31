#define TDO 3
#define TCS 4
#define TSCK 5
#define TempPin A5

#define FDO 8
#define FSCK 9
#define ForcePin A4

int tstreamdata[32];
long fstreamdata;

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
  //temperature data simulator pins
  pinMode(TDO, OUTPUT);
  pinMode(TCS, INPUT);
  pinMode(TSCK, INPUT);
  pinMode(TempPin, INPUT);

  //force data simulator pins
  pinMode(FDO, OUTPUT);
  pinMode(FSCK, INPUT);
  Serial.begin(9600);
}

void loop() {
  for(int i = 0; i < 32; i++) //initalizes storage for data to be streamed
  {
    tstreamdata[i] = 0;
  }
  int tempdata = analogRead(TempPin)/8;
  for(int i = 6; i >= 0; i--) //converts analog temperature data into a binary number within the data to be streamed
  {
    if(tempdata%ipow(2,i+1) > 0 && ipow(2,i) <= tempdata)
    {
      tstreamdata[20+i] = 1;
      tempdata = tempdata%ipow(2,i);
    }
    else
    {
      tstreamdata[20+i] = 0;
    }
  }
  //this code bit here makes sense when you look in the library at how the software SPI behaves
  
  
  int t = 31;
  while(digitalRead(TCS) == LOW && t >= 0) //waits for slave select to be low
  {
    delay(1);
    if(digitalRead(TSCK) == LOW) //waits for clock to be low
    {
      digitalWrite(DO, tstreamdata[t]);
      t--;
      delay(1); //these delays ensure the timing of the signals are in sync with the master
      
    }
  }
  //delay(250);
  //Serial.println();
  //Serial.println("New Data");
}
