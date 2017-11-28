#include "Morse.h"
#include "Binary_Tree.h"
#include "Syntax_Error.h"
#include "Huffman_Tree.h"
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>

// Namespace for namesake, Samuel F. B. Morse.  =D
using namespace SFBM;
using std::string;
using std::stringstream;
using std::istringstream;
using std::ifstream;
using std::vector;

ifstream morse_text;
stringstream text_buffer;

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

void Morse::code_key_eval(SFBM::Map<string, string>& morse_map, vector <Huff_Data<char>>& morse_Huff_Data) {

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

		// While processing roman characters, assign to morse_value for later map and Huffman Tree integration
		else if ((next_char != '.') && (next_char != '_')) {
			if (morse_value == "temp") {
				/* Convert roman character from char to string by using string constructor:
				string(size_t n, char a) */
				morse_value = string(1, next_char);
				/* Call assign_weight to assign weight to character, while simultaneously
				   placing into Huff_Data array */
				assign_weight(next_char, morse_Huff_Data);
			}
			else {
				morse_map[key] = morse_value;
				// Clear the key to prepare for next key's concatenation process
				key = "";
				/* Convert roman character from char to string by using string constructor:
				string(size_t n, char a) */
				morse_value = string(1, next_char);
				/* Call assign_weight to assign weight to character, while simultaneously
				placing into Huff_Data array */
				assign_weight(next_char, morse_Huff_Data);
			}
		}

		// Look ahead to see if there is anything left to process (anything left in the stream)
		text_buffer >> next_char;

		// If nothing left to process / nothing left in the stream
		if (!text_buffer) {
			morse_map[key] = morse_value;
			key = "";
			morse_value = string(1, next_char);
			/* Call assign_weight to assign weight to character, while simultaneously
			placing into Huff_Data array */
			/* Note: At this point, the final char will be a period (from the end of the file.)
			We're going to replace that with a space character for the Huffman Tree.  */
			assign_weight(next_char = ' ', morse_Huff_Data);
			break;
		}

		// Else, put the character back and jump back to the top of the loop
		else
			text_buffer.putback(next_char);
	}
}

void Morse::assign_weight(char current_char, vector <Huff_Data<char>>& morse_Huff_Data){
	int weight = 0, index = 0;

	switch (current_char) {
	case ' ': weight = 1205; index = 0;
		break;
	case 'a': weight = 115; index = 5;
		break;
	case 'b': weight = 18; index = 22;
		break;
	case 'c': weight = 20; index = 20;
		break;
	case 'd': weight = 35; index = 10;
		break;
	case 'e': weight = 380; index = 2;
		break;
	case 'f': weight = 27; index = 14;
		break;
	case 'g': weight = 43; index = 8;
		break;
	case 'h': weight = 11; index = 26;
		break;
	case 'i': weight = 100; index = 6;
		break;
	case 'j': weight = 17; index = 23;
		break;
	case 'k': weight = 39; index = 9;
		break;
	case 'l': weight = 29; index = 12;
		break;
	case 'm': weight = 160; index = 3;
		break;
	case 'n': weight = 140; index = 4;
		break;
	case 'o': weight = 89; index = 7;
		break;
	case 'p': weight = 16; index = 24;
		break;
	case 'q': weight = 23; index = 17;
		break;
	case 'r': weight = 28; index = 13;
		break;
	case 's': weight = 24; index = 16;
		break;
	case 't': weight = 500; index = 1;
		break;
	case 'u': weight = 26; index = 15;
		break;
	case 'v': weight = 14; index = 25;
		break;
	case 'w': weight = 30; index = 11;
		break;
	case 'x': weight = 19; index = 21;
		break;
	case 'y': weight = 21; index = 19;
		break;
	case 'z': weight = 22; index = 18;
		break;
	}

	Huff_Data<char> result(weight, current_char);
	morse_Huff_Data[index] = result;
}

void Morse::createMapHuffVect(SFBM::Map<string, string>& morse_map, vector <Huff_Data<char>>& morse_Huff_Data) {
	Morse::open_code_key_file();
	Morse::code_key_eval(morse_map, morse_Huff_Data);
}

void change_array_size(vector <Huff_Data<char>>& morse_Huff_Data, int size) {
	morse_Huff_Data.reserve(size);
	int weight = 0;
	char current_char = ' ';
	Huff_Data<char> temp(weight, current_char);
	for (int i = 0; i < size; i++) {
		morse_Huff_Data.push_back(temp);
	}
}

int main() {

	Morse new_morse;
	SFBM::Map<string, string> morse_map;
	vector <Huff_Data<char>> morse_Huff_Data;

	change_array_size(morse_Huff_Data, 27);

	new_morse.createMapHuffVect(morse_map, morse_Huff_Data);

	std::ostringstream code;

	Huffman_Tree<char> huff_tree;

	huff_tree.build_tree(morse_Huff_Data);

	huff_tree.print_code(code);

	std::string result = code.str();

	std::cout << result;

	result = huff_tree.decode("....");


	return 0;
}