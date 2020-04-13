#pragma once

#include "pitches.h"

struct Note {
  int pitch;
  int duration_sixteenths; // Length in sixteenths
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

    this->note_number = this->note_count++; // Keep track of location in the melody.
  }
};

int Note::note_count = 0; // Needs to be initialized here.

int millisecondsPerSixteenthAtBPM(int BPM) {
  return (int)((60.0 * 1000.0) / (BPM * 2.0));
};

void play(Note* note, int pin, int BPM) {
  const int millis_to_play = note->duration_sixteenths * millisecondsPerSixteenthAtBPM(BPM);
  
  if (!note->is_rest) {
    tone(pin, note->pitch, millis_to_play);
  }
  
  delay(millis_to_play + 5);
}
