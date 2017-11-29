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

	//string decodeMessage(const Binary_Tree<char>& morse_tree);

	//string encodeMessage(const Binary_Tree<char>& morse_tree);

	static SFBM::Map<string, string> morse_map;
	static Binary_Tree<char> morse_tree;
};

#endif
