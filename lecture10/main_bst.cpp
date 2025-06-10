#include "bst.hpp"
#include <iostream>

int main(){
    BST<int> b;
    b.insert(5);
    b.insert(15);
    b.insert(25);
    b.insert(4);

    b.insert(11);
    b.insert(0);
    std::cout << b.search(15) << "\n"
    << b.search(25) << "\n"
    << b.search(150) << "\n"
    << b.search(0) << "\n"
    << b.search(100) << "\n\n"
    << b.remove(15) << "\n"
    << b.search(25) << "\n";
    return 0;
}