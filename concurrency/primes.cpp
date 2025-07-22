#include <iostream>
#include <cstdint>
#include <cmath>
#include <thread>
#include <atomic>
#include <vector>
#include <algorithm>
#include <mutex>
#include <barrier>

const int num_threads = 8;
std::vector<uint64_t> primes;
std::mutex mtx;

bool is_prime(uint64_t n){
    for(uint64_t i = 3; i*i <= n; i+=2){
        if(n % i == 0){
            return false;
        }
    }
    return true;
}

void find_primes(int tid, uint64_t n){
    for(int i = 3+2*tid; i < n; i+=2*num_threads){
        if(is_prime(i)){
            mtx.lock();
            primes.push_back(i);
            mtx.unlock();
        }
    }
}

int prime_counting_func(uint64_t n){
    return n / log(n);
}

void find_primes_slow(uint64_t stop){
    std::vector<std::jthread> threads;
    for(int i = 0; i < num_threads; i++){
        threads.emplace_back(find_primes, i, stop);
    }
}

std::vector<uint64_t> thread_primes[num_threads];
std::barrier bar(num_threads);
uint64_t highest_squared;
uint64_t current_start;

void find_primes_fast(int tid, uint64_t stop){
    bool done = false;
    bool t0_done = false;
    while(!done || tid == 0){
        if(tid == 0){
            size_t idx = primes.size();
            for(int i = 0; i < num_threads; i++){
                primes.insert(primes.end(),
                    thread_primes[i].begin(), thread_primes[i].end());
                thread_primes[i].clear();
            }
            auto it = primes.begin() + idx;
            std::sort(it, primes.end());
            current_start = primes.back() + 2;
                
            highest_squared = primes.back()*primes.back();
            if(t0_done){
                break;
            }
        }
        bar.arrive_and_wait();
        bool local_is_prime = true;
        for(uint64_t i = current_start + (2*tid); i < highest_squared; i += 2*num_threads){
            local_is_prime = true;
            if(tid == 2){
                std::cout << i << "\n";
            }
            if(i >= stop){
                done = true;
                t0_done = true;
                break;
            }
            for(auto &j : primes){
                if(i % j == 0){
                    local_is_prime = false;
                    break;
                }
            }
            if(local_is_prime){
                thread_primes[tid].push_back(i);
            }
        }
        bar.arrive_and_wait();
    }
}

int main(){
    //Find primes under 1000
    primes.push_back(2);
    find_primes_slow(1000);
    std::sort(primes.begin(), primes.end());

    std::vector<std::jthread> threads;
    for(int i = 0; i < num_threads; i++){
        threads.emplace_back(find_primes_fast, i, 1500000);
    }
    for(auto &t : threads){
        t.join();
    }
    std::cout << primes.size() << "\n";
    return 0;
}