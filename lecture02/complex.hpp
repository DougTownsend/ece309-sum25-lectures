#include <stdio.h>

#ifndef COMPLEX_HPP
#define COMPLEX_HPP

class Complex{
public:
    double real;
    double imag;

    Complex(): real(0.0), imag(0.0) {}
    Complex(double r, double i): real(r), imag(i){}

    void print();
    Complex operator+(const Complex &c) const;
    Complex operator+(const int &c) const;
};

Complex operator+(const int &lhs, const Complex &c);
#endif