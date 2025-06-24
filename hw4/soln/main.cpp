#include <iostream>
#include "probe.hpp"

int main(){
    Hash h(50);
    h.insert(5);
    h.insert(99);
    h.insert(0);
    h.insert(34);
    h.insert(2);
    h.insert(10);
    h.insert(19);

    auto it = h.begin();
    while (it != h.end()) {
        std::cout << *it << " ";
        ++it;
    }
    std::cout << "\n";
    
    return 0;
}