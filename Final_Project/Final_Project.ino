#include <TimerFreeTone.h>
#include <pitches.h>

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
bool toggle = 0;
int LED = 12;

int servoangle = 90;
int servohome = 180;
bool pill = 0;
int TONE_PIN = 2;
const byte IR_RECEIVE_PIN = 7;
int ir_command;

void setup() {
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
  Wire.begin();
  rtc.begin();
  rtc.adjust(DateTime(2023, 12, 3, 0, 0, 0));
  pinMode(TONE_PIN, OUTPUT);
  myStepper.setSpeed(15);
  pinMode(Photo_Resist_Pin, INPUT);
  Serial.begin(9600);
  myservo.attach(3);
  pinMode(LED, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  myservo.write(servohome);
  // put your setup code here, to run once:

}

void loop() {
  if (IrReceiver.decode()) // Only perform an action if an IR signal is read by the reciever from the remote
   {
      ir_command = IrReceiver.decodedIRData.command;   // Decode IR remote button press signal data
      if (ir_command == 69){
    Serial.println("Power pressed");
    toggle = 0;
    Serial.print("Toggle = ");
    Serial.println(toggle);
  }
IrReceiver.resume();  
}
  
  DateTime now = rtc.now();
  sprintf(t, "%02d:%02d:%02d %02d/%02d/%02d", now.hour(), now.minute(), now.second(), now.day(), now.month(), now.year());  
  Serial.print(F("Date/Time: "));
  Serial.println(t);
  Serial.println(now.hour());
  delay(1000);
  

  digitalWrite(LED, HIGH);
   if (now.hour() == 0 && now.minute() == 2 && now.second() == 0) {
    toggle = 1;
    Serial.print("Toggle is ");
    Serial.println(toggle);
   }
  
 
  Photo_Resist_Value = analogRead(Photo_Resist_Pin);
  Serial.print("Photocell = ");
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
    buzzer_alarm();
    delay(500);
   

  }
   if (toggle == 0){
    Serial.println("System off");
    myservo.write(servohome);
    delay(20);
    pill = 0;
  }

}

void buzzer_alarm(){
  float tempo = 95; //beats per minute
  int melody[] = {G4, FS4, E4, D4, E4, E4}; // notes in the melody (as note names or as frequencies)
  float duration[] = {q, q, q, q, e, q}; // lengths as number of beats per note in melody
   // Array items can be multiple bytes. sizeof()/sizeof(arr[0]) gives array length
  int numNotes = sizeof(melody)/sizeof(melody[0]);
  Serial.println("Playing Alarm");
  play_song(tempo, melody, duration, numNotes); // Call provided function with all song details
}


// This function can play any song and provide Serial feedback
// Tempo should be given as beats per minute
// Melody should be given as an array of note frequences (or names if using pitches library)
// Duration should be given as an array with number of beats for each melody note
// numNotes is the number of notes in the song
void play_song(float tempo, int melody[], float duration[], int numNotes) {
  float beat_delay = (1/tempo) * 60 * 1000; //ms per beat
  Serial.print(tempo);
  Serial.print(" beats per minute -> ");
  Serial.print(beat_delay);
  Serial.println(" ms per beat");
  for (int thisNote = 0; thisNote < numNotes; thisNote++) { // Loop through the notes in the array.
    Serial.print(thisNote);
    Serial.print(" ");
    Serial.print(melody[thisNote]);
    Serial.print(" Hz, ");
    Serial.print(duration[thisNote]);
    Serial.print(" beats, ");
    Serial.print(duration[thisNote]*beat_delay);
    Serial.println(" milliseconds");
    TimerFreeTone(TONE_PIN, melody[thisNote], duration[thisNote]*beat_delay); // Play thisNote for duration
    delay(50); // Short delay between notes.
  }   
}

