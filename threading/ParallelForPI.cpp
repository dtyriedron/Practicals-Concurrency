//
// Created by 40203 on 02/10/2018.
//

#include <omp.h>
#include <thread>
#include <cmath>
#include <iostream>

int main(){
    //get the number of supported threads
    auto num_threads = std::thread::hardware_concurrency();

    //number of iteration values to perform
    const int n = static_cast<int>(pow(2,30));
    //factor value
    double factor = 0.0;
    //calculated pi
    double pi = 0.0;

    //parallelised for loop that does the work
#pragma omp parallel for num_threads(num_threads) reduction(+:pi) private(factor)
    for(int k = 0; k<n;++k){
        //determine sign of factor
        if(k%2==0){
            factor = 1.0;
        }
        else{
            factor = -1.0;
        }
        //add this iteration value to pi sum
        pi += factor / (2.0 * k+1);
    }

    //get the final value of pi
    pi *= 4.0;

    //show more precision of pi
    std::cout.precision(std::numeric_limits<double>::digits10);
    std::cout << "pi = " << pi <<std::endl;

    return 0;
}