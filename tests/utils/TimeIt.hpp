// @file TimeIt.hpp
#pragma once
#include <string>
#include <functional>
#include <type_traits>

#include <iostream>
#include <chrono>

template <class T>
inline void DoNotOptimize(const T& value) {
    // GCC/Clang specific instruction telling the compiler the memory was "read"
    asm volatile("" : : "r,m"(value) : "memory");
}

template <typename Func, typename... Args>
inline void ProtectedExec(Func&& f, Args&&... args)
{
    if constexpr (std::is_void_v<std::invoke_result_t<Func, Args...>>) 
    {
        std::forward<Func>(f)(std::forward<Args>(args)...);
    } else {
        auto result = std::forward<Func>(f)(std::forward<Args>(args)...);
        DoNotOptimize(result);
    }
}

// INLINE EXECUTION MACRO
#define PROFILE_EXECUTE(TargetFunc, Iterations, ...) \
    do { \
        auto start = std::chrono::high_resolution_clock::now(); \
        for (int i = 0; i < (Iterations); i++) { \
            ProtectedExec(TargetFunc, __VA_ARGS__); \
        } \
        auto end = std::chrono::high_resolution_clock::now(); \
        std::chrono::duration<double, std::milli> ms = end - start; \
        std::cout << "[Profile: " << #TargetFunc << "] Time: " << ms.count() << " ms\n"; \
    } while(0)

class TimeIt 
{
public:
    static void profile(const std::string& target_name, int iterations, std::function<void()> func);
};