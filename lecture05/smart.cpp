#include <memory>
#include <cstdlib>
#include <iostream>

class Test{
    public:
    int number;
    Test() : number(std::rand() % 100) {
        std::cout << "Construct: " << number << "\n";
    }
    ~Test(){
        std::cout << "Destroy: " << number << "\n";     
    }

};

int main(){
    std::shared_ptr<Test> p(new Test);
    std::cout << "a\n";
    p = nullptr;
    std::cout << "b\n";
    p = std::shared_ptr<Test>(new Test);
    std::cout << p.use_count() << "\n";
    auto q = p;
    std::cout << p.use_count() << "\n";
    q = nullptr;
    std::cout << p.use_count() << "\n";
    auto r = std::make_unique<Test>();
    //auto s = r;
    return 0;
}