#ifndef MORSE_H_
#define MORSE_H_

#include "map.h"

using namespace std;

class Morse {
public:
	void open_code_key_file();

	void code_key_eval();

	void createMap();
	
	void createBTree();

private:
	SFBM::Map<string, string> morse_map;
	static const string CODE_SYMBOLS;

};

#endif