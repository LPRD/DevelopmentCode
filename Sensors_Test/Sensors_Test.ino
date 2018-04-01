#include <SPI.h>
#include <Wire.h>
#include <HX711.h>
#include <Adafruit_MAX31855.h>
#include <Adafruit_MMA8451.h>
#include <Adafruit_Sensor.h>
#include <Telemetry.h>
#include <avr/pgmspace.h>

// LEDs
#define THERMO1_LED 28
#define THERMO2_LED 30
#define THERMO3_LED 32
#define FORCE_LED 42
#define PRESSURE1_LED 44
#define PRESSURE2_LED 50
#define TEMP1_LED 46
#define TEMP2_LED 48
//#define STATE_LED 38
//#define STATUS_LED 40

//Thermocouples
#define MAXCS1 22
#define MAXCS2 33
#define MAXCS3 31
#define MAXDO 24
#define MAXCLK 52

//Calibration Factors
#define PRESSURE_CALIBRATION_FACTOR 246.58
#define PRESSURE_OFFSET 118.33
#define LOAD_CELL_CALIBRATION_FACTOR 20400.0

//Load Cell
#define FORCE_DAT 2
#define FORCE_CLK 26

//Pressure
#define PRESSURE_1 A2
#define PRESSURE_2 A3

//Analog Temp
#define TEMP_1 A4
#define TEMP_2 A5

float chamber_temp_1, chamber_temp_2, chamber_temp_3, pressure_1, pressure_2, force, temp_1, temp_2;
unsigned long int last_run_time = 0;
#define PERIOD 1000


Adafruit_MMA8451  mma = Adafruit_MMA8451();
Adafruit_MAX31855 chamber_thermocouple_1(MAXCLK, MAXCS1, MAXDO);
Adafruit_MAX31855 chamber_thermocouple_2(MAXCLK, MAXCS2, MAXDO);
Adafruit_MAX31855 chamber_thermocouple_3(MAXCLK, MAXCS3, MAXDO);
HX711 scale(FORCE_DAT, FORCE_CLK);

void setup () {

  //Pin Setup
  pinMode (THERMO1_LED, OUTPUT);
  pinMode (THERMO2_LED, OUTPUT);
  pinMode (THERMO3_LED, OUTPUT);
  pinMode (FORCE_LED, OUTPUT);
  pinMode (PRESSURE1_LED, OUTPUT);
  pinMode (PRESSURE2_LED, OUTPUT);
  pinMode (TEMP1_LED, OUTPUT);
  pinMode (TEMP2_LED, OUTPUT);

  pinMode (PRESSURE_1, INPUT);
  pinMode (PRESSURE_2, INPUT);
  pinMode (TEMP_1, INPUT);
  pinMode (TEMP_2, INPUT);

  while (!Serial);
  Serial.begin(115200);
  Serial.println(F("Initializing..."));

  delay(500);

  //LEDs
  digitalWrite(PRESSURE1_LED, HIGH);
  digitalWrite(PRESSURE2_LED, HIGH);

  //Load Cell
  scale.set_scale(LOAD_CELL_CALIBRATION_FACTOR);
  digitalWrite(FORCE_LED, HIGH);

  //Accelerometer Initialization
  Wire.begin();
  if (!mma.begin())
    Serial.println(F("Accelerometer error"));
  else {
    mma.setRange(MMA8451_RANGE_2_G);  // set acc range (2 5 8)
    Serial.print(F("Accelerometer range "));
    Serial.print(2 << mma.getRange());
    Serial.println("G");
  }
  delay(100);

  //Thermo 1 setup
  float result = chamber_thermocouple_1.readCelsius();
  if (isnan(result) || result == 0) {
    Serial.print("Chamber Thermocouple 1");
    Serial.println(F(" temp sensor error"));
  }
  else {
    Serial.print("Chamber Thermocouple 1");
    Serial.println(F(" temp sensor connected"));
    digitalWrite(THERMO1_LED, HIGH);
  }
  delay(100);

  //Thermo 2 setup
  result = chamber_thermocouple_2.readCelsius();
  if (isnan(result) || result == 0) {
    Serial.print("Chamber Thermocouple 2");
    Serial.println(F(" temp sensor error"));
  }
  else {
    Serial.print("Chamber Thermocouple 2");
    Serial.println(F(" temp sensor connected"));
    digitalWrite(THERMO2_LED, HIGH);
  }
  delay(100);

  //Thermo 3 setup
  result = chamber_thermocouple_3.readCelsius();
  if (isnan(result) || result == 0) {
    Serial.print("Chamber Thermocouple 3");
    Serial.println(F(" temp sensor error"));
  }
  else {
    Serial.print("Chamber Thermocouple 3");
    Serial.println(F(" temp sensor connected"));
    digitalWrite(THERMO3_LED, HIGH);
  }
  delay(100);

  //Temp setup
  digitalWrite (TEMP_1, HIGH);
  digitalWrite (TEMP_2, HIGH);
}

void loop (){

  if (millis() > last_run_time + PERIOD)
  {
    last_run_time = millis ();
    //Force Data
    force = scale.get_units();

    //Temp Data
    temp_1 = (analogRead(TEMP_1) * 5.0 / 1024.0 - 0.5) * 100 ;
    temp_2 = (analogRead(TEMP_2) * 5.0 / 1024.0 - 0.5) * 100 ;

    //Thermo Data
    chamber_temp_1 = chamber_thermocouple_1.readCelsius ();
    chamber_temp_2 = chamber_thermocouple_2.readCelsius ();
    chamber_temp_3 = chamber_thermocouple_3.readCelsius ();

    //Pressure data
    pressure_1 = (analogRead(PRESSURE_1) * 5 / 1024.0) * PRESSURE_CALIBRATION_FACTOR - (PRESSURE_OFFSET); // Pressure is measured in PSIG
    pressure_2 = (analogRead(PRESSURE_2) * 5 / 1024.0) * PRESSURE_CALIBRATION_FACTOR - (PRESSURE_OFFSET); // Pressure is measured in PSIG

    mma.read();
    Serial.print("X:\t"); Serial.print(mma.x);
    Serial.print("\tY:\t"); Serial.print(mma.y);
    Serial.print("\tZ:\t"); Serial.print(mma.z);
    Serial.println();

    /* Get a new sensor event */
    sensors_event_t event;
    mma.getEvent(&event);

    /* Display the results (acceleration is measured in m/s^2) */
    Serial.print("X: \t"); Serial.print(event.acceleration.x); Serial.print("\t");
    Serial.print("Y: \t"); Serial.print(event.acceleration.y); Serial.print("\t");
    Serial.print("Z: \t"); Serial.print(event.acceleration.z); Serial.print("\t");
    Serial.println("m/s^2 ");

    /* Get the orientation of the sensor */
    uint8_t o = mma.getOrientation();

    switch (o) {
      case MMA8451_PL_PUF:
        Serial.println("Portrait Up Front");
        break;
      case MMA8451_PL_PUB:
        Serial.println("Portrait Up Back");
        break;
      case MMA8451_PL_PDF:
        Serial.println("Portrait Down Front");
        break;
      case MMA8451_PL_PDB:
        Serial.println("Portrait Down Back");
        break;
      case MMA8451_PL_LRF:
        Serial.println("Landscape Right Front");
        break;
      case MMA8451_PL_LRB:
        Serial.println("Landscape Right Back");
        break;
      case MMA8451_PL_LLF:
        Serial.println("Landscape Left Front");
        break;
      case MMA8451_PL_LLB:
        Serial.println("Landscape Left Back");
        break;
    }
    Serial.println();

    Serial.print ("Chamber Temp 1 = ");
    Serial.print (chamber_temp_1);
    Serial.println (" C");

    Serial.print ("Chamber Temp 2 = ");
    Serial.print (chamber_temp_2);
    Serial.println (" C");

    Serial.print ("Chamber Temp 3 = ");
    Serial.print (chamber_temp_3);
    Serial.println (" C");

    Serial.print ("Force = ");
    Serial.print (force);
    Serial.println (" lbs");

    Serial.print ("Temp 1 = ");
    Serial.print (temp_1);
    Serial.println (" C");

    Serial.print ("Temp 2 = ");
    Serial.print (temp_2);
    Serial.println (" C");

    Serial.print ("Pressure 1 = ");
    Serial.print (pressure_1);
    Serial.println (" PSIG");

    Serial.print ("Pressure 2 = ");
    Serial.print (pressure_2);
    Serial.println (" PSIG");
  }
}

