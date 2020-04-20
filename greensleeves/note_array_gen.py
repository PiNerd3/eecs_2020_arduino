import string
import datetime
import re

WHOLE_FILE = """// ------------- BEGIN GENERATED CODE -------------

/**
 * {song_name}
 * A sketch to play {song_name} using an Arduino Uno, a passive buzzer, and (optionally) a potentiometer.
 * Generated {date} by Arduino Song Tool (name wip), which is written and made available by Nathaniel Hamovitz.
 * To generate your own musical sketch, go to {website_url} and follow the instructions.
 */
 
// Pitch definitions
const int NOTE_B0 = 31;
const int NOTE_C1 = 33;
const int NOTE_CS1 = 35;
const int NOTE_D1 = 37;
const int NOTE_DS1 = 39;
const int NOTE_E1 = 41;
const int NOTE_F1 = 44;
const int NOTE_FS1 = 46;
const int NOTE_G1 = 49;
const int NOTE_GS1 = 52;
const int NOTE_A1 = 55;
const int NOTE_AS1 = 58;
const int NOTE_B1 = 62;
const int NOTE_C2 = 65;
const int NOTE_CS2 = 69;
const int NOTE_D2 = 73;
const int NOTE_DS2 = 78;
const int NOTE_E2 = 82;
const int NOTE_F2 = 87;
const int NOTE_FS2 = 93;
const int NOTE_G2 = 98;
const int NOTE_GS2 = 104;
const int NOTE_A2 = 110;
const int NOTE_AS2 = 117;
const int NOTE_B2 = 123;
const int NOTE_C3 = 131;
const int NOTE_CS3 = 139;
const int NOTE_D3 = 147;
const int NOTE_DS3 = 156;
const int NOTE_E3 = 165;
const int NOTE_F3 = 175;
const int NOTE_FS3 = 185;
const int NOTE_G3 = 196;
const int NOTE_GS3 = 208;
const int NOTE_A3 = 220;
const int NOTE_AS3 = 233;
const int NOTE_B3 = 247;
const int NOTE_C4 = 262;
const int NOTE_CS4 = 277;
const int NOTE_D4 = 294;
const int NOTE_DS4 = 311;
const int NOTE_E4 = 330;
const int NOTE_F4 = 349;
const int NOTE_FS4 = 370;
const int NOTE_G4 = 392;
const int NOTE_GS4 = 415;
const int NOTE_A4 = 440;
const int NOTE_AS4 = 466;
const int NOTE_B4 = 494;
const int NOTE_C5 = 523;
const int NOTE_CS5 = 554;
const int NOTE_D5 = 587;
const int NOTE_DS5 = 622;
const int NOTE_E5 = 659;
const int NOTE_F5 = 698;
const int NOTE_FS5 = 740;
const int NOTE_G5 = 784;
const int NOTE_GS5 = 831;
const int NOTE_A5 = 880;
const int NOTE_AS5 = 932;
const int NOTE_B5 = 988;
const int NOTE_C6 = 1047;
const int NOTE_CS6 = 1109;
const int NOTE_D6 = 1175;
const int NOTE_DS6 = 1245;
const int NOTE_E6 = 1319;
const int NOTE_F6 = 1397;
const int NOTE_FS6 = 1480;
const int NOTE_G6 = 1568;
const int NOTE_GS6 = 1661;
const int NOTE_A6 = 1760;
const int NOTE_AS6 = 1865;
const int NOTE_B6 = 1976;
const int NOTE_C7 = 2093;
const int NOTE_CS7 = 2217;
const int NOTE_D7 = 2349;
const int NOTE_DS7 = 2489;
const int NOTE_E7 = 2637;
const int NOTE_F7 = 2794;
const int NOTE_FS7 = 2960;
const int NOTE_G7 = 3136;
const int NOTE_GS7 = 3322;
const int NOTE_A7 = 3520;
const int NOTE_AS7 = 3729;
const int NOTE_B7 = 3951;
const int NOTE_C8 = 4186;
const int NOTE_CS8 = 4435;
const int NOTE_D8 = 4699;
const int NOTE_DS8 = 4978;

const int NOTE_R = 5000; // Representing a rest. Just something unreachable.


// Settings.

#define VARIABLE_BPM {enable_variable_bpm}

//  Pin assignments
const int PASSIVE_BUZZER = {buzzer_pin};

//  BPM
const int DEFAULT_BPM = {default_bpm};

#if VARIABLE_BPM
  const int BPM_POT = {bpm_pot_pin};
  const int LOWEST_VARIABLE_BPM = (int)(0.5 * DEFAULT_BPM);
  const int HIGHEST_VARIABLE_BPM = 2 * DEFAULT_BPM;
#endif

// Utility and setup.

inline int millisecondsPerBeatAtBPM(int BPM) {{
  return (int)((60.0 * 1000.0) / BPM); // TODO: check for correctness
}};

const int MILLISECONDS_PER_BEAT = millisecondsPerBeatAtBPM(DEFAULT_BPM);

#if VARIABLE_BPM
inline int calculateMillisecondsPerBeatFromPot() {{
  const int pot_val = analogRead(BPM_POT);
  const double BPM_val = (pot_val / 1023.0) * (HIGHEST_VARIABLE_BPM - LOWEST_VARIABLE_BPM) + LOWEST_VARIABLE_BPM;
  return millisecondsPerBeatAtBPM((int)BPM_val);
}};
#endif

// Note object.

struct Note {{
  int pitch;
  int duration_beats; // Length in beats
  int duration_millis; // Length in milliseconds, at default BPM. Calculated.
  bool is_rest;
  
  Note(int pitch, int duration) {{
    if (pitch == NOTE_R) {{
      this->is_rest = true;
    }} else {{
      this->is_rest = false;
      this->pitch = pitch;
    }}
    
    this->duration_beats = duration;
    this->duration_millis = duration * MILLISECONDS_PER_BEAT;
  }}
}};

void play_note(Note* note, int milli_delay = 5) {{
  #if VARIABLE_BPM
    const int millis_to_play = note->duration_beats * calculateMillisecondsPerBeatFromPot();
  #else 
    const int millis_to_play = note->duration_millis;
  #endif
  
  if (!note->is_rest) {{
    tone(PASSIVE_BUZZER, note->pitch, millis_to_play);
  }}
  
  delay(millis_to_play + milli_delay);
  // delay(millis_to_play + (int)(0.05 * (double)millis_to_play)); // Or possibly this
}}

{gened_code}

void play_song() {{
  for (int i = 0; i < {song_name}_LENGTH; i++) {{
    play_note(&({song_name}_NOTES[i]));
  }}
}}

void setup() {{
  #if VARIABLE_BPM
    pinMode(BPM_POT, INPUT);
  #endif

  play_song();
}}

void loop() {{
//  play_song(); // A little quieter.
}}"""

DEFAULT_OCTAVE = '5'
ENHARMS = {
    "AF": "GS",
    "BF": "AS",
    "CF": "B",
    "DF": "CS",
    "EF": "DS",
    "FF": "E",
    "GF": "FS",

    "BS": "C",
    "ES": "F"
}

OPPOSITE_ENHARMS = {v: k for k, v in ENHARMS.items()}

KEYS = ('A', 'B', 'C', 'D', 'E', 'F', 'G', 'AF', 'BF', 'CF', 'DF',
        'EF', 'FF', 'GF', 'AS', 'BS', 'CS', 'DS', 'ES', 'FS', 'GS')

KEY_SIGS = {"C": dict()}

KEY_SIGS["G"] = dict(KEY_SIGS["C"], F="FS")
KEY_SIGS["D"] = dict(KEY_SIGS["G"], C="CS")
KEY_SIGS["A"] = dict(KEY_SIGS["D"], G="GS")
KEY_SIGS["E"] = dict(KEY_SIGS["A"], D="DS")
KEY_SIGS["B"] = dict(KEY_SIGS["E"], A="AS")
KEY_SIGS["FS"] = dict(KEY_SIGS["B"], E="ES")
KEY_SIGS["CS"] = dict(KEY_SIGS["FS"], B="BS")

KEY_SIGS["F"] = dict(KEY_SIGS["C"], B="BF")
KEY_SIGS["BF"] = dict(KEY_SIGS["F"], E="EF")
KEY_SIGS["EF"] = dict(KEY_SIGS["BF"], A="AF")
KEY_SIGS["AF"] = dict(KEY_SIGS["EF"], D="DF")
KEY_SIGS["DF"] = dict(KEY_SIGS["AF"], G="GF")
KEY_SIGS["GF"] = dict(KEY_SIGS["DF"], C="CF")


def sanitized_input(_str):
    return input(_str).strip().upper()

def get_input_satisfying(q, stern_q, func, sanitize = True):
  if sanitize:
    res = sanitized_input(q)
    while not func(res):
      res = sanitized_input(stern_q)
    return res
  else:
    res = input(q)
    while not func(res):
      res = input(stern_q)
    return res


def tool():
    global WHOLE_FILE
    global DEFAULT_OCTAVE
    global ENHARMS
    global KEY_SIGS
    global KEYS
    global OPPOSITE_ENHARMS

    print("Hello and welcome to Arduino Song Tool (name wip).\n")

    song_name_human = get_input_satisfying("Song name:\n", "Song names must start with a letter and must be alphanumeric (spaces are allowed). Please try again:\n", lambda s: re.fullmatch(r"[a-zA-Z][a-zA-Z0-9 ]*", s), sanitize = False)
    song_name = song_name_human.strip().upper().replace(" ", "_")

    key_name = get_input_satisfying("Key?\n", "Please enter a valid key name.\n", lambda s: s in KEYS)
    key = None
    if key_name in KEY_SIGS:
        key = KEY_SIGS[key_name]
    elif key_name in ENHARMS:
        key = KEY_SIGS[ENHARMS[key_name]]
    elif key_name in OPPOSITE_ENHARMS:
        key = KEY_SIGS[OPPOSITE_ENHARMS[key_name]]
    assert(key is not None)

    def check_octave(_str):
      try:
        oct = int(_str)
        return 0 < oct <= 8
      except ValueError:
        return _str == ''
    default_octave = get_input_satisfying(f"Default octave (1 through 8)? Leave blank for {DEFAULT_OCTAVE}.\n", f"Please enter a valid octave. Leave blank for {DEFAULT_OCTAVE}.\n", check_octave)
    if default_octave == '':
      default_octave = DEFAULT_OCTAVE

    def check_length(_str):
      try:
          l = int(_str)
          return l > 1
      except ValueError:
          return _str == ''
    default_length = get_input_satisfying("Default note length (in beats)? Leave blank for erroring when you leave length out.\n", "Please enter a valid note length (in beats). Leave blank for erroring when you leave length out.\n", check_length)
    if default_length == '':
      default_length = None

    note_strings = []
    print("Please enter your melody. Each note is on a new line. Format: <Note><Octave> <Length in beats>")
    while (new_note_string := sanitized_input('')) != '': #nolint #nofmt
        if " " not in new_note_string and default_length is None:
          print("Because you did not enter a default length, you must supply the length of each note. Please try again (your previous entry was discarded).")
        else:
          note_strings.append(new_note_string)

    string_builder = []
    for note_string in note_strings:
        note_string = note_string.strip()
        if " " in note_string:
            pitch, dur = note_string.split(" ")
        else:
            pitch, dur = note_string, default_length

        if pitch[-1] in string.digits:
            octave = pitch[-1]
            pitch = pitch[:-1]
        else:
            octave = default_octave

        while pitch in OPPOSITE_ENHARMS:
          pitch = OPPOSITE_ENHARMS[pitch]
        while pitch in key:
            pitch = key[pitch]
        while pitch in ENHARMS:
            pitch = ENHARMS[pitch]
        if pitch[-1] == 'N':
            pitch = pitch[:-1]

        string_builder.append(f"Note(NOTE_{pitch}{octave}, {dur}),")
    
    buzzer_pin = get_input_satisfying("What pin is your buzzer on? (Pin must be capable of generating a PWM signal - on the Arduino Uno, this is pins 3, 4, 5, 9, 10, and 11.)\n", "Please enter a valid pin.\n", lambda s: re.fullmatch(r"\d\d?", s))

    def check_bpm(_str):
      try:
        l = int(_str)
        return l > 0
      except ValueError:
        return False
    bpm = get_input_satisfying("What is the BPM of your song?\n", "Please enter a positive integer.\n", check_bpm)

    do_variable_bpm = get_input_satisfying("Use a potentiometer to control the tempo of your song as it plays? (y/n)\n", "Please enter a valid response.\n", lambda s: s in {'Y', 'N', 'YES', 'NO', 'T', 'F', 'TRUE', 'FALSE'})
    do_variable_bpm = do_variable_bpm in {'Y', 'YES', 'T', 'TRUE'}
  
    pot_pin = None
    if do_variable_bpm:
      def check_pot_pin(_str):
        return _str == '' or re.fullmatch(r"A?\d\d?", _str)
      pot_pin = get_input_satisfying("What pin is your potentiometer on? (Pin must be capable of reading an analog signal - on the Arduino Uno, this is pins A0 through A5.)\n", "Please enter a valid pin.\n", check_pot_pin)
    else:
      pot_pin = "A0"

    print(WHOLE_FILE.format(buzzer_pin=buzzer_pin, bpm_pot_pin=pot_pin, default_bpm=bpm, enable_variable_bpm=str(do_variable_bpm).lower(), gened_code=(f"Note {song_name}_NOTES[] = {{\n" + " ".join(
        string_builder) + "\n};\n\n" + f"const int {song_name}_LENGTH = sizeof({song_name}_NOTES) / sizeof(Note);\n\n"), song_name=song_name, date=datetime.date.today(), website_url="https://Arduino-Song-Tool-name-wip.nathanielhamovitz.repl.run"))


def main():
    tool()


if __name__ == "__main__":
    tool()
