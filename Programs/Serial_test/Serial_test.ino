int temp_0_pin = A0, temp_1_pin = A1;
int total_0 = 0, total_1 = 0, c = 0;

void setup() 
{
  Serial.begin(9600); // opens serial port, sets data rate to 9600 bps
  pinMode(temp_0_pin, INPUT);
  pinMode(temp_1_pin, INPUT);
}

void loop() 
{
  int t_0 = analogRead(temp_0_pin);
  int t_1 = analogRead(temp_1_pin);
  Serial.print("Temp 1: ");
  Serial.println(t_0);
  Serial.print("Temp 2: ");
  Serial.println(t_1);
  c = c+1;
  total_0 = total_0 + t_0;
  total_1 = total_1 + t_1;
  int ave_0 = total_0/c;
  int ave_1 = total_1/c;
  Serial.print("Ave 1: ");
  Serial.println(ave_0);
  Serial.print("Ave 2: ");
  Serial.println(ave_1);
}
