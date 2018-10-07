//
// Created by 40203 on 07/10/2018.
//

#include <chrono>
#include <thread>
#include <iostream>

void task_one(){
    std::cout << "task one starting " << std::endl;
    std::cout << "task one sleeping for 3 seconds" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(3));
    std::cout << "task one awake again" << std::endl;
    std::cout << "task one sleeping for 5 seconds" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    std::cout << "task one awake again" << std::endl;
    std::cout << "task one ending" << std::endl;
}

void task_two(){
    std::cout << "task two starting" << std::endl;
    std::cout << "task two sleeping for 2 seconds" << std::endl;
    std::this_thread::sleep_for(std::chrono::microseconds(2000000));
    std::cout << "task two awake again" << std::endl;
    std::cout << "task two sleeping for 10 seconds" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(10));
    std::cout << "task two awake again" << std::endl;
    std::cout << "task two ending" << std::endl;
}

int main(){
    std::cout << "starting task one" << std::endl;
    std::thread t1(task_one);
    std::cout << "starting task two" << std::endl;
    std::thread t2(task_two);
    std::cout << "joining task one" << std::endl;
    t1.join();
    std::cout << "task one joined" << std::endl;
    std::cout << "joining task two" << std::endl;
    t2.join();
    std::cout << "task two joined"<< std::endl;
    std::cout << "exiting"<< std::endl;
    return 0;
}
