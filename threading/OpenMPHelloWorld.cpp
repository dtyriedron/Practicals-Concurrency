//
// Created by 40203 on 02/10/2018.
//

#include <iostream>
#include <omp.h>

//number of threads to run
constexpr int THREADS = 10;

void hello(){
    //get the thread number
    auto my_rank = omp_get_thread_num();
    //get the number of threads in operation
    auto thread_count = omp_get_num_threads();
    //display a message
    std::cout << "hello from thread " << my_rank << " of " << thread_count << std::endl;

}

int main(){
    //run hello THREADS times
    #pragma omp parallel num_threads(THREADS)
    hello();

    return 0;
}