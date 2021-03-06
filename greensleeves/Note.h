#pragma once

#include "pitches.h"

namespace song {

struct Note {
  int pitch;
  int duration_sixteenths; // Length in sixteenths
  bool is_rest;

  int note_number;
  
  static int note_count;
  
  Note(int pitch, int duration) {
    if (pitch == NOTE_R || pitch == NOTE_SONG_END) {
      this->is_rest = true;
    } else {
      this->is_rest = false;
      this->pitch = pitch;
    }
    
    this->duration_sixteenths = duration;

    this->note_number = this->note_count++; // Keep track of location in the melody.
  }
};

int Note::note_count = 0; // Needs to be initialized here.

Note* make_note(int pitch, int duration) {
  return new Note(pitch, duration);
};

const size_t NOTE_SIZE = sizeof(Note);

int millisecondsPerSixteenthAtBPM(int BPM) {
  return (int)((60.0 * 1000.0) / (BPM * 2.0));
};

void play_note(Note* note, int pin, int BPM, int milli_delay = 5) {
  const int millis_to_play = note->duration_sixteenths * millisecondsPerSixteenthAtBPM(BPM);
  
  if (!note->is_rest) {
    tone(pin, note->pitch, millis_to_play);
  }
  
  delay(millis_to_play + milli_delay);
}

template<int MELODY_LENGTH>
struct Song {
  Note (*melody)[MELODY_LENGTH];
  int song_length;
  int buzzer_pin;
  int BPM;

  Song(Note (*melody)[MELODY_LENGTH], int buzzer_pin, int BPM)
    : melody(melody), song_length(MELODY_LENGTH), buzzer_pin(buzzer_pin), BPM(BPM) {}

  void play() const {
    for (int i = 0; i < song_length; i++) {
      play_note(&((*melody)[i]), buzzer_pin, BPM);
    }
  }
};

} // namespace Song
