//
// Created by 40203 on 07/10/2018.
//

#include <thread>
#include <iostream>
#include <vector>
#include <random>
#include <chrono>

constexpr size_t num_threads = 100;

void task(size_t n, int val){
    std::cout << "Thread: " << n << " random value: " << val << std::endl;
}

int main(){
    //c++ style of creating a random
    //seed with real random number if available
    std::random_device r;
    //create random number generator
    std::default_random_engine e(r());

    //create 100 threads in a vector
    std::vector<std::thread> threads;
    for(size_t i =0; i < num_threads;++i) {
        threads.emplace_back(std::thread(task, i, e()));
    }

    //use c++ ranged for loop to join threads
    //same as foreach in c#
    for (auto &t :threads){
        t.join();
    }

    return 0;
}