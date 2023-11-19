#include <DS3231.h>
#include <Servo.h> //Include servo library
#include "Stepper.h"
Servo myservo;
int Photo_Resist_Pin = A0;
const int buttonPin = 7;
int Photo_Resist_Value;
const int stepsPerRevolution = 2048;
Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11);
bool previousState = 1;
bool currentState = 1;
bool toggle = 0;
int LED = 12;
int mp3_1 = 4;
int mp3_2 = 5;

void setup() {
  myStepper.setSpeed(15);
  pinMode(Photo_Resist_Pin, INPUT);
  Serial.begin(9600);
  myservo.attach(3);
  pinMode(mp3_1, OUTPUT);
  pinMode(mp3_2, OUTPUT);
  pinMode(LED, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  // put your setup code here, to run once:

}

void loop() {
  digitalWrite(LED, HIGH);
  if (pressed() == true) {
   toggle = !toggle;
 }
  Photo_Resist_Value = analogRead(Photo_Resist_Pin);
  Serial.println(Photo_Resist_Value);
  delay(30);
  if (Photo_Resist_Value > 500) {
  myStepper.step(stepsPerRevolution); 
  delay(500);

  // step one revolution in the other direction:
  myStepper.step(-stepsPerRevolution);
  delay(500);
   // Serial.println("No pill detected");
    
    
  }
  if (toggle == 1){
    int servoangle = 180;
    myservo.write(servoangle);
    digitalWrite(mp3_1, LOW);
    delay(20);
  }
  else {
    digitalWrite(mp3_2, LOW);
  }

  

}

bool pressed() {
     previousState = currentState;
    currentState = digitalRead(buttonPin);
  // read the state of the pushbutton value:
    if (currentState == LOW && previousState == HIGH) {
      delay(10);
      return true;
  } else {
      return false;
  }
}
