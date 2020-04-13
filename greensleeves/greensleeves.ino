#include "pitches.h"
#define NOTE_R5 5000


const int PASSIVE_BUZZER = 5;
const int BPM_POT = A0;

#include "Note.h"

const double BPM = 160.0;
//const int MILLISECONDS_PER_SIXTEENTH = (int)((60.0 * 1000.0) / (BPM * 2.0));

int getMillisecondsPerSixteenth(int baseBPM = 100, int topBPM = 200) {
  double BPM_val = (analogRead(BPM_POT) / 1023.0) * (topBPM - baseBPM) + baseBPM;
  return (int)((60.0 * 1000.0) / (BPM_val * 2.0));
};

//typedef struct Note Note_;

//Note* make_note(int pitch, int duration) {
//  Note* ret = new Note(pitch, duration);
//  ret->pitch = pitch;
//  ret->sixteenth_duration = duration;
//  return ret;
//};

// Notes in the melody.
const Note GREENSLEEVES[] = {
  Note(NOTE_R5, 10),
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
  Note(NOTE_R5, 2),
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
  Note(NOTE_R5, 2)
};

void play_song(const Note[]...) song) {
  const int SONG_LENGTH = 1;//sizeof(song) / sizeof(Note);

  Serial.println(SONG_LENGTH);
  
  for (int i = 0; i < SONG_LENGTH; i++) {
    Serial.println("starting note");
    
//    const Note note = song[i];
//    note.play();

    song[i].play();

//    Serial.println(note.note_number);
//    Serial.println(note.sixteenth_duration);
//    Serial.println(note.millis_duration);
  }
};

void setup() {
//  pinMode(ACTIVE_BUZZER, OUTPUT);

  pinMode(BPM_POT, INPUT);
  
  Serial.begin(9600);
  Serial.println(MILLISECONDS_PER_SIXTEENTH);

  play_song(GREENSLEEVES);
};

void loop() {
//  Serial.println("starting loop");
};
