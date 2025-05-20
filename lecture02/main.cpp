#include <stdio.h>
#include "complex.hpp"

void int_2x(int &i, int *optional){
    if(optional)
        //do something
        printf("opt");
    i = i*2;
}

int main(){
    Complex c1(1,1);
    Complex c2(4,-3.5);
    Complex c3; //Uses the default values
    Complex *p = &c1;
    c1 = c1 + c2;
    c1 = c1.operator+(c2);
    c1 = c1 + 5;
    c1 = -5 + c1;
    c1.print();
    p->print();
    c3.print();
    int j = 10;
    printf("%d\n", j);
    int *ip = nullptr;
    int_2x(j, ip);
    printf("%d\n", j);
    return 0;
}

