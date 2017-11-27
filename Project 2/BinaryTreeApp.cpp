
#include "Binary_Search_Tree.h"
using namespace std;



int main() {

	vector<std::string> expression{ "/", "*", "5","NULL","NULL","3","NULL","NULL","-","6","NULL","NULL","*","2","NULL","NULL","1"};
	vector<std::string> BinarySearchData{ "lay", "house", "cow", "built", "and", "all", "NULL", "NULL", "ate", "NULL", "NULL", "cock", "cat", "NULL", "NULL", "corn", "NULL", "NULL","dog","crumpled","crowed","NULL","NULL","NULL","forlorn","farmer","NULL","NULL","horn","NULL","NULL","jack","is","in","NULL","NULL","NULL","killed","kept","NULL","NULL","kissed","NULL","NULL","rat","milked","malt","maiden","NULL","NULL","man","NULL","married","NULL","NULL","priest","morn","NULL","NULL","NULL","that","shorn","shaven","NULL","NULL","tattered","sowing","NULL","NULL","NULL","tossed","this","the","NULL","NULL","torn","NULL","NULL","with","waked","NULL","NULL","worried" };
	
	vector<std::string> BinarySearchData_1{"lay", "house", "cow", "built", "and", "all", "NULL", "NULL", "ate", "NULL", "NULL", "cock", "cat", "NULL", "NULL", "bite", "NULL", "NULL", "dog", "crumpled", "crowed", "NULL", "NULL", "NULL", "forlorn", "farmer", "NULL", "NULL", "horn", "NULL", "NULL", "jack", "is", "in", "NULL", "NULL", "NULL", "killed", "kept", "NULL", "NULL", "kissed", "NULL", "NULL", "rat", "milked", "malt", "maiden", "NULL", "NULL", "man", "NULL", "married", "NULL", "NULL", "priest", "morn", "NULL", "NULL", "NULL", "that", "shorn", "shaven", "NULL", "NULL", "tattered", "sowing", "NULL", "NULL", "NULL", "tossed", "this", "the", "NULL", "NULL", "torn", "NULL", "NULL", "with", "waked", "NULL", "NULL", "worried" };

	vector<std::string> BinarySearchData_2{ "cat","NULL","cow","NULL","dog","NULL","fox" };
	
	Binary_Tree<std::string> the_tree;
	the_tree.read_tree(expression);
	int height = the_tree.height();


	std::string preOrder = the_tree.pre_order();
	std::string inOrder = the_tree.in_order();
	std::string postOrder = the_tree.post_order();


	Binary_Search_Tree<std::string> binary_tree;
	binary_tree.read_tree(BinarySearchData);
	std::string target = "kept";
	std::string tobedeleted = "house";
	binary_tree.find(target);
	binary_tree.erase(tobedeleted);
	const std::string* maxNode = binary_tree.max();
	const std::string* minNode = binary_tree.min();
	
	Binary_Search_Tree<std::string> binary_tree_2;
	binary_tree_2.read_tree(BinarySearchData_2);
	target = "fox";
	binary_tree_2.find(target);

	Binary_Tree <std::string> bTree;
	bTree.read_tree(BinarySearchData_1);

	
	

}
