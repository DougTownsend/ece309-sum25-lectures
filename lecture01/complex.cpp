#include <stdio.h>

class Complex{
private:
    double real;
    double imag;

public:
    /*
    //Cannot have this if the other constructor has default values
    //for both parameters.
    //Default constructor:
    Complex(){
        real = 0;
        imag = 0;
    }
    */

    //If arguments are provided, they are used.
    //Otherwise, it uses the default values.
    //Parameterized Constructor:
    Complex(double r=0.0, double i=0.0){
        real = r;
        imag = i;
    }

    void print(){
        printf("%.02lf", real);
        if(imag >= 0.0)
            printf("+");
        printf("%.02lfi\n", imag);
    }

    void add(Complex c){
        real += c.real;
        imag += c.imag;
    }
};


int main(){
    Complex c1(1,1);
    Complex c2(4,-3.5);
    Complex c3; //Uses the default values
    Complex *p = &c1;
    c1.add(c2);
    c1.print();
    p->print();
    c3.print();
    return 0;
}

