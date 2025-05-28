#include <stdio.h>
#include <stdlib.h>
#include "vec.hpp"

VecInt::VecInt(){
    arr = nullptr;
    arr_size = 0;
    arr_capacity = 0;
}

VecInt::~VecInt(){
    if(arr) delete [] arr;
}

VecInt::VecInt(const VecInt &other){
    arr_capacity = other.capacity();
    arr = new int [arr_capacity];
    arr_size = other.size();
    for(int i = 0; i < arr_size; i++){
        arr[i] = other.at(i);
    }
}

VecInt& VecInt::operator=(const VecInt &other){
    arr_capacity = other.capacity();
    arr = new int [arr_capacity];
    arr_size = other.size();
    for(int i = 0; i < arr_size; i++){
        arr[i] = other.at(i);
    }
    return *this;
}

void VecInt::push_back(int d){
    if(arr_capacity == arr_size){
        arr_capacity *= 2;
        if (!arr_capacity) arr_capacity = 1;
        int *tmp = new int[arr_capacity];
        for(int i = 0; i < arr_size; i++){
            tmp[i] = arr[i];
        }
        if(arr) delete [] arr;
        arr = tmp;
    }
    arr[arr_size] = d;
    arr_size++;
}

int VecInt::size(void) const{
    return arr_size;
}

int VecInt::capacity(void) const{
    return arr_capacity;
}

int VecInt::at(int i) const{
    if(i >=0 && i < arr_size){
        return arr[i];
    } else {
        printf("Out of bounds\n");
        exit(1);
    }
}

void VecInt::erase(int idx){
    for(int i = idx + 1; i < arr_size; i++){
        arr[i-1] = arr[i];
    }
    arr_size--;
}