#include "avl.hpp"
#include <iostream>

int main(){
    BST<int> b;
    b.insert(5);
    b.insert(15);
    b.insert(25);
    b.insert(0);

    b.print();

    return 0;
}