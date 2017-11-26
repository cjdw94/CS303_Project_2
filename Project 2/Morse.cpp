#include "Morse.h"
#include "Syntax_Error.h"
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>

// Namespace for namesake, Samuel F. B. Morse.  =D
using namespace SFBM;
using std::string;
using std::stringstream;
using std::istringstream;

ifstream morse_text;
stringstream text_buffer;
SFBM::Map<string, string> morse_map;

// Opens (specifically) the "morse.txt" source file for processing the given Morse code
void Morse::open_code_key_file() {
	morse_text.open("morse.txt");
	if (!morse_text) {
		throw Syntax_Error("Unable to open file.");
	}
	if (morse_text) {
		/* Method rdbuf() accesses the input file stream's buffer via pointer and transfers into the text_buffer 
		stringstream for further use/manipulation */
		text_buffer << morse_text.rdbuf();
	}
	morse_text.close();
}

void Morse::code_key_eval() {

	// Process each char
	char next_char;
	int i = 0;
	string key;
	string morse_value = "temp";

	while (text_buffer >> next_char) {
		// While processing code characters, concatenate together to form complete string for key
		if ((next_char == '.') || (next_char == '_')) {
			key += next_char;
		}

		// While processing roman characters, assign to morse_value for later map integration
		else if ((next_char != '.') && (next_char != '_')) {
			if (morse_value == "temp") {
				/* Convert roman character from char to string by using string constructor:
				string(size_t n, char a) */
				morse_value = string(1, next_char);
			}
			else {
				morse_map[key] = morse_value;
				// Clear the key to prepare for next key's concatenation process
				key = "";
				/* Convert roman character from char to string by using string constructor:
				string(size_t n, char a) */
				morse_value = string(1, next_char);
			}
		}

		// Look ahead to see if there is anything left to process (anything left in the stream)
		text_buffer >> next_char;

		// If nothing left to process / nothing left in the stream
		if (!text_buffer) {
			morse_map[key] = morse_value;
			key = "";
			morse_value = string(1, next_char);
			break;
		}

		// Else, put the character back and jump back to the top of the loop
		else
			text_buffer.putback(next_char);
	}
}

void Morse::createMap() {
	Morse::open_code_key_file();
	Morse::code_key_eval();
}

void Morse::createBTree() {

}

int main() {

	Morse new_morse;
	new_morse.createMap();

	return 0;
}