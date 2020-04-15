import string

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
	global DEFAULT_OCTAVE
	global ENHARMS
	global KEY_SIGS
	
	
	print("Hello and welcome to this tool.\n")
	
	song_name = strip_and_upper(input("Song name:\n")).replace(" ", "_")
	
	key = KEY_SIGS[strip_and_upper(input("Key?\n"))]
	
	default_octave = DEFAULT_OCTAVE
	if ask_for_octave := input("Default octave? Leave blank for 5.\n").strip() and len(ask_for_octave) == 1 and ask_for_octave in string.digits:
		default_octave = ask_for_octave
	
	default_length = None
	ask_for_length = input("Default length? Leave blank for syntax erroring on leaving length out.\n")
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
	while (new_note_string := strip_and_upper(input(ask_string))) != '':
		note_strings.append(new_note_string)
		ask_string = ""

	string_builder = []
	for note_string in note_strings:
		note_string = note_string.strip()
		if " " in note_string:
			pitch, dur = note_string.split(" ")
		else:
			pitch, dur = note_string, default_octave
		
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

	print(f"Note {song_name}_NOTES[] = {{\n" + "\n".join(string_builder) + "\n};\n\n" + f"const int {song_name}_LENGTH = sizeof({song_name}_NOTES) / sizeof(Note);\n\n" + f"const Song<{song_name}_LENGTH> {song_name} = Song<{song_name}_LENGTH>(&{song_name}_NOTES, ____buzzer___, ___bpm___);")


def main():
	tool()
	
if __name__ == "__main__":
	# main()
	tool()
	
"""
Note MINUTE_WALTZ_NOTES[] = {
  Note(NOTE_GS5, 2),
  Note(NOTE_G5, 5),
  Note(NOTE_GS5, 5),
  Note(NOTE_C5, 5),
  Note(NOTE_AS5, 5),
  Note(NOTE_G5, 5),
  Note(NOTE_GS5, 5),
  Note(NOTE_AS5, 5),
  Note(NOTE_GS5, 5),
  Note(NOTE_C5, 5),
  Note(NOTE_AS5, 5),
  Note(NOTE_G5, 5),
  Note(NOTE_GS5, 5),
  Note(NOTE_C5, 5),
  Note(NOTE_AS5, 5),
  Note(NOTE_G5, 5),
  Note(NOTE_GS5, 5),
  Note(NOTE_SONG_END, 0)
};
"""