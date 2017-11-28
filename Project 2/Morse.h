#ifndef MORSE_H_
#define MORSE_H_

#include "map.h"
#include "Binary_Tree.h"
#include "Huffman_Tree.h"
#include <string>
#include <vector>

using namespace SFBM;
using std::string;
using std::vector;

class Morse{
public:
	void open_code_key_file();

	void code_key_eval(SFBM::Map<string, string>& morse_map, vector <Huff_Data<char>>& morse_Huff_Data);

	void assign_weight(char current_char, vector <Huff_Data<char>>& morse_Huff_Data);

	void createMapHuffVect(SFBM::Map<string, string>& morse_map, vector <Huff_Data<char>>& morse_Huff_Data);

	void change_array_size(vector <Huff_Data<char>>& morse_Huff_Data, int size);

private:
	SFBM::Map<string, string> morse_map;

};

#endif
