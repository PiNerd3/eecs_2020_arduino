// Pitch definitions
const int NOTE_B0 = 31; const int NOTE_C1 = 33; const int NOTE_CS1 = 35; const int NOTE_D1 = 37; const int NOTE_DS1 = 39; const int NOTE_E1 = 41; const int NOTE_F1 = 
44; const int NOTE_FS1 = 46; const int NOTE_G1 = 49; const int NOTE_GS1 = 52; const int NOTE_A1 = 55; const int NOTE_AS1 = 58; const int NOTE_B1 = 62; const int NOTE_C2 = 65; const int NOTE_CS2 = 69; const int NOTE_D2 = 73; const int NOTE_DS2 = 78; const int NOTE_E2 = 82; const int NOTE_F2 = 87; const int NOTE_FS2 = 93; const int 
NOTE_G2 = 98; const int NOTE_GS2 = 104; const int NOTE_A2 = 110; const int NOTE_AS2 = 117; const int NOTE_B2 = 123; const int NOTE_C3 = 131; const int NOTE_CS3 = 139; const int NOTE_D3 = 147; const int NOTE_DS3 = 156; const int NOTE_E3 = 165; const int NOTE_F3 = 175; const int NOTE_FS3 = 185; const int NOTE_G3 = 196; const int NOTE_GS3 = 208; const int NOTE_A3 = 220; const int NOTE_AS3 = 233; const int NOTE_B3 = 247; const int NOTE_C4 = 262; const int NOTE_CS4 = 277; const int NOTE_D4 = 294; const int NOTE_DS4 = 311; const int NOTE_E4 = 330; const int NOTE_F4 = 349; const int NOTE_FS4 = 370; const int NOTE_G4 = 392; const int NOTE_GS4 = 415; const int NOTE_A4 = 440; const int NOTE_AS4 = 466; const int NOTE_B4 = 494; const int NOTE_C5 = 523; const int NOTE_CS5 = 554; const int NOTE_D5 = 587; const int NOTE_DS5 = 622; const int NOTE_E5 = 659; const int NOTE_F5 = 698; const int NOTE_FS5 = 740; const int NOTE_G5 = 784; const int NOTE_GS5 = 831; const int NOTE_A5 = 880; const int NOTE_AS5 = 932; const int NOTE_B5 = 988; const int NOTE_C6 = 1047; const int NOTE_CS6 = 1109; const int NOTE_D6 = 1175; const int NOTE_DS6 = 1245; const int NOTE_E6 = 1319; const int NOTE_F6 = 1397; const int NOTE_FS6 = 1480; const int NOTE_G6 = 1568; const int NOTE_GS6 = 1661; const int NOTE_A6 = 1760; const int NOTE_AS6 = 1865; const 
int NOTE_B6 = 1976; const int NOTE_C7 = 2093; const int NOTE_CS7 = 2217; const int NOTE_D7 = 2349; const int NOTE_DS7 = 2489; const int NOTE_E7 = 2637; const int NOTE_F7 = 2794; const int NOTE_FS7 = 2960; const int NOTE_G7 = 3136; const int NOTE_GS7 = 3322; const int NOTE_A7 = 3520; const int NOTE_AS7 = 3729; const int NOTE_B7 = 3951; const int NOTE_C8 = 4186; const int NOTE_CS8 = 4435; const int NOTE_D8 = 4699; const int NOTE_DS8 = 4978;
const int NOTE_R = 5000; // Representing a rest. Just something unreachable.


// Settings.

#define VARIABLE_BPM false

//  Pin assignments
const int PASSIVE_BUZZER = 5;

//  BPM
const int DEFAULT_BPM = 160;

#if VARIABLE_BPM
  const int BPM_POT = 0;
  const int LOWEST_VARIABLE_BPM = (int)(0.5 * DEFAULT_BPM);
  const int HIGHEST_VARIABLE_BPM = 2 * DEFAULT_BPM;
#endif

// Utility and setup.

inline int millisecondsPerSixteenthAtBPM(int BPM) {
  return (int)((60.0 * 1000.0) / (BPM)); // TODO: check for correctness
};

const int MILLISECONDS_PER_SIXTEENTH = millisecondsPerSixteenthAtBPM(DEFAULT_BPM);

#if VARIABLE_BPM
inline int calculateMillisecondsPerSixteenthFromPot() {
  const int pot_val = analogRead(BPM_POT);
  const double BPM_val = (pot_val / 1023.0) * (HIGHEST_VARIABLE_BPM - LOWEST_VARIABLE_BPM) + LOWEST_VARIABLE_BPM;
  return millisecondsPerSixteenthAtBPM((int)BPM_val);
};
#endif

// Note object.

struct Note {
  int pitch;
  int duration_sixteenths; // Length in sixteenths
  int duration_millis; // Length in milliseconds, at default BPM. Calculated.
  bool is_rest;

  Note(int pitch, int duration) {
    if (pitch == NOTE_R) {
      this->is_rest = true;
    } else {
      this->is_rest = false;
      this->pitch = pitch;
    }

    this->duration_sixteenths = duration;
    this->duration_millis = duration * MILLISECONDS_PER_SIXTEENTH;
  }
};

void play_note(Note* note, int BPM, int milli_delay = 5) {
  const int millis_to_play = note->duration_sixteenths * millisecondsPerSixteenthAtBPM(BPM);

  if (!note->is_rest) {
    tone(PASSIVE_BUZZER, note->pitch, millis_to_play);
  }

  delay(millis_to_play + milli_delay);
  // delay(millis_to_play + (int)(0.05 * (double)millis_to_play)); // Or possibly this
}

Note MY_DUMB_SONG_NOTES[] = {
  Note(NOTE_A5, 4),  Note(NOTE_A2, 4),  Note(NOTE_AS2, 4),  Note(NOTE_AS5, 29),  Note(NOTE_SONG_END, 0)
};

const int MY_DUMB_SONG_LENGTH = sizeof(MY_DUMB_SONG_NOTES) / sizeof(Note);



void play_song() {
  for (int i = 0; i < MY_DUMB_SONG_LENGTH; i++) {
    play(&(MY_DUMB_SONG[i]));
  }
}

void setup() {
  #if VARIABLE_BPM
    pinMode(BPM_POT, INPUT);
  #endif

  play_song();
}

void loop() {
//  play_song(); // A little quieter.
}