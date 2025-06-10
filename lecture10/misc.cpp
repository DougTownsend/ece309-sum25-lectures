#include <iostream>
#include <unordered_set>
#include <stdlib.h>

class test{
    public:
    int x;
    test(){
        std::cout << "Default\n";
    }

    test(int n) : x(n){
        std::cout << "param\n";
    }

    test& operator=(const test& other){
        std::cout << "operator=\n";
        x = other.x;
        return *this;
    }
};

int main(){
    test t;
    t = test(5);
    std::unordered_set<int> s;
    std::cout << s.bucket_count() << "\n";
    s.insert(0);
    std::cout << "bucket count " << s.bucket_size(0) << "\n";
    s.insert(12);
    std::cout << "bucket count " << s.bucket_size(0) << "\n";
    std::cout << s.bucket_count() << "\n";
    size_t last_count = s.bucket_count();
    for(int i = 0; i < 10000; i++){
        s.insert(rand());
        if(s.bucket_count() != last_count){
            last_count = s.bucket_count();
            std::cout << i << " " << s.bucket_count() << "\n";
        }
    }
}