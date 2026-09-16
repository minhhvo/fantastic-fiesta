// @file TimeIt.cpp
#include "TimeIt.hpp"

void TimeIt::profile(const std::string& target_name, int iterations, std::function<void()> func) 
{
    auto start = std::chrono::high_resolution_clock::now();
    
    for (int i = 0; i < iterations; i++) 
    {
        func();
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> ms = end - start;
    
    std::cout << "[Profile: " << target_name << "] Time: " << ms.count() << " ms\n";
}