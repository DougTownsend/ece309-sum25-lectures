#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <list>
#include <stdlib.h>

class Heap{
    public:
    std::vector<int> v;
    void percolate_up(int idx){
        while(idx > 0){
            int parent = (idx-1) / 2;
            if(v[idx] > v[parent]){
                std::swap(v[idx], v[parent]);
                idx = parent;
            } else{
                return;
            }
        }
    }

    void percolate_down(int idx){
        int val = v[idx];
        int child = idx*2 + 1;
        while(child < v.size()){
            int max = val;
            int max_idx = -1;
            for(int i = child; i <= child+1 && i < v.size(); i++){
                if(v[i] > max){
                    max = v[i];
                    max_idx = i;
                }
            }
            if(max == val) return;
            std::swap(v[idx], v[max_idx]);
            idx = max_idx;
            child = idx*2 + 1;
        }  
    }

    public:
    void insert(int i){
        v.push_back(i);
        percolate_up(v.size()-1);
    }

    void make_heap(){
        int n = v.size()-1;
        n = (n-1)/2;
        while(n >= 0){
            percolate_down(n);
            n--;
        }
    }

    int remove(){
        int ret;
        std::swap(v[0], v[v.size()-1]);
        ret = v.back();
        v.pop_back();
        percolate_down(0);
        return ret;
    }

    bool is_heap(){return std::is_heap(v.begin(), v.end());}

    void print(){
        for (auto &i : v){
            std::cout << i << "\n";
        }
    }

    bool empty(){
        return v.empty();
    }
};

int main(){
    Heap h;
    std::list<int> l;
    for(int i = 0; i < 6; i++){
        h.v.push_back(rand());
    }
    h.print();
    std::cout << "is heap: " << h.is_heap() << "\n\n";
    h.make_heap();
    std::cout << "is heap: " << h.is_heap() << "\n\n";

    while(!h.empty()){
        l.push_front(h.remove());
    }

    for(auto i : l) std::cout << i << "\n";
}