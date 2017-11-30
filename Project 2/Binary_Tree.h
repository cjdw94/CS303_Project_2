#ifndef BINARY_TREE_H
#define BINARY_TREE_H

/** Class for a binary tree. */

//#include <cstddef>
#include <sstream>
#include <stdexcept>
#include <string>
#include <algorithm>
#include "BTNode.h"
#include <vector>

template<typename Item_Type>
class Binary_Tree
{
public:

	// Declarations for setRoot and getRoot methods
	void setRoot(BTNode<Item_Type>* newRoot);
	BTNode<Item_Type>* getRoot();
	
	// Constructors and Functions

	/** Construct an empty Binary_Tree. */
	Binary_Tree() : root(NULL) {}

	/** Construct a Binary_Tree with two subtrees.
	@param the_data The data at the root
	@param left_child The left subtree
	@param right_child The right subtree
	*/
	Binary_Tree(const Item_Type& the_data,
		const Binary_Tree<Item_Type>& left_child
		= Binary_Tree(),
		const Binary_Tree<Item_Type>& right_child
		= Binary_Tree()) :
		root(new BTNode<Item_Type>(the_data, left_child.root,
			right_child.root)) {}

	/** Virtual destructor to avoid warnings */
	virtual ~Binary_Tree() {} // Do nothing.

	/** Return the left subtree. */
	Binary_Tree<Item_Type> get_left_subtree() const;

	/** Return the right subtree. */
	Binary_Tree<Item_Type> get_right_subtree() const;

protected:

	// Protected constructor
	/** Construct a Binary_Tree with a given node as the root */
	Binary_Tree(BTNode<Item_Type>* new_root) : root(new_root) {}

	// Data Field
	BTNode<Item_Type>* root;

};  // End Binary_Tree

template<typename Item_Type>
void Binary_Tree<Item_Type>::setRoot(BTNode<Item_Type>* new_root) {

	root = new_root;
}

template<typename Item_Type>
BTNode<Item_Type>* Binary_Tree<Item_Type>::getRoot() {
	return root;
}

/************************************************
Implementation of member functions
*************************************************/

// Accessors

/** Return the left-subtree. */
template<typename Item_Type>
Binary_Tree<Item_Type>
Binary_Tree<Item_Type>::get_left_subtree() const {
	if (root == NULL) {
		throw std::invalid_argument("get_left_subtree on empty tree");
	}
	return Binary_Tree<Item_Type>(root->left);
}

/** Return the right-subtree */
template<typename Item_Type>
Binary_Tree<Item_Type>
Binary_Tree<Item_Type>::get_right_subtree() const {
	if (root == NULL) {
		throw std::invalid_argument("get_right_subtree on null tree");
	}
	return Binary_Tree<Item_Type>(root->right);
}

#endif


