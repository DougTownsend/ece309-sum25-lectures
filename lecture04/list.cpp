#include <iostream>
#include <string>

class ListNode{
    public:
    ListNode *next;
    std::string item;

    ListNode(){
        next = nullptr;
        item = "";
    }
};

class List{
    private:
    ListNode *head;
    ListNode *tail;

    public:
    List(){
        head = nullptr;
        tail = nullptr;
    }

    bool empty(){
        return head == nullptr;
    }

    void push_back(std::string s){
        ListNode *n = new ListNode;
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
        ListNode *n = head;
        head = head->next;
        delete n;
        return copy;
    }

    void print(){
        ListNode *n = head;
        while(n){
            std::cout << n->item << "\n";
            n = n->next;
        }
    }
};

int main(){
    List l;
    l.push_back("milk");
    l.push_back("eggs");
    l.push_back("lettuce");
    l.push_back("tomatoes");
    l.push_back("apples");

    l.print();
    std::cout << "\n";
    std::string front = l.pop_front();
    l.print();

    std::cout << "\n";
    std::cout << front << "\n";
    return 0;
}