#include <vector>
#include <iostream>

class Hash{
    private:
    struct Bucket{
        int data;
        bool empty;
        bool never_filled;
        Bucket() : empty(true), never_filled(true) {}
    };
    std::vector<Bucket> table;
    int num_buckets;

    public:
    class iterator{
        std::vector<Bucket>::iterator it;
        std::vector<Bucket>::iterator table_end;

        public:
        iterator(std::vector<Bucket>::iterator i, std::vector<Bucket>::iterator end) : it(i), table_end(end) {}
        
        const int& operator*(){
            return (*it).data;
        }

        iterator& operator++(){
            do{
                ++it;
            }while((*it).empty && it != table_end);
            return *this;
        }

        bool operator!=(const iterator& other){
            return it != other.it;
        }
    };

    iterator begin(){
        for(auto it = table.begin(); it != table.end(); ++it){
            if(!(*it).empty) return iterator(it, table.end());
        }
        return iterator(table.end(), table.end());
    }

    iterator end(){
        return iterator(table.end(), table.end());
    }

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
        int start_idx = idx;
        if(!table[idx].empty){
            do
                idx = (idx + 1) % num_buckets;
            while (!table[idx].empty && idx != start_idx);
            if(idx == start_idx) return false;
        }
        table[idx].data = key;
        table[idx].empty = false;
        table[idx].never_filled = false;
        return true;
    }

    bool search(int key){
        int i = hash(key);
        int start = i;
        while (!table[i].never_filled && table[i].data != key){
            i = (i + 1) % num_buckets;
            if(i == start) return false;
        }
        if(!table[i].never_filled && !table[i].empty && table[i].data == key) return true;
        else return false;
    }

    bool remove(int key){
        int i = hash(key);
        if(table[i].empty) return false;
        else if (table[i].data != key) return false;
        table[i].empty = true;
        return true;
    }
};
