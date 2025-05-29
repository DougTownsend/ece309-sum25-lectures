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
        friend class List;
        std::shared_ptr<ListNode> p;
        std::string& operator*(){return p->item;}
        iterator& operator++(){
            p = p->next;
            return *this;
        }
        bool operator==(const iterator& other) {return other.p == p;}
        bool operator!=(const iterator& other) {return other.p != p;}
        private:
        iterator(std::shared_ptr<ListNode> n = nullptr) : p(n){}
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

    void insert_after(int pos, std::string s){
        auto newnode = std::make_shared<ListNode>();
        newnode->item = s;
        if(pos <= 0 || !head){
            newnode->next = head;
            if(tail == head) tail = newnode;
            head = newnode;
        } else {
            auto n = head;
            for(int i = 0; i < pos-2 && n->next; n = n->next);
            newnode->next = n->next;
            n->next = newnode;
            if(!newnode->next) tail = newnode;
        }
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
    l.insert_after(1, "peppers");
    l.insert_after(5, "tofu");
    l.print();
    cout << "\n";
    return 0;
}