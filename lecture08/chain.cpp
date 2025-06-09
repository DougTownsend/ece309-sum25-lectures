#include <vector>
#include <iostream>
#include <list>

class Hash{
    private:
    std::vector<std::list<int>> table;
    int num_buckets;

    public:
    Hash(int n_buckets) : num_buckets(n_buckets){
        table.resize(n_buckets);
    }

    int hash(int key){
        return key % num_buckets;
    }

    bool insert(int key){
        int idx = hash(key);
        for(auto i : table[idx]){
            if (i == key) return false;
        }
        table[idx].push_back(key);
        return true;
    }

    bool search(int key){
        int idx = hash(key);
        for(auto i : table[idx]){
            if (i == key) return true;
        }
        return false;
    }

    bool remove(int key){
        int i = hash(key);
        for(auto it = table[i].begin(); it != table[i].end(); ++it){
            if(*it == key){
                table[i].erase(it);
                return true;
            }
        }
        return false;
    }
};


int main(){
    Hash h(10);
    h.insert(14);
    h.insert(24);
    std::cout << h.insert(4) << "\n" <<
    h.insert(1235) << "\n" <<
    h.insert(3454) << "\n" <<
    h.insert(1) << "\n" <<
    h.insert(120000000) << "\n";

    std::cout <<"search\n" <<
    h.search(123) << "\n" <<
    h.search(3454) << "\n" <<
    h.search(1235) << "\n" <<
    h.search(4) << "\n";

    std::cout <<"removing 4\n" << h.remove(4) << "\n" << h.search(4) << "\n";
    return 0;
}