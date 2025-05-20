#include <stdio.h>
#include "complex.hpp"

void Complex::print(){
    printf("%.02lf", real);
    if(imag >= 0.0)
        printf("+");
    printf("%.02lfi\n", imag);
}

Complex Complex::operator+(const Complex &c) const{
    Complex retval;
    retval.real = real + c.real;
    retval.imag = imag + c.imag;
    return retval;
}

Complex Complex::operator+(const int &c) const{
    Complex retval;
    retval.real = real + c;
    retval.imag = imag;
    return retval;
}

Complex operator+(const int &lhs, const Complex &c){
    Complex retval;
    retval.real = c.real + lhs;
    retval.imag = c.imag;
    return retval;
}