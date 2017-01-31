#define DO 3
#define SCK 4
#define CS1 5
#define CS2 6
#define CS3 7
#define TempPin1 A5
#define TempPin2 A4
#define TempPin3 A3

int streamdata[32][3];

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
  pinMode(DO, OUTPUT);
  pinMode(CS1, INPUT);
  pinMode(CS2, INPUT);
  pinMode(CS3, INPUT);
  pinMode(SCK, INPUT);
  pinMode(TempPin1, INPUT);
  pinMode(TempPin2, INPUT);
  pinMode(TempPin3, INPUT);
  Serial.begin(9600);
}

void loop() {
  for(int i = 0; i < 3; i++) //initalizes storage for data to be streamed
  {
    for(int j = 0; j < 32; j++)
    {
      streamdata[j][i] = 0;
    }
  }
  int tempdata[3] = {analogRead(TempPin1)/8, analogRead(TempPin2)/8, analogRead(TempPin3)/8};
  for(int j = 0; j < 3; j++)
  {
    for(int i = 6; i >= 0; i--) //converts analog temperature data into a binary number within the data to be streamed
  {
    if(tempdata[j]%ipow(2,i+1) > 0 && ipow(2,i) <= tempdata[j])
    {
      streamdata[20+i][j] = 1;
      tempdata[j] = tempdata[j]%ipow(2,i);
    }
    else
    {
      streamdata[20+i][j] = 0;
    }
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
  int j = 31;
  int k = 31;
  //this code here makes sense when you look in the library at how the software SPI behaves
  while(digitalRead(CS1) == LOW && i >= 0) //waits for slave select to be low
  {
    delay(1);
    if(digitalRead(SCK) == LOW) //waits for clock to be low
    {
      digitalWrite(DO, streamdata[i][0]);
      i--;
      delay(1); //these delays ensure the timing of the signals are in sync with the master
      
    }
  }
  
  while(digitalRead(CS2) == LOW && j >= 0) //waits for slave select to be low
  {
    delay(1);
    if(digitalRead(SCK) == LOW) //waits for clock to be low
    {
      digitalWrite(DO, streamdata[j][1]);
      j--;
      delay(1); //these delays ensure the timing of the signals are in sync with the master
      
    }
  }

  while(digitalRead(CS3) == LOW && k >= 0) //waits for slave select to be low
  {
    delay(1);
    if(digitalRead(SCK) == LOW) //waits for clock to be low
    {
      digitalWrite(DO, streamdata[k][2]);
      k--;
      delay(1); //these delays ensure the timing of the signals are in sync with the master
      
    }
  }
  //delay(250);
  //Serial.println();
  //Serial.println("New Data");
}
