#include <RS485.h>
#include <SoftwareSerial.h>
#include "HX711.h"

#define calibration_factor 20400.0

/*
Software Serial on D2 (RX) and D3(TX)
*/


#define DOUT 6
#define CLK 5
#define RTS 4
#define LED_PIN 10

#define RECEIVE LOW
#define DRIVER HIGH

HX711 scale (DOUT,CLK);

char Message[maxMsgLen + 1] ;
int text;

void setup()
{
  pinMode(RTS, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT)
  digitalWrite (RTS, RECEIVE);
  digitalWrite (LED_PIN, LOW);
   
  Serial.begin(9600);
  while(!Serial);
  
  scale.set_scale(calibration_factor);
  scale.tare();
  
  RS485_Begin(115200);
}

void loop()
{
  int STATE = digitalRead (RTS);
  delay (1000); //Delay 1 ms for debouncing
  
  if (STATE == DRIVER) {
    Serial.println("Transmitter");
    float force = scale.get_units();
    if (RS485_SendMessage(Message, fWrite, ENABLE_PIN)) // Send data to PC
    {
      Serial.print("Sending-");
      Serial.print("Force:");
      Serial.print(force);
      Serial.print(" N");
      Serial.println();
    }
  }
  
  else if (STATE == RECEIVE)
  {  
    Serial.println("Receiver");
    text = Serial.read();
    for(int i=0;i<3;i++)
    {
      if ('H' == text ){
        digitalWrite(LED_PIN, HIGH);
        Serial.println("led HIGH");
        delay(1000);
      }
      else if ('L' == text )
      {
        digitalWrite(LED_PIN, LOW);
        Serial.println("led LOW ");
        delay(1000);
      }
    }
  }
}

