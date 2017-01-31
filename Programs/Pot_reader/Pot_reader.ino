#include <LiquidCrystal.h>

int opotpin = A0;
int kpotpin = A1;
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
double oLastMeasure = 0.00;
double kLastMeasure = 0.00;
float trm = 0.1;

void setup()
{
    lcd.begin(16, 2);
    pinMode(opotpin, INPUT); 
    pinMode(kpotpin, INPUT);
    Serial.begin(9600);
    lcd.setCursor(0, 0);
    double odegrees = (analogRead(opotpin)/1023.0 * 270);
    double kdegrees = (analogRead(kpotpin)/1023.0 * 270);
    lcd.print("O Deg: ");
    lcd.print(odegrees);
    lcd.setCursor(0, 1); //set cursor to 2nd row
    lcd.print("K Deg: ");
    lcd.print(kdegrees);
} 

void loop()
{
      double odegrees = (analogRead(opotpin)/1023.0 * 270);
      double kdegrees = (analogRead(kpotpin)/1023.0 * 270);
      if(odegrees - oLastMeasure > trm || odegrees - oLastMeasure < -trm)
      {
        lcd.setCursor(0, 0);
        lcd.print("O Deg: ");
        lcd.print(odegrees);
      }
      if(kdegrees - kLastMeasure > trm || kdegrees - kLastMeasure < -trm)
      {
        lcd.setCursor(0, 1); //set cursor to 2nd row
        lcd.print("K Deg: ");
        lcd.print(kdegrees);
      }
      
      oLastMeasure = odegrees;
      kLastMeasure = kdegrees;
}

