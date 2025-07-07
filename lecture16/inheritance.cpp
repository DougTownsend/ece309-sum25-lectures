#include <iostream>

class Shape{
    public:
    virtual int area() = 0;
    virtual void print() = 0;
};

class Circle : public Shape{
    protected:
    int r;

    public:
    Circle(int r = 0) : r(r){}

    int area(){
        return r * 3.14;
    }

    void print(){
        std::cout << "Circle: R: " << r << "Area: " << area() <<"\n";
    }
};

class Rectangle : public Shape{
    protected:
    int l;
    int w;

    public:
    Rectangle(int len =0, int wid = 0) : l(len), w(wid) {}

    int area(){
        return l*w;
    }

    virtual void print(){
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

void print_shape(Shape &r){
    r.print();
}

int main(){
    Rectangle r(10,5);
    print_shape(r);
    Square s(6);
    print_shape(s);
    Circle c(5);
    print_shape(c);
    return 0;
}