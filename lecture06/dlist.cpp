#include <iostream>
#include <string>
#include <memory>

class DList{
    private:
    class DListNode{
        public:
        std::shared_ptr<DListNode> next;
        std::shared_ptr<DListNode> prev;
        std::string item;

        DListNode(){
            next = nullptr;
            item = "";
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
        std::string& operator*(){return p->item;}
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

    iterator push_back(std::string s){
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

    iterator push_front(std::string s){
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

    std::string pop_front(){
        std::string copy = head->item;
        head = head->next;
        if(head)
            head->prev = nullptr;
        if (head == nullptr) tail = nullptr;
        return copy;
    }

    std::string pop_back(){
        std::string copy = tail->item;
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

    iterator insert_after(iterator it, std::string s){
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
    DList l;
    l.push_front("eggs");
    l.push_front("lettuce");
    l.push_back("apples");

    auto it = l.begin();
    l.insert_after(--it, "tofu");
    l.print();
    cout << "\n";
    l.print_rev();
    return 0;
}