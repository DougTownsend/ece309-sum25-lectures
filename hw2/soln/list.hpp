#include <iostream>
#include <string>
#include <memory>

#ifndef LIST_HPP
#define LIST_HPP

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
            if(p) p = p->next;
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

    //Task 1:
    iterator sorted_insert(std::string s){
        auto n = head;
        std::shared_ptr<ListNode> newnode(new ListNode);
        newnode->item = s;
        if(!head || s < head->item){
            if(!head) tail = newnode;
            newnode->next = head;
            head = newnode;
        } else {
            while(n->next && s > n->next->item) n = n->next;
            if(!n->next) tail = newnode;
            newnode->next = n->next;
            n->next = newnode;
        }
        return iterator(newnode);
    }

    //Task 2:
    iterator insert_after(iterator pos, std::string s){
        std::shared_ptr<ListNode> newnode(new ListNode);
        newnode->item = s;
        auto n = head;
        if(!pos.p){
            if(!head) tail = newnode;
            newnode->next = head;
            head = newnode;
        } else {
            n = pos.p;
            if(!n->next) tail = newnode;
            newnode->next = n->next;
            n->next = newnode;
        }
        return iterator(newnode);
    }

    //Task 3:
    iterator find(std::string s){
        auto n = head;
        while(n && n->item != s) n = n-> next;
        return iterator(n);
    }

    //Task 4:
    iterator erase(iterator pos){
        auto n = head;
        if(!pos.p || empty()) return iterator(nullptr);
        else if(pos.p == head){
            if(tail == head) tail = nullptr;
            head = head->next;
            return iterator(head);
        } else {
            while(n->next && n->next != pos.p) n = n->next;
            if (n->next == tail) tail = n;
            n->next = n->next->next;
            return iterator(n->next);
        }
    }
};

#endif