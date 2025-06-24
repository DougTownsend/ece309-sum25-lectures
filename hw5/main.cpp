#include "heap.hpp"
#include <chrono>

void test1(){
    int gold, silver, bronze;
    Heap h {10,9,5,8,6,7};
    h.top_three(gold, silver, bronze);
    std::cout << "Test 1:\nHeap: ";
    h.print();
    std::cout << "G/S/B: " << gold << " " << silver << " " << bronze << "\n";
    if(gold == 10 && silver == 9 && bronze == 8) std::cout << "Pass\n";
    else std::cout << "Fail\n";
}

void test2(){
    int gold, silver, bronze;
    Heap h {10};
    h.top_three(gold, silver, bronze);
    std::cout << "\nTest 3:\nHeap: ";
    h.print();
    std::cout << "G/S/B: " << gold << "\n";
    if(gold == 10) std::cout << "Pass\n";
    else std::cout << "Fail\n";
}

void test3(){
    int gold, silver, bronze;
    Heap h {10, 9};
    h.top_three(gold, silver, bronze);
    std::cout << "\nTest 3:\nHeap: ";
    h.print();
    std::cout << "G/S/B: " << gold << " " << silver << "\n";
    if(gold == 10 && silver == 9) std::cout << "Pass\n";
    else std::cout << "Fail\n";
}

void test4(){
    int gold, silver, bronze;
    Heap h {10, 9, 8 ,5, 4, 3};
    h.top_three(gold, silver, bronze);
    std::cout << "\nTest 4:\nHeap: ";
    h.print();
    std::cout << "G/S/B: " << gold << " " << silver << " " << bronze << "\n";
    if(gold == 10 && silver == 9 && bronze == 8) std::cout << "Pass\n";
    else std::cout << "Fail\n";
}

void test5(){
    int gold, silver, bronze;
    Heap h {11, 10, 6, 5, 4, 3, 2, 1, 0, 9};
    h.top_three(gold, silver, bronze);
    std::cout << "\nTest 5:\nHeap: ";
    h.print();
    std::cout << "G/S/B: " << gold << " " << silver << " " << bronze << "\n";
    if(gold == 11 && silver == 10 && bronze == 9) std::cout << "Pass\n";
    else std::cout << "Fail\n";
}

Heap random_heap(int size){
    Heap h;
    for(int i = 0; i < size; i++) h.insert(rand());
    return h;
}

void test_O1(){
    int gold, silver, bronze;
    std::cout << "\nChecking for O(1) time complexity.\nAll tests should take a similar amount of time.\n\n";

    std::cout << "Time elapsed for 5 heaps of size 10:\n";
    for(int i = 0; i < 5; i++){
        Heap h = random_heap(10);
        auto start = std::chrono::high_resolution_clock::now();
        h.top_three(gold, silver, bronze);
        auto end = std::chrono::high_resolution_clock::now();
        std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << " ns\n";
    }

    std::cout << "\nTime elapsed for 5 heaps of size 1,000:\n";
    for(int i = 0; i < 5; i++){
        Heap h = random_heap(1000);
        auto start = std::chrono::high_resolution_clock::now();
        h.top_three(gold, silver, bronze);
        auto end = std::chrono::high_resolution_clock::now();
        std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << " ns\n";
    }

    std::cout << "\nTime elapsed for 5 heaps of size 1,000,000:\n";
    for(int i = 0; i < 5; i++){
        Heap h = random_heap(1000000);
        auto start = std::chrono::high_resolution_clock::now();
        h.top_three(gold, silver, bronze);
        auto end = std::chrono::high_resolution_clock::now();
        std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << " ns\n";
    }
}

int main(){
    srand(time(NULL));
    test1();
    test2();
    test3();
    test4();
    test5();
    test_O1();
}