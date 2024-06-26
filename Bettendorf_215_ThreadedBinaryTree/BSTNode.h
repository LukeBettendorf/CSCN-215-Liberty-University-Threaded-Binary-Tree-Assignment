// From the software distribution accompanying the textbook
// "A Practical Introduction to Data Structures and Algorithm Analysis,
// Third Edition (C++)" by Clifford A. Shaffer.
// Source code Copyright (C) 2007-2011 by Clifford A. Shaffer.
// 11/17/2023 modification by Prof Sipantzi
// This is the file to include for access to the complete binary node
// template implementation

//Last modified by Luke Bettendorf on 3/5/2024

#include "book.h"
#include "BinNode.h"

#pragma once

// Simple binary tree node implementation
template <class Key, class E>
class BSTNode : public BinNode<E> {
private:
  Key k;                  // The node's key
  E it;                   // The node's value
  BSTNode* lc;            // Pointer to left child
  BSTNode* rc;            // Pointer to right child
  //Bitfield indicators to show if the left and right pointers are threads or branches
  unsigned int leftBit : 1;
  unsigned int rightBit : 1;


public:
  // Two constructors -- with and without initial values
  BSTNode() { lc = rc = NULL;}
  BSTNode(Key K, E e, BSTNode* l =NULL, BSTNode* r =NULL)
    { k = K; it = e; lc = l; rc = r; }
  ~BSTNode() {}             // Destructor

  // Functions to set and return the value and key
  E& element() { return it; }
  void setElement(const E& e) { it = e; }
  Key& key() { return k; }
  void setKey(const Key& K) { k = K; }

  // Functions to set and return the children
  inline BSTNode* left() const { return lc; }
  void setLeft(BinNode<E>* b) { lc = (BSTNode*)b; }
  inline BSTNode* right() const { return rc; }
  void setRight(BinNode<E>* b) { rc = (BSTNode*)b; }

  // Return true if it is a leaf, false otherwise
  bool isLeaf() { return (lc == NULL) && (rc == NULL); }

  //Getters and setters for bitfields
  unsigned int getLeftBit() const { return leftBit; }
  unsigned int getRightBit() const { return rightBit; }

  void setLeftBit(int value) { leftBit = value; }
  void setRightBit(int value) { rightBit = value; }

  //This function allows us to compare two nodes.
  bool operator==(BSTNode* b) { return k == b->key(); }
};
