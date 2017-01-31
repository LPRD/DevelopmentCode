/*Relay Testing Arduino Code for test stand. Written before spring
break 2016. JWCS*/

//Ports
const int oxSafeP=         13;   //oxidizer safety port
const int fuelSafeP=       12;   //fuel safety port
const int oxRedP=          11;   //oxidzer open port
const int fuelRedP=        10;   //fuel open port
const int oxWhiteP=         9;   //oxidizer closed port
const int fuelWhiteP=       8;   //fuel close port

//Buttons
  //const int safeB=            A0;  //safety button-Actually doesn't exist 
  const int oxSafeB=          A1;  //oxidizer safety port
  const int fuelSafeB=        A2;  //fuel safety port
  const int oxOpenB=           7;  //oxidzer open port
  const int fuelOpenB=         6;  //fuel open port
  const int oxCloseB=          5;  //oxidizer closed port
  const int fuelCloseB=        4;  //fuel close port

// States: Assuming that the buttons read true when pressed/current flows
bool safeOn =     true;    // safety button on-temporary fix
bool oxSafeOn =   false;    // oxidizer safety button on
bool fuelSafeOn = false;    // fuel safety button on
bool oxDel =      false;    // oxidizer state changing (delta)
bool fuelDel =    false;    // fuel state changing (delta)
bool oxClose =    true;     // oxidizer state closing or opening
bool fuelClose =  true;     // fuel state closing or opening

void setup() {
  pinMode(oxSafeP, OUTPUT);
  pinMode(fuelSafeP, OUTPUT);
  pinMode(oxRedP, OUTPUT);
  pinMode(fuelRedP, OUTPUT);
  pinMode(oxWhiteP, OUTPUT);
  pinMode(fuelWhiteP, OUTPUT);
  //pinMode(safeB, INPUT);
  pinMode(oxSafeB, INPUT);
  pinMode(fuelSafeB, INPUT);
  pinMode(oxOpenB, INPUT);
  pinMode(fuelOpenB, INPUT);
  pinMode(oxCloseB, INPUT);
  pinMode(fuelCloseB, INPUT);
}

void loop() {
  stateUpdate();
  if (!safeOn) {
    digitalWrite(oxSafeP, LOW);
    digitalWrite(fuelSafeP, LOW);
  } else {
    normalOperation();
  }
}

stateUpdate() {
  safeOn  =    true;//digitalRead(safeB); // If button not pressed, safety off
  oxSafeOn =   digitalRead(oxSafeB); // Ibid
  fuelSafeOn = digitalRead(fuelSafeB);// Ibid
  oxDel =      digitalRead(oxOnB) || digitalRead(oxCloseB);// If either is triggered
  fuelDel =    digitalRead(fuelOnB) || digitalRead(fuelCloseB); // Ibid
  oxClose =    oxDel && digitalRead(oxCloseB); // If changing, and not closing, open
  fuelClose =  fuelDel && digitalRead(fuelCloseB);// Ibid
}

normalOperation(){
  if (!oxSafeOn) {                                    // Not Safe? Close everything
    digitalWrite(oxSafeP, LOW); // Low closes
    digitalWrite(oxRedP, LOW); // It won't open
    digitalWrite(oxWhiteP, HIGH); // It will close
  } else if (!oxDel) {                                 // Not changing? Don't close/open
    digitalWrite(oxSafeP, HIGH); // High allows flow
    digitalWrite(oxRedP, LOW); // It won't open
    digitalWrite(oxWhiteP, LOW); //It won't close
  } else if (oxClose) {                                // Now it's closing
    digitalWrite(oxSafeP, HIGH); //High allows flow
    digitalWrite(oxRedP, LOW); //It won't open
    digitalWrite(oxWhiteP, HIGH); //It will close
  } else {                                            // Now it's opening
    digitalWrite(oxSafeP, HIGH); // High allows flow
    digitalWrite(oxRedP, HIGH); // It will open
    digitalWrite(oxWhiteP, LOW); // It won't close
  }
  if (!fuelSafeOn) {                                    // Not Safe? Close everything
    digitalWrite(fuelSafeP, LOW); // Low closes
    digitalWrite(fuelRedP, LOW); // It won't open
    digitalWrite(fuelWhiteP, HIGH); // It will close
  } else if (!fuelDel) {                                 // Not changing? Don't close/open
    digitalWrite(fuelSafeP, HIGH);// High allows flow
    digitalWrite(fuelRedP, LOW);// It won't open
    digitalWrite(fuelWhiteP, LOW);// It won't close
  } else if (fuelClose) {                                // Now it's closing
    digitalWrite(fuelSafeP, HIGH);// High allows flow
    digitalWrite(fuelRedP, LOW);// It won't open
    digitalWrite(fuelWhiteP, HIGH);// It will close
  } else {                                            // Now it's opening
    digitalWrite(fuelSafeP, HIGH); // High allows flow
    digitalWrite(fuelRedP, HIGH); // It will open
    digitalWrite(fuelWhiteP, LOW); // It won't close
  }
}
