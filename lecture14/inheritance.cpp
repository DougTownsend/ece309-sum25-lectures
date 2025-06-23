#include <iostream>

class Rectangle{
    protected:
    int l;
    int w;

    public:
    Rectangle(int len =0, int wid = 0) : l(len), w(wid) {}

    int area(){
        return l*w;
    }

    void print(){
        std::cout << "Rectangle: L: " << l << " W: " << w << " Area: " << area() << "\n";
    }

};

class Square : public Rectangle{
    public:
    Square(int len =0) : Rectangle(len, len) {}

    void print(){
        std::cout << "Square: L: " << l << " Area: " << area() << "\n";
    }
};

int main(){
    Rectangle r(10,5);
    r.print();
    Square s(6);
    s.print();
    return 0;
}