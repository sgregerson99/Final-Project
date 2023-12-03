#include <Servo.h> //Include servo library
#include <RTClib.h>
#include <Wire.h>
#include "Stepper.h"
#include <IRremote.h>
RTC_DS3231 rtc;
char t[32];
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
int servoangle = 180;
int servohome = 0;
bool pill = 0;
int buzzer = 2;
const byte IR_RECEIVE_PIN = 7;
int ir_command;

void setup() {
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
  Wire.begin();
  rtc.begin();
  rtc.adjust(DateTime(F(__DATE__),F(__TIME__)));
  pinMode(buzzer, OUTPUT);
  myStepper.setSpeed(15);
  pinMode(Photo_Resist_Pin, INPUT);
  Serial.begin(9600);
  myservo.attach(3);
  pinMode(mp3_1, OUTPUT);
  pinMode(mp3_2, OUTPUT);
  pinMode(LED, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  myservo.write(servohome);
  // put your setup code here, to run once:

}

void loop() {
  if (IrReceiver.decode()) // Only perform an action if an IR signal is read by the reciever from the remote
   {\
      ir_command = IrReceiver.decodedIRData.command;   // Decode IR remote button press signal data
      Serial.println(ir_command);
  digitalWrite(mp3_1, HIGH);
  digitalWrite(mp3_2, HIGH);
  DateTime now = rtc.now();
  sprintf(t, "%02d:%02d:%02d %02d/%02d/%02d", now.hour(), now.minute(), now.second(), now.day(), now.month(), now.year());  
  Serial.print(F("Date/Time: "));
  Serial.println(t);
  Serial.println(now.hour());
  delay(1000);

  digitalWrite(LED, HIGH);
   if (now.hour() == 12 && now.minute() == 30) {
    toggle = 1;
    Serial.print("Toggle is");
    Serial.println(toggle);
   }
  if (ir_command == 69){
    Serial.print("Power pressed");
    toggle = 0;
  }
 
  Photo_Resist_Value = analogRead(Photo_Resist_Pin);
  Serial.println(Photo_Resist_Value);
  delay(30);
  if (Photo_Resist_Value < 500 ) { 
    pill = 1;
  }
  if (pill == 0){
    myStepper.step(stepsPerRevolution); 
    delay(500);

   //step one revolution in the other direction:
    myStepper.step(-stepsPerRevolution);
    delay(500);
    Serial.println("No pill detected");
  }
  
  if (toggle == 1){ 
    Serial.println("Pill Dispensed, music playing");
    myservo.write(servoangle);
    digitalWrite(mp3_1, LOW); 
   

  }
   if (toggle == 0){
    Serial.println("System off");
    digitalWrite(mp3_1, HIGH);
    digitalWrite(mp3_2, LOW);
    myservo.write(servohome);
    delay(20);
    pill = 0;
  }

  
IrReceiver.resume();  
}
}
