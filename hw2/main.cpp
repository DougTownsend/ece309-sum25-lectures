#include "list.hpp"
#include <vector>

int main(){
    //Task 1: sorted_insert
    std::cout << "Task 1\n";
    List l;
    int score = 0.0;
    l.sorted_insert("milk");
    l.sorted_insert("eggs");
    auto i = l.sorted_insert("lettuce");
    l.sorted_insert("tomatoes");
    l.sorted_insert("apples");
    if (i.p == nullptr || *i != "lettuce"){
        std::cout << "Return iterator incorrect. Return an iterator pointing to the inserted element.\n";
    } else {
        score += 2;
    }
    std::vector<std::string> sorted = {"apples", "eggs", "lettuce", "milk", "tomatoes"};
    bool correct = true;
    int idx = 0;
    if(l.empty()){
        std::cout << "List is empty.\n";
        correct = false;
    }
    for(auto &s : l){
        //std::cout << s <<"\n" <<sorted[idx] << "\n\n";
        if(s != sorted[idx]){
            std::cout << "Element " << idx << " is " << s << ". Should be " << sorted[idx] << ".\n";
            correct = false;
        }
        idx++;
    }
    if(idx != 5){
        correct = false;
        std::cout << "Incorrect number of elements in list.\n";
    }
    if(correct)
        score += 13;
    std::cout << "Task 1 score: " << score << "/15.\n\n";

    //Task 2: insert_after
    std::cout << "Task 2:\n";
    List l2;
    l2.push_back("peppers");
    l2.push_back("tofu");
    l2.push_back("bread");
    l2.push_back("oranges");
    l2.push_back("onions");
    l2.push_back("rice");
    int task2_score = 0;
    auto it = l2.begin();
    l2.insert_after(it, "garlic");
    ++++it;
    l2.insert_after(it, "beans");
    it.p = nullptr;
    l2.insert_after(it, "potatoes");
    it = l2.begin();
    while(it.p->next != nullptr) ++it;
    l2.insert_after(it, "hummus");
    l2.push_back("blueberries");
    std::vector<std::string> t2_correct = {"potatoes", "peppers", "garlic", "tofu", "beans", "bread", "oranges", "onions", "rice", "hummus", "blueberries"};
    correct = true;
    idx = 0;
    if(l2.empty()){
        std::cout << "List is empty.\n";
        correct = false;
    }
    for(auto &s : l2){
        //std::cout << s <<"\n" <<t2_correct[idx]<<"\n\n";
        if(s != t2_correct[idx]){
            std::cout << "Element " << idx << " is " << s << ". Should be " << t2_correct[idx] <<".\n";
            correct = false;
        }
        idx++;
    }
    if(correct){
        task2_score = 15;
    }
    score += task2_score;
    std::cout << "Task 2 score: " << task2_score << "/15.\n\n";

    //Task 3:
    std::cout << "Task 3:\n";
    List l3;
    l3.push_back("peppers");
    l3.push_back("tofu");
    l3.push_back("bread");
    l3.push_back("oranges");
    l3.push_back("onions");
    l3.push_back("rice");
    std::vector<List::iterator> t3_correct;
    std::vector<std::string> t3_strings = {"peppers", "tofu", "bread", "oranges", "onions", "rice"};
    for(auto it = l3.begin(); it != l3.end(); ++it){
        t3_correct.push_back(it);
    }
    correct = true;
    for(size_t i = 0; i < t3_correct.size(); i++){
        auto it = l3.find(t3_strings[i]);
        if(it != t3_correct[i]){
            correct = false;
            if(it.p)
                std::cout << "l3.find(\"" << t3_strings[i] << "\"); returned an iterator pointing to \"" << *it << "\"\n";
            else
                std::cout << "Correct node address: " << t3_correct[i].p << "\nFound node address: " << it.p << "\n";
        }
    }
    auto t3_it = l3.find("broccoli");
    if (t3_it.p){
        correct = false;
        std::cout << "Return iterator with nullptr if not found (l3.end())\n";
    }
    int task3_score = 0;
    if(correct){
        task3_score = 15;
    }
    score += task3_score;
    std::cout << "Task 3 score: " << task3_score << "/15.\n\n";

    //Task 4:
    std::cout << "Task 4:\n";
    List l4;
    l4.push_back("peppers");
    l4.push_back("tofu");
    l4.push_back("bread");
    l4.push_back("oranges");
    l4.push_back("onions");
    l4.push_back("rice");
    std::vector<List::iterator> retvals;
    std::vector<List::iterator> t4_correct_retvals;
    std::vector<std::string> t4_strings = {"tofu", "bread", "onions", "broccoli"};
    auto t4_it = l4.erase(l4.begin());
    retvals.push_back(t4_it);
    ++++t4_it;
    retvals.push_back(l4.erase(t4_it));
    t4_it = retvals[1];
    ++t4_it;
    retvals.push_back(l4.erase(t4_it));
    l4.push_back("broccoli");
    idx = 0;
    correct = true;
    for(auto &s : l4){
        if(s != t4_strings[idx]){
            correct = false;
            if(idx < 4)
                std::cout << "Element " << idx << " is " << s << ". Should be " << t4_strings[idx] <<".\n";
            else
                std::cout << "Element " << idx << " is " << s << ". Should be nothing.\n";
        }
        idx++;
    }
    if(idx != 4){
        correct = false;
        std::cout << "Incorrect number of elements in list.\n";
    }
    int task4_score = 0;
    if(correct) task4_score = 15;
    std::cout << "Task 4 score: " << task4_score << "/15.\n\n";
    score += task4_score;
    std::cout << "Total score: " << score << "/60.\n";

    return 0;
}