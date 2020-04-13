#include "pitches.h"
#include "Note.h"
#include "pitches.h"

// Settings.

const bool DEBUG = false;

//  Pin assignments
const int PASSIVE_BUZZER = 5;
const int BPM_POT = A0;

//  BPM
const int DEFAULT_BPM = 160;

const bool VARIABLE_BPM = false;
const int LOWEST_VARIABLE_BPM = 130;
const int HIGHEST_VARIABLE_BPM = 300;

const int INTER_NOTE_DELAY = 10; // Mimic the action of a real musician with a minute period of silence between notes.


// Utility and setup.


const int MILLISECONDS_PER_SIXTEENTH = millisecondsPerSixteenthAtBPM(DEFAULT_BPM);

int calculateMillisecondsPerSixteenthFromPot(const int baseBPM = LOWEST_VARIABLE_BPM, const int topBPM = HIGHEST_VARIABLE_BPM) {
  const int pot_val = analogRead(BPM_POT);
  const double BPM_val = (pot_val / 1023.0) * (topBPM - baseBPM) + baseBPM;
  if (DEBUG) {
    Serial.println(pot_val);
    Serial.println(BPM_val);
  }
  return millisecondsPerSixteenthAtBPM((int)BPM_val);
};

/** `make_note` helper function.
 *  Doesn't work, for some reason.
 *  Compiler doesn't recognize type here even though it does in, say, the declaration of GREENSLEEVES.

Note* make_note(int pitch, int duration) {
  Note* ret = new Note(pitch, duration);
  ret->pitch = pitch;
  ret->sixteenth_duration = duration;
  return ret;
};

*/

Note GREENSLEEVES[] = {
  Note(NOTE_R, 10),
  Note(NOTE_E5, 2),
  Note(NOTE_G5, 4),
  Note(NOTE_A5, 2),
  Note(NOTE_B5, 3),
  Note(NOTE_C6, 1),
  Note(NOTE_B5, 2),
  Note(NOTE_A5, 4),
  Note(NOTE_FS5, 2),
  Note(NOTE_D5, 3),
  Note(NOTE_E5, 1),
  Note(NOTE_FS5, 2),
  Note(NOTE_G5, 4),
  Note(NOTE_E5, 2),
  Note(NOTE_E5, 3),
  Note(NOTE_DS5, 1),
  Note(NOTE_E5, 2),
  Note(NOTE_FS5, 4),
  Note(NOTE_DS5, 2),
  Note(NOTE_B4, 4),
  Note(NOTE_E5, 2),
  Note(NOTE_G5, 4),
  Note(NOTE_A5, 2),
  Note(NOTE_B5, 3),
  Note(NOTE_C6, 1),
  Note(NOTE_B5, 2),
  Note(NOTE_A5, 4),
  Note(NOTE_FS5, 2),
  Note(NOTE_D5, 3),
  Note(NOTE_E5, 1),
  Note(NOTE_FS5, 2),
  Note(NOTE_G5, 3),
  Note(NOTE_FS5, 1),
  Note(NOTE_E5, 2),
  Note(NOTE_DS5, 3),
  Note(NOTE_CS5, 1),
  Note(NOTE_DS5, 2),
  Note(NOTE_E5, 6),
  Note(NOTE_E5, 4),
  Note(NOTE_R, 2),
  Note(NOTE_D6, 6),
  Note(NOTE_D6, 3),
  Note(NOTE_CS6, 1),
  Note(NOTE_B5, 2),
  Note(NOTE_A5, 4),
  Note(NOTE_FS5, 2),
  Note(NOTE_D5, 3),
  Note(NOTE_E5, 1),
  Note(NOTE_FS5, 2),
  Note(NOTE_G5, 4),
  Note(NOTE_E5, 2),
  Note(NOTE_E5, 3),
  Note(NOTE_DS5, 1),
  Note(NOTE_E5, 2),
  Note(NOTE_FS5, 4),
  Note(NOTE_DS5, 2),
  Note(NOTE_B4, 6),
  Note(NOTE_D6, 6),
  Note(NOTE_D6, 3),
  Note(NOTE_CS6, 1),
  Note(NOTE_B5, 2),
  Note(NOTE_A5, 4),
  Note(NOTE_FS5, 2),
  Note(NOTE_D5, 3),
  Note(NOTE_E5, 1),
  Note(NOTE_FS5, 2),
  Note(NOTE_G5, 3),
  Note(NOTE_FS5, 1),
  Note(NOTE_E5, 2),
  Note(NOTE_DS5, 3),
  Note(NOTE_CS5, 1),
  Note(NOTE_DS5, 2),
  Note(NOTE_E5, 6),
  Note(NOTE_E5, 4),
  Note(NOTE_R, 2)
};

const int GREENSLEEVES_LENGTH = sizeof(GREENSLEEVES) / sizeof(Note);

void play_greensleeves() {
  for (int i = 0; i < GREENSLEEVES_LENGTH; i++) {
    if (DEBUG) {
      Serial.println("starting note");
    }
    
//    GREENSLEEVES[i].play();

    play(&GREENSLEEVES[i], PASSIVE_BUZZER, DEFAULT_BPM);
  
    if (DEBUG) {
      Serial.println(GREENSLEEVES[i].note_number);
      Serial.println(GREENSLEEVES[i].duration_sixteenths);
    }
  }
}

void setup() {
  pinMode(BPM_POT, INPUT);

  if (DEBUG) {
    Serial.begin(9600);
    Serial.println(GREENSLEEVES_LENGTH);
    Serial.println(MILLISECONDS_PER_SIXTEENTH);
  }

  play_greensleeves();
}

void loop() {
//  play_greensleeves(); // A little quieter.
}
