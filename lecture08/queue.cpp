#include <list>
#include <iostream>

class Queue{
    private:
    std::list<int> l;

    public:
    void push(int i){
        l.push_back(i);
    }

    int pop(){//do not use when empty!
        int ret = *l.begin();
        l.pop_front();
        return ret;
    }

    bool empty(){
        return l.empty();
    }

    int& peek(){
        return *l.begin();
    }
};

int main(){
    Queue s;
    for(int i=0; i < 5; i++)
        s.push(i);
    for(int i=0; i < 5; i++){
        if(s.peek() == 2) std::cout << s.peek();
        std::cout << s.pop() << "\n";
    }
    return 0;
}