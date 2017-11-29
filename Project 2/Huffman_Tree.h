#ifndef GENERIC_HUFFMAN_TREE_H
#define GENERIC_HUFFMAN_TREE_H

#include <vector>
#include <string>
#include <ostream>
#include "Binary_Tree.h"
#include "Priority_Queue.h"

template<typename T>
struct Huff_Data
{
	//Data Fields
	/** The weight or probability assigned to this HuffData*/
	double weight;
	/** The object if this is a leaf */
	T object;
	// Constructor
	Huff_Data(double w, T the_object) : weight(w), object(the_object) {}

	std::string str() const { 
		std::ostringstream os;
		os << "w: " << weight;

		return os.str();
	}
};



template<typename T>
struct Compare_Huffman_Trees
{
	bool operator()(const Binary_Tree<Huff_Data<T>>& left_tree, const Binary_Tree<Huff_Data<T>>& right_tree) {
			double wLeft = left_tree.get_data().weight;
			double wRight = right_tree.get_data().weight;
			return wLeft > wRight;
	}
};

template<typename T>
class Huffman_Tree {
public:

	void build_tree(const std::vector<Huff_Data<T>>& symbols);

	Huffman_Tree(){ dummy = T(); }
	
	std::string decode(const std::string& coded_message);

	void print_code(std::ostream& out){
		print_code(out, "", huff_tree);
	}

private:
	void print_code(std::ostream& out, std::string code,const Binary_Tree<Huff_Data<T>>& tree);
	Binary_Tree<Huff_Data<T>> huff_tree;
	T dummy;
	

};


template<typename T>
void Huffman_Tree<T>::build_tree(
	const std::vector<Huff_Data<T>>& symbols) { 
		priority_queue < Binary_Tree<Huff_Data<T>>,Compare_Huffman_Trees<T> > the_queue;
		for (size_t i = 0; i < symbols.size(); i++) {
			the_queue.push(Binary_Tree<Huff_Data<T>>(symbols[i]));
		}
		// Build the tree
		while (the_queue.size() > 1) {
		Binary_Tree<Huff_Data<T>> left = the_queue.top();
			the_queue.pop();
			Binary_Tree<Huff_Data<T>> right = the_queue.top();
			the_queue.pop();
			double wl = left.get_data().weight;
			double wr = right.get_data().weight;
			Huff_Data<T> sum(wl + wr, dummy);
			Binary_Tree<Huff_Data<T>> new_tree(sum, left, right);
			the_queue.push(new_tree);
		}
		huff_tree = the_queue.top();
		the_queue.pop();
}


template<typename T>
void Huffman_Tree<T>::print_code(std::ostream& out, std::string code, const Binary_Tree<Huff_Data<T>>& tree) {
		Huff_Data<T> the_data = tree.get_data();
		if (the_data.object != dummy) {
			if (the_data.object == dummy) {
				out << "space: " << code << '\n';
			}
			else {
				out << the_data.object << ": " << code << '\n';
			}
		}
		else {
			print_code(out, code + ".", tree.get_left_subtree());
			print_code(out, code + "_", tree.get_right_subtree());
		}
}

template<typename T>
std::string Huffman_Tree<T>::decode(const std::string& coded_message) {
	std::string result;
	Binary_Tree<Huff_Data<T>> current_tree = huff_tree;
	for (size_t i = 0; i < coded_message.length(); i++) {
		if (coded_message[i] == ' ') 
				current_tree = current_tree.get_left_subtree();
		else if(coded_message[i] == '.' || coded_message[i] == '-')
			current_tree = current_tree.get_right_subtree(); 
		else {
				if (coded_message[i] == '.') 
					current_tree = current_tree.get_left_subtree();
				else
					current_tree = current_tree.get_right_subtree();
		}
			if (current_tree.is_leaf()) {
				Huff_Data<T> the_data = current_tree.get_data();
				result += the_data.object;
				current_tree = huff_tree;
		
			}
		}
		return result;
}


#endif