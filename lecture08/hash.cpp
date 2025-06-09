#include <vector>
#include <iostream>

class Hash{
    private:
    struct Bucket{
        int data;
        bool empty;
        Bucket() : empty(true) {}
    };
    std::vector<Bucket> table;
    int num_buckets;

    public:
    Hash(int n_buckets) : num_buckets(n_buckets){
        table.resize(n_buckets);
        for (int i = 0; i < n_buckets; i++)
            table[i].empty = true;
    }

    int hash(int key){
        return key % num_buckets;
    }

    bool insert(int key){
        int idx = hash(key);
        if(!table[idx].empty) return false;
        table[idx].empty = false;
        table[idx].data = key;
        return true;
    }

    bool search(int key){
        int i = hash(key);
        if(table[i].empty) return false;
        else if (table[i].data != key) return false;
        return true;
    }

    bool remove(int key){
        int i = hash(key);
        if(table[i].empty) return false;
        else if (table[i].data != key) return false;
        table[i].empty = true;
        return true;
    }
};


int main(){
    Hash h(10);
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