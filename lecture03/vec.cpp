#include <stdio.h>
#include <stdlib.h>
#include <utility>

class VecInt{
private:
    int *arr;
    int arr_size;
    int arr_capacity;
public:
    VecInt(){
        arr = nullptr;
        arr_size = 0;
        arr_capacity = 0;
    }

    ~VecInt(){
        printf("Destructor called\n");
        if(arr) delete [] arr;
    }

    VecInt(const VecInt &other){
        arr_capacity = other.capacity();
        arr = new int [arr_capacity];
        arr_size = other.size();
        for(int i = 0; i < arr_size; i++){
            arr[i] = other.at(i);
        }
    }

    VecInt& operator=(const VecInt &other){
        arr_capacity = other.capacity();
        arr = new int [arr_capacity];
        arr_size = other.size();
        for(int i = 0; i < arr_size; i++){
            arr[i] = other.at(i);
        }
        printf("assignment called\n");
        return *this;
    }

    VecInt(VecInt &&other){
        arr_capacity = other.capacity();
        arr = other.arr;
        arr_size = other.size();
        other.arr = nullptr;
        other.arr_size = 0;
        other.arr_capacity = 0;
    }

    void push_back(int d){
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

    int size(void) const{
        return arr_size;
    }

    int capacity(void) const{
        return arr_capacity;
    }

    int at(int i) const{
        if(i >=0 && i < arr_size){
            return arr[i];
        } else {
            exit(1);
        }
    }
};

VecInt v;
int main(){
    v.push_back(1);
    v.push_back(3);
    v.push_back(2);
    v.push_back(5);
    v.push_back(5);

    for(int i = 0; i < v.size(); i++)
        printf("%d\n", v.at(i));
    printf("here\n");
    VecInt v2 = std::move(v);
    printf("%d\n", v2.at(3));
    return 0;
}