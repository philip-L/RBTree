  //
//  main.cpp
//  RBTree
//
//  Created by Philip Leblanc on 2017-10-15.
//  Copyright © 2017 Philip Leblanc. All rights reserved.
//

#include <iostream>
#include "RBTree.h"

using namespace std;

int main(int argc, const char * argv[]) {
    RBTree mytree;
    
    cout << "Tree is empty: " << (mytree.isEmpty() ? "true" : "false") << endl << endl;
    
    //insertion test
    mytree.insert(10);
    mytree.insert(5);
    mytree.insert(5);
    mytree.insert(4);
    mytree.insert(3);
    mytree.insert(2);
    mytree.insert(12);
    mytree.insert(13);
    mytree.inOrder(mytree.getRoot());
    cout << endl;
    mytree.insert(14);
    mytree.insert(20);
    mytree.insert(19);
    mytree.insert(18);
    mytree.insert(17);
    mytree.insert(16);
    mytree.insert(1);
    mytree.inOrder(mytree.getRoot());
    cout << endl;
    mytree.insert(0);
    mytree.insert(9);
    mytree.insert(8);
    mytree.insert(6);
    mytree.insert(7);
    mytree.insert(11);
    mytree.insert(15);
    mytree.inOrder(mytree.getRoot());
    cout << endl;
    
    
    //deletion test
    mytree.remove(21);
    mytree.remove(11);
    mytree.remove(18);
    mytree.remove(1);
    mytree.remove(16);
    mytree.remove(12);
    mytree.remove(5);
    mytree.remove(8);
    mytree.remove(20);
    mytree.remove(19);
    mytree.remove(18);
    mytree.remove(17);
    mytree.remove(16);
    mytree.inOrder(mytree.getRoot());
    cout << endl;
    mytree.remove(6);
    mytree.remove(7);
    mytree.remove(9);
    mytree.remove(13);
    mytree.remove(14);
    mytree.remove(15);
    mytree.inOrder(mytree.getRoot());
    cout << endl;
    mytree.remove(10);
    mytree.remove(2);
    mytree.remove(3);
    mytree.remove(0);
    mytree.remove(4);
    mytree.inOrder(mytree.getRoot());
    cout << endl;


    
    return 0;
}
