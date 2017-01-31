#define DO 8
#define SCK 9

int data = 500;

void setup(){
  pinMode(DO, OUTPUT);
  pinMode(SCK, INPUT);
}

void loop(){
  digitalWrite(DO, HIGH);
  delay(250);
  digitalWrite(DO, LOW);
  delay(8);
  shiftOut(DO, SCK, MSBFIRST, (data << 8));
  delay(1);
  shiftOut(DO, SCK, MSBFIRST, data);
}
