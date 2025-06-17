#include "avl.hpp"
#include <iostream>

int main(){
    BST<int> b{50, 15, 75, 14, 20, 61, 98, 11, 16, 21, 99, 25};
    b.remove(50);
    b.print();
    return 0;
}