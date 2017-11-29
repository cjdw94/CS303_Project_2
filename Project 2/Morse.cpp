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
	string key;
	string morse_value = "temp";
	BTNode<char>* root = morse_tree.getRoot();
	BTNode<char>* current_node = root;

	while (text_buffer >> next_char) {

		// While processing code characters, concatenate together to form complete string for key
		if ((next_char == '.') || (next_char == '_')) {
			key += next_char;
		
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

		// While processing roman characters, assign to morse_value for later map/tree integration
		else if ((next_char != '.') && (next_char != '_')) {
			if (morse_value == "temp") {
				/* Convert roman character from char to string by using string constructor:
				string(size_t n, char a) */
				morse_value = string(1, next_char);
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
				key = "";
				morse_value = string(1, next_char);
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
void Morse::createMapTree (SFBM::Map<string, string>& morse_map, Binary_Tree<char>& morse_tree) {
	Morse::openCodeKeyFile();
	Morse::codeKeyEval(morse_map, morse_tree);
}

string Morse::decodeMessage(const Binary_Tree<char>& morse_tree) {

}

string Morse::encodeMessage(const Binary_Tree<char>& morse_tree) {

}

int main() {

	Morse new_morse;
	SFBM::Map<string, string> morse_map;
	Binary_Tree<char> morse_tree(null_char);
	new_morse.createMapTree(morse_map, morse_tree);

	return 0;
}