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
	void openCodeKeyFile();

	void codeKeyEval(SFBM::Map<string, string>& morse_map, Binary_Tree<char>& morse_tree);

	void createMapTree();

	string decodeMessage(string message);

	string encodeMessage(string message);

	static SFBM::Map<string, string> morse_map;
	static Binary_Tree<char> morse_tree;
};

#endif
