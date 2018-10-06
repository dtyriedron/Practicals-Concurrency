//
// Created by 40203 on 06/10/2018.
//
#include <vector>
#include <random>
#include <fstream>
#include <iostream>
#include <chrono>
#include <thread>
#include <functional>
#include <omp.h>

//lets create a function that relies on i to determine the amount of work
double f(unsigned int i){
    //calculate start and end values
    auto start = i * (i+1)/2;
    auto end = start +i;
    //declare return value
    auto result = 0.0;

    //loop for number of iterations, calculating sin
    for(auto j = start; j<=end; ++j){
        result +=sin(j);
    }

    //return result
    return result;
}

int main(int argc, char **argv){
    //get number pf hardware threads
    auto thread_count = std::thread::hardware_concurrency();
    //define number of iterations to calculate
    auto n = static_cast<size_t>(pow(2, 14));
    //declare sum value
    auto sum = 0.0;

    //get start time
    auto start = std::chrono::system_clock::now();
#pragma omp parallel for num_threads(thread_count) reduction(+:sum) schedule(static, 2)
    for(auto i =0; i<=n; ++i){
        sum+= f(i);
    }
    //get end time
    auto end = std::chrono::system_clock::now();
    //calculate and output time
    auto total = std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();
    std::cout << "Total time: " << total << "ms" << std::endl;

    return 0;
}