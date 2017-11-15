#pragma once
#include <map>
#include <fstream>

using namespace std;

class Morse {
public:
	void createMap(ifstream& fin);
	
	void createBTree();

private:
	map<string, string> encode_map;

};