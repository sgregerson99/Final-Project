#include <DS3231.h>
#include <Wire.h><br>
#include <Stepper.h>
int Photo_Resist_Pin = A0;
int Photo_Resist_Value;
const int stepsPerRevolution = 2048;
Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11);

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}

