import string

# TARGET_NOTE_LINE = "  Note(NOTE_{pitch}, {dur}),"
DEFAULT_OCTAVE = '5'

def strip_and_upper(_str):
	return _str.strip().upper()

def tool():
	global DEFAULT_OCTAVE
	
	
	print("Hello and welcome to this tool.\n")
	
	song_name = strip_and_upper(input("Song name:\n"))
	
	default_octave = DEFAULT_OCTAVE
	if ask_for_octave := input("Default octave? Leave blank for 5.\n").strip() and len(ask_for_octave) == 1 and ask_for_octave in string.digits:
		default_octave = ask_for_octave
		
	default_length = None
	ask_for_length = input("Default length? Leave blank for syntax erroring on leaving length out.")
	try:
		_ = int(ask_for_length)
		default_length = ask_for_length
	catch:
		pass
			
	note_strings = []
	new_note_string = input("Please enter your melody. Each note is on a new line. [TODO] Format: <Note><Octave> <Length in sixteenth notes>\n").strip().upper()
	
	while new_note_string:
		if not had_custom_octave:
			note_strings.append(new_note_string.strip().upper())
			had_custom_octave = True # just ignore that first one
		new_note_string = input("").strip().upper()
		
	string_builder = []
	for note_string in note_strings:
		pitch, dur = note_string.split(" ")
		if pitch[-1] in string.digits:
			pitch += default_octave
		string_builder.append(f"  Note(NOTE_{pitch}, {dur}),")
	string_builder.append("  Note(NOTE_SONG_END, 0)")

	print(f"Note {song_name}_NOTES[] = {{\n" + "\n".join(string_builder) + "\n};")
		
		
		
def main():
	tool()
	
if __name__ == "__main__":
	# main()
	tool()