#include <iostream>
#include <string>
#include "BST.h"
#include "BSTNode.h"

using namespace std;

// Luke Bettendorf
//CSCN 215 (003) - Spring 2024
//Programming Assignment 2
//Last Modified: 2/25/2024

int main() {

	BST<int, string> tree;

	//Inserting nodes into the tree
	tree.insert(24, "twenty-four");
	tree.insert(77, "seventy-seven");
	tree.insert(70, "seventy");
	tree.insert(75, "seventy-five");
	tree.insert(66, "sixty-six");
	tree.insert(79, "seventy-nine");
	tree.insert(68, "sixty-eight");
	tree.insert(67, "sixty-seven");
	tree.insert(69, "sixty-nine");
	tree.insert(90, "ninety");
	tree.insert(85, "eighty-five");
	tree.insert(83, "eighty-three");
	tree.insert(87, "eighty-seven");
	tree.insert(65, "sixty-five");
	tree.print();

	return 0;
}