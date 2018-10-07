//
// Created by 40203 on 07/10/2018.
//

#include <vector>
#include <random>
#include <iostream>
#include <thread>
#include <functional>

int main() {
    auto add = [](int x, int y) { return x + y; };
    //call the defined function
    auto x = add(10, 12);
    //display answer - should be 22
    std::cout << "10 + 12 = " << x << std::endl;
    
    //create function object with with same lmbda expression
    std::function<int(int, int)> add_function = [](int x, int y) {return x+y;};
    //call the function object
    x = add_function(20,12);
    //display the answer - should be 32
    std::cout << "20+12 = " << x << std::endl;
    
    int a = 5;
    int b = 10;
    //define the values passed to the function
    auto add_fixed = [a,b] { return a+b;};
    //call the function
    x= add_fixed();
    //display the answer - should be 15
    std::cout << "5+10 = " << x << std::endl;
    
    //change the values for a and b
    a = 20;
    b = 30;
    //call the fixed function again
    x = add_fixed();
    //display the answer should be 15
    std::cout << "20+30 = " << x <<std::endl;
    
    //define the values passed to the function, but pass as reference
    auto add_reference = [&a, &b] {return a+b;};
    //call the function
    x = add_reference();
    //display the answer should be 50
    std::cout << "20+30 = " << x <<std::endl;
    
    //change the values of a and b
    a = 30;
    b = 5;
    //call the reference based function again
    x = add_reference();
    //display the answer should be 35;
    std::cout << "30+5 = " << x <<std::endl;
    
    return 0;
}

