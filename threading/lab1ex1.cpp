//
// Created by 40203 on 07/10/2018.
//

#include <random>
#include <vector>
#include <thread>
#include <iostream>

//vector to store 1000000 random numbers
//std::vector<size_t> numbers = std::make_shared<std::vector<size_t >>();

std::vector<size_t> task_one(){
    //creation of random seed
    std::random_device r;
    //generation of random number
    std::default_random_engine e(r());
    //loop to put random numbers into vector
    /*for(size_t i =0; i<1000000; ++i){
        numbers.emplace_back(e());
    }
    return numbers;*/
}

//task two to sort through to find max in vector from task one
size_t task_two(std::vector<size_t > t){
    //loop to go through vector t and sort for max
    for(size_t i =0; i<t.capacity();++i){
        if(t[i] > t[i+1]){
            std::swap(t[i], t[i+1]);
        }
    }
    return t.back();
}

//task three to sort through to find min in vector from task one
size_t task_three(std::vector<size_t > t){
    //loop to go through vector t and sort for min
    for(size_t i =0; i<t.capacity();++i){
        if(t[i] < t[i+1]){
            std::swap(t[i], t[i+1]);
        }
    }
    return t.back();
}

int main(){
    std::cout << "generating vector with 1000000 random values" << std::endl;
    std::thread t1(task_one);
    t1.join();
    std::cout << "finding max in the vector" << std::endl;
    std::thread t2(task_two(task_one()));
    std::cout << "finding min in the vector" << std::endl;
    std::thread t3(task_three(task_one()));
    t2.join();
    t3.join();

    return 0;
}