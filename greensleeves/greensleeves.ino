// include "pitches.h":
#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978

#define NOTE_R 5000 // Representing a rest. Just something unreachable.


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

int millisecondsPerSixteenthAtBPM(int BPM) {
  return (int)((60.0 * 1000.0) / (BPM * 2.0));
};

const int MILLISECONDS_PER_SIXTEENTH = millisecondsPerSixteenthAtBPM(DEFAULT_BPM);

int calculateMillisecondsPerSixteenthFromPot(int baseBPM = LOWEST_VARIABLE_BPM, int topBPM = HIGHEST_VARIABLE_BPM) {
  const int pot_val = analogRead(BPM_POT);
//  const double BPM_val = (pot_val / 1023.0) * (topBPM - baseBPM) + baseBPM;
  const double BPM_val = map(pot_val, 0, 1023, baseBPM, topBPM);
  if (DEBUG) {
    Serial.println(pot_val);
    Serial.println(BPM_val);
  }
  return millisecondsPerSixteenthAtBPM((int)BPM_val);
};

// Note object.

struct Note {
  int pitch;
  int duration_sixteenths; // Length in sixteenths
  int duration_millis; // Length in milliseconds, at default BPM. Calculated.
  bool is_rest;

  int note_number;
  
  static int note_count;
  
  Note(int pitch, int duration) {
    if (pitch == NOTE_R) {
      this->is_rest = true;
    } else {
      this->is_rest = false;
      this->pitch = pitch;
    }
    
    this->duration_sixteenths = duration;
    this->duration_millis = duration * MILLISECONDS_PER_SIXTEENTH;

    this->note_number = this->note_count++; // Keep track of location in the melody.
  }

  void play(bool variable_speed = VARIABLE_BPM) {
    int millis_to_play;
    if (variable_speed) {
      millis_to_play = this->duration_sixteenths * calculateMillisecondsPerSixteenthFromPot();
    } else {
      millis_to_play = this->duration_millis;
    }
    
    if (!this->is_rest) {
      tone(PASSIVE_BUZZER, this->pitch, millis_to_play);
    }
    
    delay(millis_to_play + INTER_NOTE_DELAY);
  }
};

int Note::note_count = 0; // Needs to be initialized here.

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
    
    GREENSLEEVES[i].play();
  
    if (DEBUG) {
      Serial.println(GREENSLEEVES[i].note_number);
      Serial.println(GREENSLEEVES[i].duration_sixteenths);
      Serial.println(GREENSLEEVES[i].duration_millis);
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
