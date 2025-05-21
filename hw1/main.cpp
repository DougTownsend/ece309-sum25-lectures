#include <stdio.h>
#include <stdlib.h>
#include "vec.hpp"

int main(){
    VecInt v;
    v.push_back(2);
    v.push_back(3);
    v.push_back(5);
    v.push_back(7);
    v.push_back(11);

    int before[] = {2,3,5,7,11};
    int after[] = {2,3,7,11};
    bool test_passed = true;
    printf("Before call to erase()\n");
    for(int i = 0; i < v.size(); i++){
        printf("Index %d: expected %d, got %d\n", i, before[i], v.at(i));
        if (v.at(i) != before[i])
            test_passed = false;
    }
    v.erase(2);
    printf("After call to erase()\n");
    for(int i = 0; i < v.size(); i++){
        printf("Index %d: expected %d, got %d\n", i, after[i], v.at(i));
        if (v.at(i) != after[i])
            test_passed = false;
    }
    if(v.size() != 4){
        printf("Size not updated!\n");
        test_passed = false;
    }
    if(test_passed)
        printf("Tests passed!\n");
    else
        printf("Tests failed. Check output for differences.\n");
    return 0;
}