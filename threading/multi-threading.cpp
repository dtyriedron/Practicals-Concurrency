//
// Created by 40203 on 07/10/2018.
//

#include <thread>
#include <iostream>

/*
 * this is the function called by the thread
 */
void hello_world(){
    std::cout << "Hello from thread " << std::this_thread::get_id() << std::endl;
}

int main(){
    //create a new thread
    std::thread t(hello_world);
    //wait for thread to finish
    t.join();
    //return 0
    return 0;
}