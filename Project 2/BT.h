#pragma once
#ifndef BT_H
#define BT_H

#include <string>
#include <algorithm>
#include "BTNode.h"

using namespace std;

class BT {

public:

	BT() { root = NULL; }

	BTNode<string>* root;
};

#endif 