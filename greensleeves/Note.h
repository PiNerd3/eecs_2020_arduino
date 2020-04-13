int MILLISECONDS_PER_SIXTEENTH = 200;

struct Note {
  int pitch;
  int duration_sixteenths;
  int duration_millis;
  bool is_rest;

  int note_number;
  
  static int note_count;
  
  Note(int pitch, int sixteenths) {
    if (pitch == NOTE_R5) {
      this->is_rest = true;
    } else {
      this->is_rest = false;
      this->pitch = pitch;
    }
    
    this->duration_sixteenths = sixteenths;
    this->duration_millis = sixteenths * MILLISECONDS_PER_SIXTEENTH;

    this->note_number = this->note_count++;
  }

  void play(bool variable_speed = true) {
    int play_duration_millis;
    if (variable_speed) {
      play_duration_millis = this->duration_sixteenths * 200;//getMillisecondsPerSixteenth();
    } else {
      play_duration_millis = this->duration_millis;
    }
    
    if (!this->is_rest) {
      tone(PASSIVE_BUZZER, this->pitch, play_duration_millis);
    }
    
    delay(play_duration_millis + 5);
  }
};

int Note::note_count = 0;
