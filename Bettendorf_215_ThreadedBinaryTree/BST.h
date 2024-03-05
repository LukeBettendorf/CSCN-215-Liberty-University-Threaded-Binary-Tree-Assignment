// From the software distribution accompanying the textbook
// "A Practical Introduction to Data Structures and Algorithm Analysis,
// Third Edition (C++)" by Clifford A. Shaffer.
// Source code Copyright (C) 2007-2011 by Clifford A. Shaffer.
// 11/17/2023 modification by Prof Sipantzi
// This file includes all of the pieces of the BST implementation

// Include the node implementation
#include "BSTNode.h"

// Include the dictionary ADT
#include "dictionary.h"

#pragma once

using namespace std;

// Binary Search Tree implementation for the Dictionary ADT
template <class Key, class E>
class BST : public Dictionary<Key, E> {
private:
    BSTNode<Key, E>* root;   // Root of the BST

    int nodecount;         // Number of nodes in the BST

    // Private "helper" functions
    void clearhelp(BSTNode<Key, E>*);
    BSTNode<Key, E>* inserthelp(BSTNode<Key, E>*,
        const Key&, const E&);
    BSTNode<Key, E>* deletemin(BSTNode<Key, E>*);
    BSTNode<Key, E>* getmin(BSTNode<Key, E>*);
    BSTNode<Key, E>* removehelp(BSTNode<Key, E>*, const Key&);
    E* findhelp(BSTNode<Key, E>*, const Key&) const;
    void printhelp(BSTNode<Key, E>*, int) const;
    void vist(BSTNode<Key, E>*) const;

    //This function will find the next node in order.
    BSTNode<Key, E>* findNextInorder(BSTNode<Key, E>* current) const;
    //This function will find the previous node in order.
    BSTNode<Key, E>* findPrevInorder(BSTNode<Key, E>* current) const;


public:

    BST() { root = NULL; nodecount = 0; }  // Constructor

    //Note from Prof Sipantzi -- I've commented out the destructor
    //since you would have to change clearhelp() to make it work with
    //doubly-threaded trees and that is not part of the assignment.
    //~BST() { clearhelp(root); }            // Destructor

    void clear()   // Reinitialize tree
    {
        clearhelp(root); root = NULL; nodecount = 0;
    }

    // Insert a record into the tree.
    // k Key value of the record.
    // e The record to insert.
    void insert(const Key& k, const E& e) {
        root = inserthelp(root, k, e);
        nodecount++;
    }

    // Remove a record from the tree.
    // k Key value of record to remove.
    // Return: The record removed, or NULL if there is none.
    E* remove(const Key& k) {
        E* temp = findhelp(root, k);   // First find it
        if (temp != NULL) {
            root = removehelp(root, k);
            nodecount--;
        }
        return temp;
    }
    // Remove and return the root node from the dictionary.
    // Return: The record removed, null if tree is empty.
    E* removeAny() {  // Delete min value
        if (root != NULL) {
            E* temp = new E;
            *temp = root->element();
            root = removehelp(root, root->key());
            nodecount--;
            return temp;
        }
        else return NULL;
    }

    // Return Record with key value k, NULL if none exist.
    // k: The key value to find. */
    // Return some record matching "k".
    // Return true if such exists, false otherwise. If
    // multiple records match "k", return an arbitrary one.
    E* find(const Key& k) const { return findhelp(root, k); }

    // Return the number of records in the dictionary.
    int size() { return nodecount; }

    void print() const { // Print the contents of the BST
        if (root == NULL) cout << "The BST is empty.\n";
        else printhelp(root, 0);
    }

    //This function prints out the tree in order without using recursion.
    void printInorder() const {
        //Create a pointer to the root of the tree.
        BSTNode<Key, E>* current = root;
		//Find the leftmost node in the tree.
		while (current->getLeftBit() == 0) {
			current = current->left();
		}
		//Find the next node in order.
		current = findNextInorder(current);
		//Print out the next node in order.
        while (current != root) {
            vist(current);
            current = findNextInorder(current);
        }
    }

	//This function will print the tree in reverse order without using recursion.
    void printReverse() const {
        //Create a pointer to the root of the tree.
        BSTNode<Key, E>* current = root;
        //Find the rightmost node in the tree.
        while (current->getRightBit() == 0) {
            current = current->right();
        }
        //Find the previous node in order.
        current = findPrevInorder(current);
        //Print out the previous node in order.
        while (current != root) {
            vist(current);
            current = findPrevInorder(current);
        }
    }
};

    // Visit -- prints out root
    template <typename Key, typename E>
    void BST<Key, E>::vist(BSTNode<Key, E>* r) const {
        cout << "Node - " << r->element() << endl;
    }

    // Clean up BST by releasing space back free store
    template <typename Key, typename E>
    void BST<Key, E>::
        clearhelp(BSTNode<Key, E>* root) {
        if (root == NULL) return;
        clearhelp(root->left());
        clearhelp(root->right());
        delete root;
    }

    //Inserthelp is the function that inserts a new node into the tree.
    //This is the first function I need to modify to make the tree doubly-threaded.
    // This function is based on the java code from
    //  https://tutorialhorizon.com/algorithms/double-threaded-binary-tree-complete-implementation/.
    // I modified the code so the boolean variables from the java code are unnecessary.
    template <typename Key, typename E>
    BSTNode<Key, E>* BST<Key, E>::inserthelp(
        BSTNode<Key, E>* root, const Key& k, const E& it) {
        if (root == NULL) {
            //Create a dummy node if it doesn't exist.
            root = new BSTNode<Key, E>(k, it, NULL, NULL);
            root->setLeftBit(0);
            root->setRightBit(1);
            root->setLeft(root);
            root->setRight(root);
        }
        //Create a new node.
        BSTNode<Key, E>* n = new BSTNode<Key, E>(k, it, NULL, NULL);
        if (root == root->left() && root == root->right()) {
            n->setLeft(root);
            root->setLeft(n);
            n->setLeftBit(root->getLeftBit());
            root->setLeftBit(1);
            n->setRight(root);

        }
        else {
            //Find the position to insert the node
            BSTNode<Key, E>* current = root->left();
            while (true) {
                if (n->key() < current->key()) {
                    //If the left bit is 0, then the left child is a child.
                    if (current->getLeftBit() == 0) {
                        //Set the left child of the new node to the left child of the current node.
                        n->setLeft(current->left());
                        current->setLeft(n);
                        n->setLeftBit(current->getLeftBit());
                        n->setRight(current);
                        current->setLeftBit(1);
                        break;
                    }
                    else {
                        current = current->left();
                    }
                }
                else {
                    //If the right bit is 0, then the right child is added as a child.
                    if (current->getRightBit() == 0) {
                        //Set the right child of the new node to the right child of the current node.
                        n->setRight(current->right());
                        current->setRight(n);
                        n->setRightBit(current->getRightBit());
                        n->setLeft(current);
                        current->setRightBit(1);
                        break;
                    }
                    //If the right bit is 1, then the right child is a thread.
                    else {
                        current = current->right();
                    }
                }
            }
        }
        return root;       // Return tree with node inserted

        //Original code
        //if (k < root->key())
        //    root->setLeft(inserthelp(root->left(), k, it));
        //else root->setRight(inserthelp(root->right(), k, it));
        //return root;       // Return tree with node inserted
    }

    // Delete the minimum value from the BST, returning the revised BST
    template <typename Key, typename E>
    BSTNode<Key, E>* BST<Key, E>::
        getmin(BSTNode<Key, E>* rt) {
        if (rt->left() == NULL)
            return rt;
        else return getmin(rt->left());
    }
    template <typename Key, typename E>
    BSTNode<Key, E>* BST<Key, E>::
        deletemin(BSTNode<Key, E>* rt) {
        if (rt->left() == NULL) // Found min
            return rt->right();
        else {                      // Continue left
            rt->setLeft(deletemin(rt->left()));
            return rt;
        }
    }

    // Remove a node with key value k
    // Return: The tree with the node removed
    template <typename Key, typename E>
    BSTNode<Key, E>* BST<Key, E>::
        removehelp(BSTNode<Key, E>* rt, const Key& k) {
        if (rt == NULL) return NULL;    // k is not in tree
        else if (k < rt->key())
            rt->setLeft(removehelp(rt->left(), k));
        else if (k > rt->key())
            rt->setRight(removehelp(rt->right(), k));
        else {                            // Found: remove it
            BSTNode<Key, E>* temp = rt;
            if (rt->left() == NULL) {     // Only a right child
                rt = rt->right();         //  so point to right
                delete temp;
            }
            else if (rt->right() == NULL) { // Only a left child
                rt = rt->left();          //  so point to left
                delete temp;
            }
            else {                    // Both children are non-empty
                BSTNode<Key, E>* temp = getmin(rt->right());
                rt->setElement(temp->element());
                rt->setKey(temp->key());
                rt->setRight(deletemin(rt->right()));
                delete temp;
            }
        }
        return rt;
    }

    // Find a node with the given key value
    template <typename Key, typename E>
    E* BST<Key, E>::findhelp(BSTNode<Key, E>* root,
        const Key& k) const {
        if (root == NULL) return NULL;          // Empty tree
        if (k < root->key())
            return findhelp(root->left(), k);   // Check left
        else if (k > root->key())
            return findhelp(root->right(), k);  // Check right
        else {
            E* temp = new E;
            *temp = root->element();
            return temp;  // Found it
        }
    }

    // Print out a BST
    template <typename Key, typename E>
    void BST<Key, E>::
        printhelp(BSTNode<Key, E>* root, int level) const {


        //Original Code:
        if (root == NULL) return;           // Empty tree
        //Check to see if the node is the dummy node
        if (root->right() == root)
            root = root->left();
        if (root->getLeftBit() == 1)
            printhelp(root->left(), level + 1);   // Do left subtree
        for (int i = 0; i < level; i++)         // Indent to level
            cout << "  ";
        cout << root->key() << "\n";        // Print node value
        if (root->getRightBit() == 1)
            printhelp(root->right(), level + 1);  // Do right subtree
    }

    //This function will find the next node in order.
    template<typename Key, typename E>
    BSTNode<Key, E>* BST<Key, E>::findNextInorder(BSTNode<Key, E>* current) const {

        //If the right bit is 0, then the right child is a thread.
        if (current->getRightBit() == 0) {
            return current->right();
        }
        //If the right bit is 1, then the right child is a child.
        else {
            current = current->right();
            while (current->getLeftBit() == 1) {
                current = current->left();
            }
            return current;
        }
    }

//This function will find the previous node in order.
template<typename Key, typename E>
BSTNode<Key, E>* BST<Key, E>::findPrevInorder(BSTNode<Key, E>* current) const {
	//If the left bit is 1, then the left child is a thread.
    if (current->getLeftBit() == 0) {
		return current->left();
	}

    //If the left bit is 1, then the left child is a child.
	else {
		current = current->left();
		while (current->getRightBit() == 1) {
			current = current->right();
		}
		return current;
	}
    return current;
}