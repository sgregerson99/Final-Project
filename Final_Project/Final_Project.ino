#include <DS3231.h>
#include <Servo.h> //Include servo library
Servo myservo
#include <Stepper.h>
int Photo_Resist_Pin = A0;
int Photo_Resist_Value;
const int stepsPerRevolution = 2048;
Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11);

void setup() {
  myStepper.setSpeed(15);
  pinMode(Photo_Resist_Pin, INPUT);
  Serial.begin(9600);
  myservo.attach(9);
  // put your setup code here, to run once:

}

void loop() {
  Photo_Resist_Value = analogRead(Photo_Resist_Pin);
  Serial.println(Photo_Resist_Value);
  delay(30);
  if (Photo_Resist_Value > 500) {
    Serial.println("clockwise");
  myStepper.step(stepsPerRevolution); 
  delay(500);

  // step one revolution in the other direction:
  Serial.println("counterclockwise");
  myStepper.step(-stepsPerRevolution);
  delay(500);
   // Serial.println("No pill detected");
    
    
  }
  if (digitalRead(buttonPin) == LOW){
    servoangle = 180;
    myservo.write(servoangle);
    digitalWrite(mp3_1, LOW);
    delay(20);
  }
  // put your main code here, to run repeatedly:

}


