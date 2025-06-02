#include <iostream>
#include <string>
#include <memory>
#include <initializer_list>
#include <vector>
#include <algorithm>

template <typename T>
class DList{
    private:
    class DListNode{
        public:
        std::shared_ptr<DListNode> next;
        std::shared_ptr<DListNode> prev;
        T item;

        DListNode(){
            next = nullptr;
        }
    };
    std::shared_ptr<DListNode> head;
    std::shared_ptr<DListNode> tail;

    public:
    class iterator{
        public:
        friend class DList;
        std::shared_ptr<DListNode> p;
        iterator(std::shared_ptr<DListNode> n = nullptr) : p(n){}
        T& operator*(){return p->item;}
        iterator& operator++(){
            p = p->next;
            return *this;
        }
        iterator& operator--(){
            p = p->prev;
            return *this;
        }
        bool operator==(const iterator& other) {return other.p == p;}
        bool operator!=(const iterator& other) {return other.p != p;}
    };
    DList(){
        head = nullptr;
        tail = nullptr;
    }
    
    DList(std::initializer_list<T> l){
        head = nullptr;
        tail = nullptr;
        for (auto &s : l) push_back(s);
    }

    void clear(){
        while(!empty()){
            pop_front();
        }
    }

    ~DList(){
        clear();
        //head = nullptr;
        //tail = nullptr;
    }

    void copy(const DList& other){
        std::shared_ptr<DListNode> n = other.head;
        while(n){
            push_back(n->item);
            n = n->next;
        }
    }

    DList(const DList &other){
        head = nullptr;
        tail = nullptr;
        copy(other);
    }

    DList& operator=(const DList &other){
        clear();
        copy(other);
        return *this;
    }

    bool empty(){
        return head == nullptr;
    }

    iterator begin(){
        return iterator(head);
    }

    iterator end(){
        return iterator(nullptr);
    }

    iterator push_back(T s){
        auto n = std::make_shared<DListNode>();
        n->item = s;
        n->next = nullptr;
        n->prev = nullptr;
        if(empty()){
            head = n;
            tail = n;
        } else {
            tail->next = n;
            n->prev = tail;
            tail = n;
        }
        return iterator(n);
    }

    iterator push_front(T s){
        auto n = std::make_shared<DListNode>();
        n->item = s;
        n->next = nullptr;
        n->prev = nullptr;
        if(empty()){
            head = n;
            tail = n;
        } else {
            head->prev = n;
            n->next = head;
            head = n;
        }
        return iterator(n);
    }

    T pop_front(){
        T copy = head->item;
        head = head->next;
        if(head)
            head->prev = nullptr;
        if (head == nullptr) tail = nullptr;
        return copy;
    }

    T pop_back(){
        T copy = tail->item;
        tail = tail->prev;
        if(tail)
            tail->next = nullptr;
        if (tail == nullptr) head = nullptr;
        return copy;
    }

    void print(){
        std::shared_ptr<DListNode> n(head);
        while(n){
            std::cout << n->item << "\n";
            n = n->next;
        }
    }

    void print_rev(){
        std::shared_ptr<DListNode> n(tail);
        while(n){
            std::cout << n->item << "\n";
            n = n->prev;
        }
    }

    iterator insert_after(iterator it, T s){
        iterator retval;
        if(!it.p) retval = push_front(s);
        else if (it.p == tail) retval = push_back(s);
        else {
            auto newnode = std::make_shared<DListNode>();
            newnode->item = s;
            newnode->prev = it.p;
            newnode->next = it.p->next;
            it.p->next->prev = newnode;
            it.p->next = newnode;
            retval = newnode;
        }
        return retval;
    }
};

using std::cout;

int main(){
    int b = 5.5;
    DList<std::string> l = {"tofu", "lemons"};
    l.push_front("eggs");
    l.push_front("lettuce");
    l.push_back("apples");

    auto it = l.begin();
    l.print();
    cout << "\n";
    l.print_rev();

    DList<int> intlist {1, 2, 3,5, 7};
    intlist.print();
    DList<double> doublist {4.4, 5.5, 6.6};
    doublist.print();

    std::vector<int> v = {1, 55, 330,4};
    std::sort(v.begin(), v.end());
    for (auto &i : v) std::cout << i << "\n";
    return 0;
}