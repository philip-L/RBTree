//
//  RBTree.cpp
//  RBTree
//
//  Created by Philip Leblanc on 2017-10-15.
//  Copyright © 2017 Philip Leblanc. All rights reserved.
//

#include "RBTree.h"

RBTree::RBTree()
{
    root = nullptr;
    size = 0;
}

RBTree::~RBTree()
{
    if(!isEmpty())
        clearRecurse(root);
}

//returns true if value is in tree
bool RBTree::search(int d)
{
    return find(d) != nullptr ? true : false;
}

void RBTree::remove(int d)
{
    if(search(d))
    {
        Node * n = find(d);
        if(n->left != nullptr && n->right != nullptr) // both children are not null
        {
            Node * p = findPredecessor(n);
            n->data = p->data;
            removeNode(p);
        }
        else // at most one non-null child
            removeNode(n);
        size--;
    }
}

void RBTree::insert(int d)
{
    if(!search(d)) //node doesn't exist
    {
        //create the node
        Node * n = new Node;
        n->data = d;
        n->red = true;
        n->right = nullptr;
        n->left = nullptr;
        n->parent = nullptr;
        //insert
        if(root == nullptr) //simplest case
            root = n;
        else
            insertRecurse(root, n);
        size++;
        insertRepair(n);
//        while (parent(root) != nullptr)
//            root = parent(root);
    }
}

void RBTree::postOrder(Node * r)
{
    if(r == nullptr)
        return;
    postOrder(r->left);
    postOrder(r->right);
    std::cout << "data: " << r->data << ", colour: " << (r->red ? "red" : "black") << std::endl;
}

void RBTree::preOrder(Node * r)
{
    if(r == nullptr)
        return;
    std::cout << "data: " << r->data << ", colour: " << (r->red ? "red" : "black") << std::endl;
    preOrder(r->left);
    preOrder(r->right);
}

void RBTree::inOrder(Node * r)
{
    if(r == nullptr)
        return;
    inOrder(r->left);
    std::cout << "data: " << r->data << ", colour: " << (r->red ? "red" : "black") << std::endl;
    inOrder(r->right);
}


//helper functions

Node * RBTree::grandParent(Node * n)
{
    if(n->parent != nullptr)
        return n->parent->parent;
    else
        return nullptr;
}

Node * RBTree::sibling(Node * n)
{
    if(n->parent == nullptr)
        return nullptr;
    if(n->parent->right == n)
        return n->parent->left;
    else
        return n->parent->right;
}

Node * RBTree::uncle(Node * n)
{
    if(n->parent != nullptr)
        return sibling(n->parent);
    else
        return nullptr;
}

void RBTree::rotateLeft(Node * n)
{
    if(n != nullptr && n->right != nullptr)
    {
        Node * pivot = n->right;
        n->right = pivot->left;
        if(pivot->left != nullptr)
            pivot->left->parent = n;
        pivot->parent = n->parent;
        if(pivot->parent == nullptr)
            root = pivot;
        else if(pivot->parent->right == n)
            pivot->parent->right = pivot;
        else
            pivot->parent->left = pivot;
        pivot->left = n;
        n->parent = pivot;
        n = pivot;
    }
}

void RBTree::rotateRight(Node * n)
{
    if(n != nullptr && n->left != nullptr)
    {
        Node * pivot = n->left;
        n->left = pivot->right;
        if(pivot->right != nullptr)
            pivot->right->parent = n;
        pivot->parent = n->parent;
        if(pivot->parent == nullptr)
            root = pivot;
        else if(pivot->parent->right == n)
            pivot->parent->right = pivot;
        else
            pivot->parent->left = pivot;
        pivot->right = n;
        n->parent = pivot;
        n = pivot;
        
    }
}

void RBTree::clearRecurse(Node * n)
{
    if(n->right != nullptr)
        clearRecurse(n->right);
    else if (n->left != nullptr)
        clearRecurse(n->left);
    n->parent = nullptr;
    delete n;
    n = nullptr;
}

Node * RBTree::find(int d)
{
    Node * iter = root;
    while(iter != nullptr)
    {
        if(iter->data == d)
            return iter;
        else if(d > iter->data)
            iter = iter->right;
        else
            iter = iter->left;
    }
    return nullptr;
}

//at most one non-leaf child
void RBTree::removeNode(Node * n)
{
    
    Node * c = (n->right == nullptr) ? n->left : n->right;
    
    if (c != nullptr) // one child exists
    {
        n->data = c->data;
        if (n->red || c->red)
            n->red = false;
        else
            deleteHelper(c);
        delete c;
        c = nullptr; // does this break the code?
        n->right = nullptr;
        n->left = nullptr;
    }
    else //both children are null
    {
        if (!n->red)
        {
            deleteHelper(n);
        }
        if (size == 1) //edge case of only one node
        {
            delete n;
            n = nullptr;
            root = nullptr;
        }
        else
        {
            if (n->parent != nullptr && n == n->parent->right)
            {
                delete n->parent->right;
                n->parent->right = nullptr;
            }
            else
            {
                delete n->parent->left;
                n->parent->left = nullptr;
            }
            n->parent = nullptr;
            n = nullptr;
            delete n;
        }
    }
}

//if both node to be deleted and it's child are black
void RBTree::deleteHelper(Node * n)
{
    if (n->parent != nullptr) //case 1
    {
        //case 2
        Node *s = sibling(n);
        
        if (s != nullptr && s->red == true)
        {
            n->parent->red = true;
            s->red = false;
            if (n == n->parent->left)
                rotateLeft(n->parent);
            else
                rotateRight(n->parent);
        }
        //case 3
        s = sibling(n);
        if ((n->parent->red == false) && (s == nullptr || ((s->red == false) && (s == nullptr || s->left == nullptr || s->left->red == false) && (s == nullptr || s->right == nullptr || s->right->red == false))))
        {
            if (s != nullptr)
                s->red = true;
            deleteHelper(n->parent);
        }
        else //case 4
        {
            s = sibling(n);
            if ((n->parent->red == true) && (s == nullptr || s->red == false) && (s == nullptr || s->left == nullptr || s->left->red == false) && (s == nullptr || s->right == nullptr || s->right->red == false))
            {
                if (s != nullptr)
                    s->red = true;
                n->parent->red = false;
            }
            else //case 5
            {
                s = sibling(n);
                if (s == nullptr || s->red == false)
                { /* this if statement is trivial, due to case 2 (even though case 2 changed the sibling to a sibling's child, the sibling's child can't be red, since no red parent can have a red child).*/
                    /* The following statements just force the red to be on the left of the left of the parent, or right of the right, so case six will rotate correctly. */
                    if ((n == n->parent->left) && (s == nullptr || s->right == nullptr || s->right->red == false) && (s != nullptr) && (s->left != nullptr) && (s->left->red == true))
                    { /* this last test is trivial too due to cases 2-4. */
                        s->red = true;
                        s->left->red = false;
                        rotateRight(s);
                    }
                    else if ((n == n->parent->right) && (s == nullptr || s->left == nullptr || s->left->red == false) && (s != nullptr) && (s->right != nullptr) && (s->right->red == true))
                    {/* this last test is trivial too due to cases 2-4. */
                        s->red = true;
                        s->right->red = false;
                        rotateLeft(s);
                    }
                }
                // case 6
                s = sibling(n);
                if(s != nullptr)
                    s->red = n->parent->red;
                n->parent->red = false;
                
                if (n == n->parent->left)
                {
                    if (s != nullptr && s->right != nullptr)
                        s->right->red = false;
                    rotateLeft(n->parent);
                }
                else
                {
                    if (s != nullptr && s->left != nullptr)
                        s->left->red = false;
                    rotateRight(n->parent);
                }
            }
        }
    }
}


Node * RBTree::findSuccesor(Node * n)
{
    Node * iter = n->right;
    while(iter->left != nullptr)
        iter = iter->left;
    return iter;
}

Node * RBTree::findPredecessor(Node * n)
{
    Node * iter = n->left;
    while(iter->right != nullptr)
        iter = iter->right;
    return iter;
}

void RBTree::insertRecurse(Node * r, Node * n)
{
    if (r != nullptr && n->data < r->data)
    {
        if (r->left != nullptr)
        {
            insertRecurse(r->left, n);
            return;
        }
        else
            r->left = n;
    }
    else if (r != nullptr && n->data > r->data) {
        if (r->right != nullptr)
        {
            insertRecurse(r->right, n);
            return;
        }
        else
            r->right = n;
    }
    // set parent
    n->parent = r;
}

void RBTree::insertRepair(Node * n)
{
    Node *p = parent(n);
    Node *u = uncle(n);
    Node *g = grandParent(n);
    
    if (p == nullptr) //case 1: The current node N is at the root of the tree
        n->red = false;
    else if (p->red == false) // case 2: The current node's parent P is black
    {} // do nothing
    else if (u != nullptr && u->red == true) //case 3: If both the parent P and the uncle U are red, then both of them can be repainted black and the grandparent G becomes red
    {
        p->red = false;
        u->red = false;
        g->red = true;
        insertRepair(g);
    }
    else if (g != nullptr && (u == nullptr || u->red == false))// case 4: The parent P is red but the uncle U is black
    {
        if (g->left != nullptr && n == g->left->right)
        {
            rotateLeft(p);
            n = n->left;
        }
        else if (g->right != nullptr && n == g->right->left)
        {
            rotateRight(p);
            n = n->right;
        }
        
        //after rotation the n node changes .. update parent and grandparent
        p = parent(n);
        g = grandParent(n);
        
        if (n == p->left)
            rotateRight(g);
        else
            rotateLeft(g);
        p->red = false;
        g->red = true;
    }
}



