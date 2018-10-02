//
// Created by Dylan on 01/10/2018.
//
#include <iostream>
#include <vector>
#include <random>
#include <cmath>
#include <chrono>
#include <thread>
#include <fstream>
#include <future>
#include <thread>
#include <vector>
#include

//number of iterations to perform to find pixel value
constexpr size_t max_iterations = 1000;

//dimension of the image (in pixels) to generate
const size_t dim = 8192;

//mandlebrot dimensions are ([-2.1,1.0], [-1.3, 1.3])
constexpr double xmin = -2.1;
constexpr double xmax = 1.0;
constexpr double ymin = -1.3;
constexpr double ymax = 1.3;

//the conversion from mandlebrot coordinate to image coordinate
constexpr double integral_x = (xmax - xmin) / static_cast<double>(dim);
constexpr double integral_y = (ymax - ymin) / static_cast<double>(dim);

std::vector<double> mandelbrot(size_t start_y, size_t end_y){
    //declare values we will use
    double x, y, x1, y1, xx = 0.0;
    size_t loop_count = 0;
    //where to store the results
    std::vector<double> results;

    //loop through each line
    y = ymin + (start_y * integral_y);
    for(size_t y_coord = start_y; y_coord < end_y; ++y_coord){
        x = xmin;
        //loop through each pixel on the line
        for(size_t x_coord = 0; x_coord < dim; ++x_coord){
            x1 = 0.0, y1 = 0.0;
            loop_count = 0;
            //calculate mandelbrot value
            while (loop_count < max_iterations && sqrt((x1*x1) + (y1*y1)) < 2.0){
                ++loop_count;
                xx = (x1*x1) - (y1*y1) + x;
                y1 = 2 *x1*y1+y;
                x1 = xx;
            }
            //get value where loop completed
            auto val = static_cast<double>(loop_count) / static_cast<double>(max_iterations);
            //push this value onto the vector
            results.push_back(val);
            //increase x based on itegral
            x += integral_x;
        }
        //increase y based on integral
        y += integral_y;
    }
    //return vector
    return results;
}

int main(){
    //get the number of supported threads
    auto num_threads = std::thread::hardware_concurrency();

    //determine strip height
    size_t strip_height = dim / num_threads;

    //create futures
    std::vector<std::future<std::vector<double>>> futures;
    for (unsigned int i =0; i < num_threads; ++i){
        //range is used to determine number of valeus to process
        futures.push_back(async(mandelbrot, i * strip_height, (i+1) * strip_height));

        //vector to store results
        std::vector<std::vector<double>> results;
        //get results
        for(auto &f : futures){
            results.push_back(f.get());
        }

        return 0;
    }
}