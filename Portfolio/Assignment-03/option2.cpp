#include "option2.h"
#include "BST.h"
#include <iostream>


int RunApp() {
	BST tree;
	tree.Insert("C", 1);
	tree.Insert("E", 2);
	tree.Insert("A", 3);
	tree.Insert("D", 4);
	tree.Insert("F", 5);
	tree.Insert("B", 6);
	tree.Insert("G", 7);

	std::cout << "InOrder:\n";
	tree.PrintInOrder();

	std::cout << "\nPreOrder:\n";
	tree.PrintPreOrder();

	std::cout << "\nPostOrder:\n";
	tree.PrintPostOrder();

	Node* found = tree.Search("E");
	if (found) {
		std::cout << "\nFound E with value = " << found->GetData() << "\n";
	}

	return 0;
}

