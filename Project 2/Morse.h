#ifndef MORSE_H_
#define MORSE_H_

#include "map.h"
#include "BT.h"
#include <iostream>

using namespace std;


class Morse{
public:
	void open_code_key_file();

	void constructStuff();

	string decode(string encoded_msg);


private:
	BT tree = BT();

};

#endif
