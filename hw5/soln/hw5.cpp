#include "heap.hpp"

void Heap::top_three(int &gold, int &silver, int &bronze) const{
    if(v.size() > 0) gold = v[0];
    if(v.size() == 2) silver = v[1];
    else if(v.size() > 2) {
        int silver_idx;
        int bronze_idx;
        if (v[1] > v[2]){
            silver_idx = 1;
            bronze_idx = 2;
        }
        else {
            silver_idx = 2;
            bronze_idx = 1;
        }
        for(int i = silver_idx * 2 + 1; i <= silver_idx * 2 + 2 && i < v.size(); i++){
            if(v[i] > v[bronze_idx]) bronze_idx = i;
        }
        silver = v[silver_idx];
        bronze = v[bronze_idx];
    }
}