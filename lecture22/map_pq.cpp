#include <map>
#include <queue>
#include <string>
#include <iostream>

class prio_string{
    public:
    std::string s;
    int prio;

    prio_string(std::string s, int prio): s(s), prio(prio) {}

    bool operator<(const prio_string &other) const{
        return prio < other.prio;
    }
    bool operator>(const prio_string &other) const{
        return prio > other.prio;
    }
};

int main(){
    std::map<std::string, int> m;
    m["hello"] = 5;
    m["bye"] = 20;

    //for(auto i : m) std::cout << i.first << ": " << i.second << "\n";

    auto it = m.find("hello");
    if(it != m.end()){
        std::cout << "It is here! " << it->second << "\n";
    }

    std::priority_queue<prio_string, std::vector<prio_string>, std::greater<prio_string>> pq;
    pq.push({"hi", 10});
    pq.push({"hell1o", 5});
    pq.push({"hello", 5});
    pq.push({"hello2", 5});

    pq.push({"abc", 20});
    pq.push({"efg", 0});

    while(!pq.empty()){
        std::cout << pq.top().s << "\n";
        pq.pop();
    }
}