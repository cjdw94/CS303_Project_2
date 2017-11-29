#include "Morse.h"
#include "Binary_Tree.h"
#include "Syntax_Error.h"
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
char null_char = NULL;
SFBM::Map<string, string> Morse::morse_map;
Binary_Tree<char> Morse::morse_tree(null_char);

// Opens (specifically) the "morse.txt" source file for processing the given Morse code
void Morse::openCodeKeyFile() {
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

// Populates the map and tree with data from "morse.txt"
void Morse::codeKeyEval(SFBM::Map<string, string>& morse_map, Binary_Tree<char>& morse_tree) {

	// Process each char
	char next_char, morse_char;
	int i = 0;
	string morse_value;
	string key = "temp";
	BTNode<char>* root = morse_tree.getRoot();
	BTNode<char>* current_node = root;

	while (text_buffer >> next_char) {

		// While processing code characters, concatenate together to form complete string for morse value
		if ((next_char == '.') || (next_char == '_')) {
			morse_value += next_char;
		
			// If '.', go left.  If no data/node there, make a dummy node.
			if (next_char == '.') {
				if (current_node->left == NULL) {
					Binary_Tree<char> left_subtree(null_char);
					current_node = (current_node->left = left_subtree.getRoot());
				}
				else
					current_node = current_node->left;
			}
			// If '_', go right.  If no data/node there, make a dummy node.
			else {
				if (current_node->right == NULL) {
					Binary_Tree<char> right_subtree(null_char);
					current_node = (current_node->right = right_subtree.getRoot());
				}
				else
					current_node = current_node->right;
			}
		}

		// While processing roman characters, assign to key for later map/tree integration
		else if ((next_char != '.') && (next_char != '_')) {
			if (key == "temp") {
				/* Convert roman character from char to string by using string constructor:
				string(size_t n, char a) */
				key = string(1, next_char);
				/* Save Morse value as char for Binary Tree*/
				morse_char = next_char;
			}
			else {
				morse_map[key] = morse_value;
				// Populate node with data, reset current_node back to root for next traversal
				if (current_node->data == NULL) {
					current_node->data = morse_char;
				}
				current_node = root;
				// Reset the key for the next map entry
				morse_value = "";
				key = string(1, next_char);
				/* Save Morse value as char for Binary Tree*/
				morse_char = next_char;
			}
		}

		// Look ahead to see if there is anything left to process (anything left in the stream)
		text_buffer >> next_char;

		// If nothing left to process / nothing left in the stream
		if (!text_buffer) {
			morse_map[key] = morse_value;
			// Populate node with data, reset current_node back to root for next traversal
			if (current_node->data == NULL) {
				current_node->data = morse_char;
			}
			current_node = root;
			// Reset the key for the next map entry
			key = "";
			morse_value = string(1, next_char);
			/* Save Morse value as char for Binary Tree*/
			morse_char = next_char;
			break;
		}

		// Else, put the character back and jump back to the top of the loop
		else
			text_buffer.putback(next_char);
	}
}

// Wrapper function to combine functionality of openCodeKeyFile() and codeKeyEval()
void Morse::createMapTree () {
	Morse::openCodeKeyFile();
	Morse::codeKeyEval(morse_map, morse_tree);
}

// Decode a coded message
string Morse::decodeMessage(string message) {
	istringstream decode_stream(message);
	string result = "";
	char next_char;
	BTNode<char>* root = morse_tree.getRoot();
	BTNode<char>* current_node = root;

	while (getline(decode_stream, message, ' ')) {
		istringstream sub_message(message);
		while (sub_message >> next_char) {
			if (next_char == '.') {
				current_node = current_node->left;
			}
			if (next_char == '_') {
				current_node = current_node->right;
			}
		}
		result += (current_node->data);
		current_node = root;
	}

	return result;
}

// Encode a non-coded message
string Morse::encodeMessage(string message) {

	istringstream encode_stream(message);
	string result = "";
	char next_char;

	while (encode_stream >> next_char) {
		string str_char(1, next_char);
		result += morse_map[str_char];
		result += " ";
	}

	return result;
}

int main() {

	Morse new_morse;

	string coded_message = "._ .__. .";

	string message = "ape";

	new_morse.createMapTree();

	std::cout << new_morse.decodeMessage(coded_message) << std::endl << std::endl;

	std::cout << new_morse.encodeMessage(message) << std::endl << std::endl;

	return 0;
}