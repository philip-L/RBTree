//
//  RBTree.h
//  RBTree
//
//  Created by Philip Leblanc on 2017-10-15.
//  Copyright © 2017 Philip Leblanc. All rights reserved.
//

#ifndef RBTree_h
#define RBTree_h

#include <stdio.h>
#include <iostream>

struct Node {
    int data = 0;
    Node * parent = nullptr;
    Node * right = nullptr;
    Node * left = nullptr;
    bool red = false;
};

class RBTree {
private:
    Node * root;
    int size; // number of nodes
    //helper functions
    Node * parent(Node * n) {return n->parent;}
    Node * grandParent(Node * n);
    Node * uncle(Node * n);
    Node * sibling(Node * n);
    void rotateRight(Node * n);
    void rotateLeft(Node * n);
    void clearRecurse(Node * root); //empty the tree
    Node * find(int data); // return nullptr if data is not present
    void removeNode(Node * n);
    void deleteHelper(Node * n);
    Node * findSuccesor(Node * n); //smallest value in right sub-tree
    Node * findPredecessor(Node * n); //largest value in left sub-tree
    void insertRecurse(Node * root, Node * n);
    void insertRepair(Node * n);

public:
    RBTree();
    ~RBTree();
    
    
    Node * getRoot() {return root;}
    int getHeight() {return 0;} //stub
    int getSize() {return size;}
    
    bool isEmpty() {return (root == nullptr) ? true : false;}
    bool search(int data);
    void remove(int data);
    void insert(int data);
    
    //tree traversals
    void inOrder(Node * root);
    void postOrder(Node * root);
    void preOrder(Node * root);
    
    
};

#endif /* RBTree_h */
