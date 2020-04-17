import string

WHOLE_FILE = """#include "Note.h"

// Settings.

const bool DEBUG = {debug_flag};

//  Pin assignments
const int PASSIVE_BUZZER = {buzzer_pin};
const int BPM_POT = {bpm_pot_pin};

//  BPM
const int DEFAULT_BPM = {default_bpm};

const bool VARIABLE_BPM = {enable_variable_bpm};
const int LOWEST_VARIABLE_BPM = 130;
const int HIGHEST_VARIABLE_BPM = 300;

const int INTER_NOTE_DELAY = 10; // Mimic the action of a real musician with a minute period of silence between notes.


// Utility and setup.

using namespace song;

const int MILLISECONDS_PER_SIXTEENTH = millisecondsPerSixteenthAtBPM(DEFAULT_BPM);

int calculateBPMFromPot(const int pot_pin, const int baseBPM = LOWEST_VARIABLE_BPM, const int topBPM = HIGHEST_VARIABLE_BPM) {
  const int pot_val = analogRead(pot_pin);
  const int BPM_val = int((pot_val / 1023.0) * (topBPM - baseBPM) + baseBPM);
  if (DEBUG) {
    Serial.println(pot_val);
    Serial.println(BPM_val);
  }
  return BPM_val;
};

{gened_code}

// Program proper.

void setup() {
  pinMode(BPM_POT, INPUT);

  if (DEBUG) {
    Serial.begin(9600);
    Serial.println({song_name}_LENGTH);
    Serial.println(MILLISECONDS_PER_SIXTEENTH);

    Serial.println("Finished with setup.\n");
  }

  {song_name}.play();
}

void loop() {}"""

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


def strip_and_upper(_str):
    return _str.strip().upper()


def tool():
    global WHOLE_FILE
    global DEFAULT_OCTAVE
    global ENHARMS
    global KEY_SIGS

    print("Hello and welcome to this tool.\n")

    song_name = strip_and_upper(input("Song name:\n")).replace(" ", "_")

    key_name = strip_and_upper(input("Key?\n"))
    if key_name in KEY_SIGS:
        key = KEY_SIGS[key_name]
    else:
        key = KEY_SIGS[ENHARMS[key_name]]

    default_octave = DEFAULT_OCTAVE
    ask_for_octave = input("Default octave? Leave blank for 5.\n").strip()
    if len(ask_for_octave) == 1 and ask_for_octave in string.digits:
        default_octave = ask_for_octave

    default_length = None
    ask_for_length = input(
        "Default length? Leave blank for syntax erroring on leaving length out.\n")
    try:
        l = int(ask_for_length)
        if l < 1:
            pass
        else:
            default_length = ask_for_length
    except ValueError:
        pass

    note_strings = []
    ask_string = "Please enter your melody. Each note is on a new line. [TODO] Format: <Note><Octave> <Length in sixteenth notes>\n"
    while (new_note_string:= strip_and_upper(input(ask_string))) != '':
        note_strings.append(new_note_string)
        ask_string = ""

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

        while pitch in key:
            pitch = key[pitch]
        while pitch in ENHARMS:
            pitch = ENHARMS[pitch]
        if pitch[-1] == 'N':
            pitch = pitch[:-1]

        string_builder.append(f"  Note(NOTE_{pitch}{octave}, {dur}),")
    string_builder.append("  Note(NOTE_SONG_END, 0)")

    print(WHOLE_FILE.format(debug_flag="false", buzzer_pin="5", bpm_pot_pin="A0", default_bpm="160", enable_variable_bpm="false", gened_code=(f"Note {song_name}_NOTES[] = {{\n" + "".join(
        string_builder) + "\n};\n\n" + f"const int {song_name}_LENGTH = sizeof({song_name}_NOTES) / sizeof(Note);\n\n" + f"const Song<{song_name}_LENGTH> {song_name} = Song<{song_name}_LENGTH>(&{song_name}_NOTES, ____buzzer___, ___bpm___);")))


def main():
    tool()


if __name__ == "__main__":
    # main()
    tool()
