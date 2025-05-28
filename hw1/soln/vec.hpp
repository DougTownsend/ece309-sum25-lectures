#include <stdio.h>
#include <stdlib.h>
#include <utility>

class VecInt{
private:
    int *arr;
    int arr_size;
    int arr_capacity;
public:
    VecInt();
    ~VecInt();
    VecInt(const VecInt &other);
    VecInt& operator=(const VecInt &other);
    void push_back(int d);
    void erase(int idx);
    int size(void) const;
    int capacity(void) const;
    int at(int i) const;
};
