#include "pitches_color.h"
// package includes the pitches and color combinations of individual notes/pitches

// Sensors
int lightsensor = A2;
int button = A4;

// Helper fields for lightsensor
int sensorvalue = 0;
int lightvalue = 0;
int highest = 0;
int lowest = 2000;

// Actuators
int buzzer = A3;
int red = 6;
int green = A7;
int blue = A8;

// Helper variable to switch between tempo of songs
int tempo = 1;

// we'll store all the notes for 'happy birthday' in a list:
int hapbday[] = {
// HAP - PY - BIRTH - DAY - TO - YOU!!
NOTE_C5, NOTE_C5, NOTE_D5, NOTE_C5, NOTE_F5, NOTE_E5, 0,
// HAP - PY - BIRTH - DAY - TO - YOU!!
NOTE_C5, NOTE_C5, NOTE_D5, NOTE_C5, NOTE_G5, NOTE_F5, 0,
// HAP - PY - BIRTH - DAY - DEAR - BLANK - BLANK
NOTE_C5, NOTE_C5, NOTE_C6, NOTE_A5, NOTE_F5, NOTE_E5, NOTE_D5, 0,
// HAP - PY - BIRTH - DAY - TO - YOU!!
NOTE_AS5, NOTE_AS5, NOTE_A5, NOTE_F5, NOTE_G5, NOTE_F5, 0,
};

// happy birthday color combinations according to note pitches
int hapbday_colors[][3] = {
// HAP - PY - BIRTH - DAY - TO - YOU!!
COL_C, COL_C, COL_D, COL_C, COL_F, COL_E, COL_R,
// HAP - PY - BIRTH - DAY - TO - YOU!!
COL_C, COL_C, COL_D, COL_C, COL_G, COL_F, COL_R,
// HAP - PY - BIRTH - DAY - DEAR - BLANK - BLANK
COL_C, COL_C, COL_C, COL_A, COL_F, COL_E, COL_D, COL_R,
// HAP - PY - BIRTH - DAY - TO - YOU!!
COL_AS, COL_AS, COL_A, COL_F, COL_G, COL_A, COL_R,
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
// happy birthday note durations
int hapbday_noteDurations[] = {
6, 16, 4, 4, 4, 4, 2, 
6, 16, 4, 4, 4, 4, 2,
6, 16, 4, 4, 4, 4, 4, 2,
6, 16, 4, 4, 4, 4, 2};

// Song pitches
int mrsaxobeat[] = {
// ROUND 1
NOTE_FS4, 0, NOTE_CS5, NOTE_A4, NOTE_FS4, 0, NOTE_CS5, NOTE_A4, NOTE_FS4, 0, NOTE_CS5, NOTE_A4, NOTE_FS4, 0, NOTE_CS5, NOTE_A4, NOTE_B4, 0,
NOTE_CS5, NOTE_A4, NOTE_B4, 0, NOTE_CS5, NOTE_A4, NOTE_GS4, 0,
NOTE_CS4, NOTE_E4, NOTE_FS4, NOTE_A4, NOTE_A4, NOTE_GS4, NOTE_GS4,
// ROUND 2
NOTE_FS4, 0, NOTE_CS5, NOTE_A4, NOTE_FS4, 0, NOTE_CS5, NOTE_A4, NOTE_FS4, 0, NOTE_CS5, NOTE_A4, NOTE_FS4, 0, NOTE_CS5, NOTE_A4, NOTE_B4, 0,
NOTE_CS5, NOTE_A4, NOTE_B4, 0, NOTE_CS5, NOTE_A4, NOTE_GS4, 0,
NOTE_CS4, NOTE_E4, NOTE_FS4, NOTE_A4, NOTE_A4, NOTE_GS4, NOTE_GS4,
// LEAD UP
NOTE_A4, NOTE_A4, NOTE_GS4, NOTE_GS4, NOTE_A4, NOTE_A4, NOTE_GS4, NOTE_GS4, NOTE_A4, NOTE_A4, NOTE_GS4, NOTE_GS4, NOTE_A4, NOTE_A4, NOTE_GS4, NOTE_GS4, NOTE_A4, NOTE_A4, NOTE_A4, NOTE_A4, NOTE_A4, NOTE_A4, NOTE_A4, NOTE_A4, NOTE_A4, NOTE_A4,
NOTE_CS5, NOTE_A4, NOTE_GS4, 0, NOTE_CS5, NOTE_A4, NOTE_GS4, 0,
};

// RGB color combinations for LEDs to flash to the beat of the song
int mrsaxobeat_colors[][3] = {
// ROUND 1
COL_FS, COL_R, COL_CS, COL_A, COL_FS, COL_R, COL_CS, COL_A, COL_FS, COL_R, COL_CS, COL_A, COL_FS, COL_R, COL_CS, COL_A, COL_B, COL_R,
COL_CS, COL_A, COL_B, COL_R, COL_CS, COL_A, COL_GS, COL_R,
COL_CS, COL_E, COL_FS, COL_A, COL_A, COL_GS, COL_GS,
// ROUND 2
COL_FS, COL_R, COL_CS, COL_A, COL_FS, COL_R, COL_CS, COL_A, COL_FS, COL_R, COL_CS, COL_A, COL_FS, COL_R, COL_CS, COL_A, COL_B, COL_R,
COL_CS, COL_A, COL_B, COL_R, COL_CS, COL_A, COL_GS, COL_R,
COL_CS, COL_E, COL_FS, COL_A, COL_A, COL_GS, COL_GS,
// LEAD UP
COL_A, COL_A, COL_GS, COL_GS, COL_A, COL_A, COL_GS, COL_GS, COL_A, COL_A, COL_GS, COL_GS, COL_A, COL_A, COL_GS, COL_GS, COL_A, COL_A, COL_A, COL_A, COL_A, COL_A, COL_A, COL_A, COL_A, COL_A,
COL_CS, COL_A, COL_GS, COL_R, COL_CS, COL_A, COL_GS, COL_R,
};

// Song note durations
int mrsaxobeat_noteDurations[] = {
// ROUND 1
6, 6, 6, 4, 6, 6, 6, 4, 6, 6, 6, 4, 6, 6, 6, 4, 6, 6,
6, 4, 6, 6, 6, 4, 6, 4,
12, 12, 12, 6, 6, 6, 6,
// ROUND 2
6, 6, 6, 4, 6, 6, 6, 4, 6, 6, 6, 4, 6, 6, 6, 4, 6, 6,
6, 4, 6, 6, 6, 4, 6, 4,
12, 12, 12, 6, 6, 6, 6,
// LEAD UP
6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 12, 12, 12, 12,
6, 4, 6, 6, 6, 4, 6, 6,
};
 
void setup() { 

  //Switch
  // pinMode(switchPin, INPUT);    // set the switch as an input
  // set button to input
  pinMode(button, INPUT);
  digitalWrite(button, HIGH);
  // digitalWrite(switchPin, HIGH); // enable the pull-up resistor

  // set LEDs to output
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
  
  // Begin with LEDs turned off
  analogWrite(red, LOW); 
  analogWrite(green, LOW); 
  analogWrite(blue, LOW);

  // Seet buzzer to output
  pinMode(buzzer, OUTPUT);

  Serial.begin(9600);

  // calibrate lightsensor values to determine what values are "high" and what are "low" for specific setting
  for(int i = 0; i < 1000; i++) {
    sensorvalue = analogRead(lightsensor);
    
    Serial.print("calibrating sensorvalue ");
    Serial.println(sensorvalue);

    if (sensorvalue < lowest) {
      lowest = sensorvalue;
    } else if (sensorvalue > highest) {
      highest = sensorvalue;
    }

    delay(10);
  }
}

// the loop routine runs over and over again forever:
void loop() {
  // read lightsensor value and constrain any values less than lowest or higher than highest calibration readings
  sensorvalue = analogRead(lightsensor);
  sensorvalue = constrain(sensorvalue, lowest, highest);
  // If the button is pressed and it's sufficiently light out, play happy birthday
  // Else if the button is pressed and it's not light out, TIME TO PARTY. Play mr.saxobeat
  if(digitalRead(button) == 0 && sensorvalue >= (lowest + ((highest - lowest) * 0.3))){  
    delay(200);
    // loop through the entire song
    for (int thisNote = 0; thisNote < (sizeof(hapbday_noteDurations)/sizeof(hapbday_noteDurations[0])); thisNote++) {
      int noteDuration = 1000/(hapbday_noteDurations[thisNote] * tempo);
      // tone plays to the output buzzer a pitch value and a note duration
      tone(buzzer, hapbday[thisNote], noteDuration);
      // Output LED colors for current note
      analogWrite(red, hapbday_colors[thisNote][0]);
      analogWrite(green, hapbday_colors[thisNote][1]);
      analogWrite(blue, hapbday_colors[thisNote][2]);
      // slight delay to not have notes overlap or play too fast
      int pauseBetweenNotes = noteDuration * 1.2;
      delay(pauseBetweenNotes);
      
      // Reset LEDs back to off before playing the next note
      analogWrite(red, 0);
      analogWrite(green, 0);
      analogWrite(blue, 0);

      // If the button is pressed while the song is playing stop the song
      if (digitalRead(button) == 0) {
        delay(1000);
        break;
      }
    }
  } else if (digitalRead(button) == 0 && sensorvalue < (lowest + ((highest - lowest) * 0.3))){
    delay(200);
    for (int thisNote = 0; thisNote < (sizeof(mrsaxobeat_noteDurations)/sizeof(mrsaxobeat_noteDurations[0])); thisNote++) {
      int noteDuration = 1000/(mrsaxobeat_noteDurations[thisNote] * tempo);
      tone(buzzer, mrsaxobeat[thisNote], noteDuration);
      analogWrite(red, mrsaxobeat_colors[thisNote][0]);
      analogWrite(green, mrsaxobeat_colors[thisNote][1]);
      analogWrite(blue, mrsaxobeat_colors[thisNote][2]);
      int pauseBetweenNotes = noteDuration * 1.2;
      delay(pauseBetweenNotes);
      
      analogWrite(red, 0);
      analogWrite(green, 0);
      analogWrite(blue, 0);

      if (digitalRead(button) == 0) {
        delay(1000);
        break;
      }
    }
  }
}