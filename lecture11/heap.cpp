#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <stdlib.h>

class Heap{
    private:
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

    void percolate_down(){
        int val = v[0];
        int idx = 0;
        int child = idx*2 + 1;
        while(child < v.size()){
            if(child < v.size()-1){
                if(v[child] > v[child+1]){
                    std::swap(v[child], v[idx]);
                    idx = child;
                } else {
                    std::swap(v[child+1], v[idx]);
                    idx = child+1;
                }
            } else{
                if(v[idx] < v[child]) std::swap(v[idx], v[child]);
            }
        }  
    }

    public:
    void insert(int i){
        v.push_back(i);
        percolate_up(v.size()-1);
    }

    int remove(){
        int ret;
        std::swap(v[0], v[v.size()-1]);
        ret = v.pop_back();

    }

    bool is_heap(){return std::is_heap(v.begin(), v.end());}
    void print(){
        for (auto &i : v){
            std::cout << i << "\n";
        }
    }
};

int main(){
    Heap h;
    for(int i = 0; i < 6; i++){
        h.insert(rand());
    }
    h.print();
    std::cout << h.is_heap() << "\n";
}