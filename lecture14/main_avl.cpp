#include "avl.hpp"
#include <iostream>

void test(){

    BST<int> b{50, 15, 75, 14, 20, 61, 98, 11, 16, 21, 99, 25};
    b.remove(50);
    b.print();
    std::cout <<"next:\n";
    BST<int> a;
    a = b;
    a.print();
}

int main(){
    test();
    return 0;
}