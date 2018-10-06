//
// Created by 40203 on 02/10/2018.
//

#include <vector>
#include <random>
#include <fstream>
#include <iostream>
#include <chrono>
#include <thread>

//generates a vector of random values
std::vector<unsigned int> generate_values(size_t size){
    //create random engine
    std::random_device r;
    std::default_random_engine e(r());
    //generate random numbers
    std::vector<unsigned int> data;
    for (size_t i = 0; i<size; ++i){
        data.push_back(e());
    }

    return data;
}

void bubble_sort(std::vector<unsigned int> &data){
    for (size_t count = data.size(); count >= 2; --count){
        for (int i = 0; i<count-1; ++i){
            if(data[i] > data[i+1]){
                std::swap(data[i], data[i+1]);
            }
        }
    }
}

void parallel_sort(std::vector<unsigned int>&values){
    //get the number of threads
    auto num_threads = std::thread::hardware_concurrency();
    //get the number of elements in the vector
    auto n = values.size();
    //declare the variables used in the loop
    int i, tmp, phase;
    //declare parallel section
#pragma omp parallel num_threads(num_threads) default(none) shared(values, n) private(i, tmp, phase)
    for (phase = 0; phase<n;++phase){
        //determine which phase of the sort we are in
        if(phase %2 ==0){
            //parallel for loop. each thread jumps forward 2 so no conflict
#pragma omp for
            for (i=1; i<n;i +=2){
                //check if we should swap values
                if(values[i-1] > values[i]){
                    //swap values
                    tmp = values[i-1];
                    values[i-1] = values[i];
                    values[i] = tmp;
                }
            }
        }
        else{
            //parallel for loop. each thread jumps forward 2 so no conflict
#pragma omp for{
            for (i=1;i<n; i+=2){
                //check if we should swap values
                if(values[i] > values[i+1]){
                    //swap values
                    tmp = values[i+1];
                    values[i+1] = values[i];
                    values[i] = tmp;
                }
            }
        }
        }
    }
}

int main(){
    //create results file
    std::ofstream results("bubble.csv", std::ofstream::out);
    //gather results for 2^8 to 2^16 results
    for (size_t size = 8; size <=16; ++size){
        //output data size
        results << pow(2, size) << ", ";
        //gather 100 results
        for(size_t i =0;i<100; ++i){
            //generate vector of random values
            std::cout << "generating " << i<< " for " << pow(2, size) << " values" <<std::endl;
            auto data = generate_values(static_cast<size_t>(pow(2,size)));
            //sort the vector
            std::cout << "sorting" << std::endl;
            auto start = std::chrono::system_clock::now();
            bubble_sort(data);
            auto end = std::chrono::system_clock::now();
            auto total = std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();
            //output time
            results << total<<",";
        }
        results<<std::endl;
    }
    results.close();

    return 0;


}