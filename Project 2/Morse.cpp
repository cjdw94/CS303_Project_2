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

// Global stringstream, will be used to house the .txt file in memory 
// (108 characters, ~158 bytes in total, presumably including newline characters)
stringstream text_buffer;

char null_char = NULL;

// Declaration of global containers, being used statically by Morse class
SFBM::Map<string, string> Morse::morse_map;
Binary_Tree<char> Morse::morse_tree(null_char);

/** Opens given/assigned text file of 108-158 characters and loads into stringstream for further manipulation
@param  None
@return None (void function) -> opens (specifically) the "morse.txt" source file for processing the given Morse code
@throws Syntax_Error if a syntax error is detected
*/
void Morse::openCodeKeyFile() {
	ifstream morse_text;
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

/** Operates from the text_buffer stringstream and evaluates the contents of "morse.txt" character by character, to populate
	both the map and binary tree
@param The map and binary tree to be built
@return None (void function) -> populates the map and binary tree with data from "morse.txt" 
								(located in stringstream variable, text_buffer)
@throws Syntax_Error -> If data is attempted to be added to a node that already contains data, throw syntax error
					 -> If data is attempted to be added to the map at a key that already exists, throw syntax error
*/
void Morse::codeKeyEval(SFBM::Map<string, string>& morse_map, Binary_Tree<char>& morse_tree) {

	Map<string, string>::iterator it;
	string found = "";
	char next_char, roman_char;
	int i = 0;
	string morse_value;
	string key = "temp";
	BTNode<char>* root = morse_tree.getRoot();
	BTNode<char>* current_node = root;

	// Process each char
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

		// While processing roman characters, assign roman char to key for later map/tree integration
		else if ((next_char != '.') && (next_char != '_')) {
			if (key == "temp") {
				/* Convert roman character from char to string by using string constructor:
				string(size_t n, char a) */
				key = string(1, next_char);
				/* Save char representation of key (roman_char) for integration into the binary tree*/
				roman_char = next_char;
			}
			else {
				// Reference map to make sure the key doesn't already exist
				it = morse_map.find(key);
				if (it != morse_map.end()) {
					found = it->first;
					if (key == found)
						// If the key exists, throw a syntax error
						throw Syntax_Error("Key already in map.");
				}
				else
					morse_map[key] = morse_value;
				// Populate node with data, reset current_node back to root for next traversal
				if (current_node->data == NULL) {
					current_node->data = roman_char;
				}
				current_node = root;
				// Reset the key for the next map entry
				morse_value = "";
				/* Convert roman character from char to string by using string constructor:
				string(size_t n, char a) */
				key = string(1, next_char);
				/* Save char representation of key (roman_char) for integration into the binary tree*/
				roman_char = next_char;
			}
		}

		// Look ahead to see if there is anything left to process (anything left in the stream)
		text_buffer >> next_char;

		// If nothing left to process / nothing left in the stream
		if (!text_buffer) {
			// Reference map to make sure the key doesn't already exist
			it = morse_map.find(key);
			if (it != morse_map.end()) {
				found = it->first;
				if (key == found)
					// If the key exists, throw a syntax error
					throw Syntax_Error("Key already in map.");
			}
			else
				morse_map[key] = morse_value;
			// Populate node with data, reset current_node back to root for next traversal
			if (current_node->data == NULL) {
				current_node->data = roman_char;
			}
			else {
				throw Syntax_Error("Node already contains data.");
			}
			current_node = root;
			// Reset the key for the next map entry
			key = "";
			/* Convert roman character from char to string by using string constructor:
			string(size_t n, char a) */
			morse_value = string(1, next_char);
			/* Save char representation of key (roman_char) for integration into the binary tree*/
			roman_char = next_char;
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

/** Decodes a given string that contains a coded message
@param  coded_msg, string that contains coded message
@return msg, string containing the newly decoded message in English
@throws Syntax_Error -> If node traversal ever results in a pointer to NULL, throw syntax error 
*/
string Morse::decodeMessage(string coded_msg) {
	string msg = "";
	BTNode<char>* current_node = morse_tree.getRoot();
	for (size_t i = 0; i < coded_msg.length(); i++) {
		if (coded_msg[i] == '.')
			if (current_node->left != NULL)
				current_node = current_node->left;
			else
				throw Syntax_Error("Invalid code, node does not exist.");
		else if (coded_msg[i] == '_')
			if (current_node->right != NULL)
				current_node = current_node->right;
			else
				throw Syntax_Error("Invalid code, node does not exist.");
		else if (coded_msg[i] == ' ') {
			msg += current_node->data;
			current_node = morse_tree.getRoot();
			continue;
		}
	}

	msg += current_node->data;
	return msg;

}

/** Encodes a given string that contains a message in English
@param  msg, string that contains a message in English
@return encoded_msg, string containing the newly coded message in Morse
@throws Syntax_Error -> If given English string to be encoded contains a character not in the map, throw syntax error
*/
string Morse::encodeMessage(string msg) {
	Map<string, string>::iterator it;
	string found = "", encoded_msg = "";
	for (size_t i = 0; i < msg.length(); i++) {
		if (msg[i] == ' ')
			encoded_msg += " ";
		else {
			string key = string(1, msg[i]);
			// Reference map to make sure the key exists
			it = morse_map.find(key);
			if (it != morse_map.end()) {
				found = it->first;
				// If the key exists, use it to encode the message
				if (key == found)
					encoded_msg += morse_map[key] + " ";
				// Else, throw syntax error
				else
					throw Syntax_Error("Key not in map.");
			}
		}
	}
	return encoded_msg;
}




int main() {

	Morse new_morse;

	new_morse.createMapTree();

	string message = new_morse.encodeMessage("why");
	string alldone = new_morse.decodeMessage(message);

	std::cout << alldone;

	return 0;
}