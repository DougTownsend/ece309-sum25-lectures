#include <iostream>
#include <string>
#include <memory>

class List{
    private:
    class ListNode{
        public:
        std::shared_ptr<ListNode> next;
        std::string item;

        ListNode(){
            next = nullptr;
            item = "";
        }
    };
    std::shared_ptr<ListNode> head;
    std::shared_ptr<ListNode> tail;

    public:
    class iterator{
        public:
        std::shared_ptr<ListNode> p;
        iterator(std::shared_ptr<ListNode> n = nullptr) : p(n){}
        std::string& operator*(){return p->item;}
        iterator& operator++(){
            p = p->next;
            return *this;
        }
        bool operator==(const iterator& other) {return other.p == p;}
        bool operator!=(const iterator& other) {return other.p != p;}
    };
    List(){
        head = nullptr;
        tail = nullptr;
    }

    void clear(){
        while(!empty()){
            pop_front();
        }
    }

    ~List() = default;

    void copy(const List& other){
        std::shared_ptr<ListNode> n = other.head;
        while(n){
            push_back(n->item);
            n = n->next;
        }
    }

    List(const List &other){
        head = nullptr;
        tail = nullptr;
        copy(other);
    }

    List& operator=(const List &other){
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

    void push_back(std::string s){
        auto n = std::make_shared<ListNode>();
        n->item = s;
        n->next = nullptr;
        if(empty()){
            head = n;
            tail = n;
        } else {
            tail->next = n;
            tail = n;
        }
    }

    std::string pop_front(){
        std::string copy = head->item;
        std::shared_ptr<ListNode> n(head);
        head = head->next;
        if (head == nullptr) tail = nullptr;
        return copy;
    }

    void print(){
        std::shared_ptr<ListNode> n(head);
        while(n){
            std::cout << n->item << "\n";
            n = n->next;
        }
    }
};

using std::cout;

int main(){
    List l;
    l.push_back("milk");
    l.push_back("eggs");
    l.push_back("lettuce");
    l.push_back("tomatoes");
    l.push_back("apples");

    l.print();
    cout << "\n";
    std::string front = l.pop_front();
    l.print();

    std::cout << "\n";
    std::cout << front << "\n\n";

    List l2 = l;
    l.pop_front();
    l2.print();
    l2 = l;
    std::cout << "\n";

    for(auto &i : l2){
        std::cout << i << " it works!\n";
    }
    return 0;
}