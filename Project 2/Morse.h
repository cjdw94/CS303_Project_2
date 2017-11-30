#ifndef MORSE_H_
#define MORSE_H_

#include "map.h"
#include "Binary_Tree.h"
#include <string>
#include <vector>

using namespace SFBM;
using std::string;
using std::vector;

class Morse{
public:
	// Opens given/assigned text file of 108-158 characters and loads into stringstream for further manipulation
	void openCodeKeyFile();

	/* Operates from the text_buffer stringstream and evaluates the contents of "morse.txt" character by character, 
	   to populate both the map and binary tree */
	void codeKeyEval(SFBM::Map<string, string>& morse_map, Binary_Tree<char>& morse_tree);

	// Wrapper function to combine functionality of openCodeKeyFile() and codeKeyEval()
	void createMapTree();

	// Decodes a given string that contains a coded message
	string decodeMessage(string coded_msg);

	// Encodes a given string that contains a message in English
	string encodeMessage(string msg);

	static SFBM::Map<string, string> morse_map;
	static Binary_Tree<char> morse_tree;
};

#endif
