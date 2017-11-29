#include "Morse.h"
#include "Syntax_Error.h"
#include <fstream>
#include <string>

// Namespace for namesake, Samuel F. B. Morse.  =D
using namespace SFBM;
using std::string;
using std::stringstream;
using std::istringstream;

ifstream morse_text;
stringstream text_buffer;
SFBM::Map<string, string> morse_map;
BTNode<string>* current = new BTNode<string>;

// Opens (specifically) the "morse.txt" source file for processing the given Morse code

void Morse::open_code_key_file() {
	morse_text.open("morse.txt");
	if (!morse_text) {
		throw Syntax_Error("Unable to open file.");
	}
	if (morse_text) {
		// Method rdbuf() accesses the input file stream's buffer via pointer and transfers into the text_buffer
		//stringstream for further use/manipulation 
		text_buffer << morse_text.rdbuf();
	}
	morse_text.close();
}

void Morse::constructStuff()
{
	morse_text.open("morse.txt");
	string line;

	while (getline(morse_text, line))
	{
		string letter = line.substr(0);
		string code = line.substr(1, -1);

		morse_map[letter] = code;

		for (size_t i = 0; i < code.length(); i++) {
			current = tree.root;
			
			if (code[i] == '.') {
				
				//if there is no node then create a node and move the root to it 
				if (tree.root->left == nullptr) {
					BTNode<string>* left = new BTNode<string>;
					current->left = left; 
					current = left;
				}
				else
					current = current->left;
				}		

			//if the character is dash then we move right down the tree
			else if (code[i] == '_') {
				//if there is no right node then make one and move the root to it
				if (current->right == nullptr) {
					BTNode<string>* right = new BTNode<string>;
					current->right = right;
					current = current->right;
				}
				else
					current = current->right;
			}
		}
		current->data = code;
		cout << letter << " " << code << endl;
	}		
}

string Morse::decode(string encoded_msg)
{
	
	string msg = "";
	for (size_t i = 0; i < encoded_msg.length(); i++) {
		current = tree.root;
		if (encoded_msg[i] == '.') {
			current = current->left;
		}
		else if (encoded_msg[i] == '_') {
			current = current->right;
		}
		else {
			msg += current->data;
		}

	}
	return msg;
}





/*
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
				string(size_t n, char a) 
				morse_value = string(1, next_char);
			}
			else {
				morse_map[key] = morse_value;
				// Clear the key to prepare for next key's concatenation process
				key = "";
				/* Convert roman character from char to string by using string constructor:
				string(size_t n, char a) 
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
  

//This code all needs to be debugged. I am having trouble finding the issue with it if you want to give it a shot Corey

//Fills the binary tree from the morse map
Binary_Tree<string> Morse::read_map_to_binary_tree() {
	SFBM::Map<string, string> iterator it;
	it = morse_map.begin();
	if (it.key == NULL) {
		return Binary_Tree<string>();
	}
	else {
		//while there are still codes in the map keep filling the tree
		while (it != morse_map.end()) {
			BTNode<string>* root = morse_tree.getRoot();
			if(root == NULL)

			string the_data;
			it++;
			the_data = it.value;

			//run the for loop to iterate through every character in the morse code
			for (int i = 0; i < the_data.length(); i++) {

				//if the character is a dot we move left down the tree
				if (the_data[i] == '.') {
					//if there is no node then create a node and move the root to it 
					if (root.left == NULL) {
						BTNode<string>* left;
						root.left = left;
						root = root.left;

					else
						root = root.left;
					}
				}

				//if the character is dash then we move right down the tree
				else if (the_data[i] == '-') {
					//if there is no right node then make one and move the root to it
					if (root.right == NULL) {
						BTNode<string>* right;
						root.right = right;
						root* = root.left;
					}
					else
						root = root.right;
				}
				
			}
			//assign the_data to the last node we moved to before restarting the while loop
			root.data = the_data;
		}
	}
}
*/





int main() {

	Morse new_morse;
	new_morse.constructStuff();
	string message = "._ .__.";
	message = new_morse.decode(message);

	cout << message;

	return 0;
}