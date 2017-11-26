#ifndef MORSE_H_
#define MORSE_H_

#include "map.h"
#include "Binary_Tree.h"

using namespace std;

class Morse {
public:
	void open_code_key_file();

	void code_key_eval();

	void createMap();

	//template <typename Item_Type>
	//Binary_Tree<Item_Type> read_map_to_binary_tree();

private:
	SFBM::Map<string, string> morse_map;
	Binary_Tree<string> morse_tree;

};

#endif