#include "pitches_color.h"
// package includes the pitches and color combinations of individual notes/pitches

// Sensors
int lightsensor = A2;
int button = A4;
int switchsensor = 5;

// Helper fields for lightsensor
int sensorvalue = 0;
int lightvalue = 0;
int highest = 0;
int lowest = 2000;
int difference = 0;

// Actuators
int buzzer = A3;
int red = 6;
int green = A7;
int blue = A8;

// LED helper
int color_mode = 1;

// Helper variable to switch between tempo of songs
double tempo = 1;

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

int hapbday_rest_pos[] = {
  6, 13, 21, 28,
};
int hapbday_rest_len = sizeof(hapbday_rest_pos)/sizeof(hapbday_rest_pos[0]);

// note durations: 4 = quarter note, 8 = eighth note, etc.:
// happy birthday note durations
int hapbday_noteDurations[] = {
  6, 16, 4, 4, 4, 4, 2, 
  6, 16, 4, 4, 4, 4, 2,
  6, 16, 4, 4, 4, 4, 4, 2,
  6, 16, 4, 4, 4, 4, 2
};

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

int mrsaxobeat_rest_pos[] = {
  1, 5, 9, 13, 17, 21, 25,
  34, 38, 42, 46, 50, 54, 58,
  95, 99,
};
int mrsaxobeat_rest_len = sizeof(mrsaxobeat_rest_pos)/sizeof(mrsaxobeat_rest_pos[0]);

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
  8, 4, 6, 6, 8, 4, 6, 6,
};

// // Song pitches
int dynamite[] = {
  // I - WAN - NA - CEL - E - BRATE - AND - LIVE - MY - LIFE
  NOTE_GS5, NOTE_GS5, NOTE_GS5, NOTE_GS5, NOTE_FS5, NOTE_E5, NOTE_FS5, NOTE_GS5, NOTE_B4, NOTE_CS5, 0,
  // SAY - ING - AY - O, - BA - BY - LETS - GO!!
  NOTE_E5, NOTE_FS5, NOTE_E5, NOTE_CS5, 0, NOTE_E5, NOTE_FS5, NOTE_E5, NOTE_CS5, 0,
  // CAUSE - WE - GON' - ROCK - THIS - CLUB
  NOTE_E5, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_E5, 0,
  // WE - GON' - LOW - ALL - NIGHT
  NOTE_E5, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_E5, 0,
  // WE - GON' - LIGHT - IT - UP
  NOTE_E5, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_DS5, 0,
  // LIKE - IT'S - DY - NA - MITE !!
  NOTE_E5, NOTE_FS5, NOTE_GS5, NOTE_B4, NOTE_CS5, 0,
  // CAUSE - I - TOLD - YOU - ONCE
  NOTE_E5, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_E5, 0,
  // NOW - I - TOLD - YOU - TWICE
  NOTE_E5, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_E5, 0,
  // WE - GON' - LIGHT - IT - UP
  NOTE_E5, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_DS5, 0,
  // LIKE - IT'S - DY - NA - MITE !!
  NOTE_E5, NOTE_FS5, NOTE_GS5, NOTE_B4, NOTE_CS5, 0,
};

int dynamite_colors[][3] = {
  COL_GS, COL_GS, COL_GS, COL_GS, COL_FS, COL_E, COL_FS, COL_GS, COL_B, COL_CS, COL_R,
  COL_E, COL_FS, COL_E, COL_CS, COL_R, COL_E, COL_FS, COL_E, COL_CS, COL_R,
  COL_E, COL_E, COL_E, COL_E, COL_E, COL_E, COL_R,
  COL_E, COL_E, COL_E, COL_E, COL_E, COL_R,
  COL_E, COL_E, COL_E, COL_E, COL_DS, COL_R,
  COL_E, COL_FS, COL_GS, COL_B, COL_CS, COL_R,
  COL_E, COL_E, COL_E, COL_E, COL_E, COL_R,
  COL_E, COL_E, COL_E, COL_E, COL_E, COL_R,
  COL_E, COL_E, COL_E, COL_E, COL_DS, COL_R,
  COL_E, COL_FS, COL_GS, COL_B, COL_CS, COL_R,
};
int dynamite_rest_pos[] = {
  10, 15, 20, 27, 33, 39, 45, 51, 57, 63, 69,
};
int dynamite_rest_len = sizeof(dynamite_rest_pos)/sizeof(dynamite_rest_pos[0]);

int dynamite_noteDurations[] = {
  8, 8, 8, 8, 8, 8, 8, 6, 7, 6, 6,
  8, 8, 3, 6, 6, 8, 8, 3, 6, 16,
  8, 8, 8, 6, 6, 8, 4,
  8, 8, 6, 6, 8, 4,
  8, 8, 6, 6, 8, 4,
  8, 8, 6, 6, 8, 4,
  8, 8, 6, 6, 8, 4,
  8, 8, 6, 6, 8, 4,
  8, 8, 6, 6, 8, 4,
  8, 8, 6, 6, 8, 4,
};

void setup() { 

  // set inputs
  pinMode(switchsensor, INPUT);
  pinMode(button, INPUT);
  digitalWrite(button, HIGH);
  digitalWrite(switchsensor, HIGH); 
  // set outputs
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(buzzer, OUTPUT);
  // Begin with LEDs turned off
  analogWrite(red, LOW); 
  analogWrite(green, LOW); 
  analogWrite(blue, LOW);

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

int hapbday_length = (sizeof(hapbday_noteDurations)/sizeof(hapbday_noteDurations[0]));
int mrsaxobeat_length = (sizeof(mrsaxobeat_noteDurations)/sizeof(mrsaxobeat_noteDurations[0]));
int dynamite_length = (sizeof(dynamite_noteDurations)/sizeof(dynamite_noteDurations[0]));

int* song_pitches;
int (*song_colors)[3];
int* song_durations;
int song_length;
int* rest_pos;
int* rest_len;

// the loop routine runs over and over again forever:
void loop() {
  Serial.println(digitalRead(switchsensor));
  // read lightsensor value and constrain any values less than lowest or higher than highest calibration readings
  sensorvalue = analogRead(lightsensor);
  sensorvalue = constrain(sensorvalue, lowest, highest);
  difference = highest - lowest;
  // If the button is pressed then play a song
  if(digitalRead(button) == 0) {
    delay(400);
    // if still holding button change color mode
    // else if it's day then play happy birthday
    // else it's time to PARTY!!
    if (digitalRead(button) == 0) {
      Serial.println("Changing color mode!");
      Serial.println(color_mode);
      color_mode = (color_mode + 1) % 2;
      delay(1000);
    } else {
      if (sensorvalue >= (lowest + (difference * 0.3))) {
        song_pitches = hapbday;
        song_colors = hapbday_colors;
        song_durations = hapbday_noteDurations;
        song_length = hapbday_length;
        rest_pos = hapbday_rest_pos;
        rest_len = hapbday_rest_len;
      } else {
        if (digitalRead(switchsensor) == 0) {
          song_pitches = mrsaxobeat;
          song_colors = mrsaxobeat_colors;
          song_durations = mrsaxobeat_noteDurations;
          song_length = mrsaxobeat_length;
          rest_pos = mrsaxobeat_rest_pos;
          rest_len = mrsaxobeat_rest_len;
        } else {
          song_pitches = dynamite;
          song_colors = dynamite_colors;
          song_durations = dynamite_noteDurations;
          song_length = dynamite_length;
          rest_pos = dynamite_rest_pos;
          rest_len = dynamite_rest_len;
          tempo = 0.75;
        }
      }

      if (color_mode == 0) {
        int rand_colors[song_length][3];
        random_colors(song_colors, song_length, rest_pos, rest_len); 
      }

      tune(song_pitches, song_colors, song_durations, song_length);
      tempo = 1;
    }
  }
}

void random_colors(int colors[][3], int songlength, int rest_position[], int rest_length) {
  for (int i = 0; i < songlength; i++) {
    colors[i][0] = random(0, 256);
    colors[i][1] = random(0, 256);
    colors[i][2] = random(0, 256);
  }
  for (int i = 0; i < rest_length; i++) {
    colors[rest_position[i]][0] = 0;
    colors[rest_position[i]][1] = 0;
    colors[rest_position[i]][2] = 0;
  }
  Serial.println(rest_length);
}

void tune(int pitches[], int colors[][3], int durations[], double songLength) {
  delay(200);
  // loop through the entire song
  Serial.println(sizeof(durations));
  for (int thisNote = 0; thisNote < songLength; thisNote++) {
    int noteDuration = 1000/(int)(durations[thisNote] * tempo);
    // tone plays to the output buzzer a pitch value and a note duration
    tone(buzzer, pitches[thisNote], noteDuration);
    // Output LED colors for current note
    analogWrite(red, colors[thisNote][0]);
    analogWrite(green, colors[thisNote][1]);
    analogWrite(blue, colors[thisNote][2]);
    // slight delay to not have notes overlap or play too fast
    int pauseBetweenNotes = noteDuration * 1.3;
    delay(pauseBetweenNotes);
    
    // Reset LEDs back to off before playing the next note
    analogWrite(red, 0);
    analogWrite(green, 0);
    analogWrite(blue, 0);
    delay(10);

    // If the button is pressed while the song is playing stop the song
    if (digitalRead(button) == 0) {
      delay(1000);
      break;
    }
  }
}