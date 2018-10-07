//
// Created by 40203 on 07/10/2018.
//

#include <functional>
#include <thread>
#include <fstream>
#include <iostream>
#include <chrono>

void work(){
    //do some spinning - no actual processing but will make the cpu work
    int n =0;
    for (int i =0; i < 1000000; ++i){
        ++n;
    }
}

int main(){
    //create new file
    std::ofstream data("data.csv", std::ofstream::out);
    //we're going to gather 100 readings, so create a thread and join it 100 times
    for (int i =0; i<100;++i){
        //get start time
        auto start = std::chrono::system_clock::now();
        //start thread 
        std::thread t(work);
        t.join();
        //get end time
        auto end = std::chrono::system_clock::now();
        //calculate the duration
        auto total = end-start;
        //write to file
        data << total.count() << std::endl;
    }
    //100 iterations complete
    data.close();
    return 0;
}