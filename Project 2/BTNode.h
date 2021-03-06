#ifndef BTNODE_H_
#define BTNODE_H_
#include <sstream>

/** A node for a Binary Tree. */
template<typename Item_Type>
struct BTNode
{
	// Data Fields
	Item_Type data;
	BTNode<Item_Type>* left;
	BTNode<Item_Type>* right;

	// Constructor
	BTNode(const Item_Type& the_data,
		BTNode<Item_Type>* left_val = NULL,
		BTNode<Item_Type>* right_val = NULL) :
		data(the_data), left(left_val), right(right_val) {}

	// Destructor (to avoid warning message)
	virtual ~BTNode() {}

	// to_string
	// Converts/returns string representation of data in node
	virtual std::string to_string() const {
		std::ostringstream os;
		return os.str();
	}
}; // End BTNode


#endif
