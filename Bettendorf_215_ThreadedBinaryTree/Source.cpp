#include <iostream>
#include <string>
#include "BST.h"
#include "BSTNode.h"
#include "book.h"

using namespace std;

// Luke Bettendorf
//CSCN 215 (003) - Spring 2024
//Programming Assignment 2
//Last Modified: 3/5/2024


void wait(); //Pauses the program until the user presses enter

int main() {

	//Print header
	cout << "Luke Bettendorf -- CSCN 215 (003) -- Programming Assignment 2 -- Threaded Binary Tree\n\n";
	//Create a BST object
	BST<int, string> tree;

	cout << "Testing the insert function to build my tree:\n";
	//Insert nodes into the tree
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
	cout << "BST Tree size: " << tree.size() << '\n';
	cout << "BST Tree Structure: \n\n";
	tree.print();

	//Print inorder traversal
	cout << "\nInorder printing of my tree \n";
	cout << "(Testing the printInorder method and the findNextInorder helper function):\n\n";

	tree.printInorder();

	//Print reverse inorder traversal
	cout << "\nReverse order printing of my tree \n";
	cout << "(Testing the printReverse method and the findPreviousInorder helper function):\n\n";
	tree.printReverse();
	cout << '\n';

	wait();
	return 0;
}

//Wait Function used in CSCN 111 and CSCN 112
//This function pauses the program until the user presses enter
void wait()
{
	//The following if-statement checks to see how many characters are in cin's buffer
	//If the buffer has characters in it, the clear and ignore methods get rid of them.
	if (std::cin.rdbuf()->in_avail() > 0) //If the buffer is empty skip clear and ignore
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //Clear the input buffer 
	}
	std::cout << "Press the Enter key to continue ... ";
	std::cin.get();
}