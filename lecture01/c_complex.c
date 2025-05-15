#include <stdio.h>

struct Complex{
    double real;
    double imag;
};

void print_complex(struct Complex c){
    printf("%.02lf", c.real);
    if(c.imag >= 0.0)
        printf("+");
    printf("%.02lfi\n", c.imag);
}

int main(){
    struct Complex c1;
    c1.real = 1;
    c1.imag = 1;
    print_complex(c1);
    c1.real = -1;
    c1.imag = -1;
    print_complex(c1);
    return 0;
}

