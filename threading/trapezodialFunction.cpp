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

void trap(std::function<double(double)> f, double start, double end, size_t iterations, std::shared_ptr<double> p){
    //get thread number
    auto my_rank = omp_get_thread_num();
    //get number of threads
    auto thread_count = omp_get_num_threads();
    //calculation for iteration slice size
    auto slice_size = (end-start)/iterations;
    //calculate number of iterations per thread
    auto iterations_thread = iterations/thread_count;
    //calculate this thread's stat point
    auto local_start = start + ((my_rank*iterations_thread) * slice_size);
    //calculate this thread's end point
    auto local_end = local_start + iterations_thread * slice_size;
    //calculate initial result
    auto my_result = (f(local_start) + f(local_end)) / 2.0;

    //declare x before the lop - stops it being allocated and destroyed each iteration
    double x;
    //sum each iteration
    for (size_t i =0; i<=iterations_thread-1;++i){
        //calculate next slice to calculate
        x = local_start + i *slice_size;
        //add to current result
        my_result += f(x);
    }
    //multiply the result by the slice size
    my_result *= slice_size;

    //critical section - add to the shared data
#pragma omp critical
    *p += my_result;

}

int main(int argc, char **argv){
    //declare shared result
    auto result = std::make_shared<double>(0.0);
    //define start and end values
    auto start = 0.0;
    auto end = 3.14159265359; //pi
    //defined number of trapezoids to generation
    auto trapezoids = static_cast<size_t>(pow(2,24));
    //get number of threads
    auto thread_count = std::thread::hardware_concurrency();

    //create function to calculate itegral of. use cos
    auto f = [](double x){return sin(x);};

    //run trap in parallel
#pragma omp parallel num_threads(thread_count)
    trap(f, start, end, trapezoids, result);

    //output result
    std::cout << "Using " << trapezoids << " trapezoids. ";
    std::cout << "Estimated integral of function " << start << " to " << end << " = "<< *result << std::endl;

    return 0;
}