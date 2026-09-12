#pragma once

#include <cmath>

#include <cstdio>
#include <cstring>
#include <cassert>

#include <string>

#include <stdlib.h> 
#include <cstdlib>
#include <cmath>

#include <functional>

#include <unordered_map>

#include "MathLibrary.hpp"

// /* @size: 8-bytes */
// union binary_operand_t { int32_t n; float_t f; double_t d; };

// // enum operator_char 
// // {
// //     multiply = '*',
// //     plus = '+',
// //     minus = '-',
// //     divide = '/'
// // };

// /* Additive Operator */
// template<std::plus<void>, typename T> 
// void plus (T a, T b) { return a + b; }
// template<std::plus<void>, typename T> 
// void add (T a, T b) { return a + b; }

// /* @Multiplicative Operator */
// template<std::multiplies<void>, typename T> 
// void multiplies (T a, T b) { return a * b; }
// template<std::multiplies<void>, typename T> 
// void multiply (T a, T b) { return a * b; }
// template<std::multiplies<void>, typename T> 
// void mul (T a, T b) { return a * b; }

// /* @Subtractive Operator */
// template<std::minus<void>, typename T> 
// void minus (T a, T b) { return a - b; }
// template<std::minus<void>, typename T> 
// void substract (T a, T b) { return a - b; }
// template<std::minus<void>, typename T> 
// void sub (T a, T b) { return a - b; }
// template<std::minus<void>, typename T> 
// void delta (T a, T b) { return a - b; }

// /* @Quotient Operator */
// // These functionals need to be specialised/revamped to handle domain and logic errors;
// // such as: division-by-zero, inputs of type int but the result is indivisible (does the caller want the ratiometric or floating-point casted return)
// template<std::divides<void>, typename T> 
// void divides (T a, T b) { return a / b; }
// template<std::divides<void>, typename T> 
// void divide (T a, T b) { return a / b; }
// template<std::divides<void>, typename T> 
// void div (T a, T b) { return a / b; }

// template<std::divides<void>, typename T1, typename T2>
// void divides (T1 a, T2 b) 
// { 
// // delegate and pass the parameters to ratio_divide and return 
// int *fptr = std::ratio (&a, &b);

// }

class BaseCalculator
{
std::unordered_map<char, std::function<double(double, double)>> operations;

public:
    BaseCalculator();
    void registerOperator(char oper, std::function<double(double, double)> func);

    double calculate(double x, double y, char oper);
};

#if __has_include(<format>)
#include <format>
#define HAS_FORMAT 1
#else
#include <sstream>
#define HAS_FORMAT 0
#endif

class MathExpression
{   
private:
    double x;
    double y;
    char oper;
        

    std::string to_string() const 
    {   
    #if HAS_FORMAT
        return std::format("{} {} {}", x, oper, y);
    #else
        std::ostringstream oss;
        
        oss << x << '\t' << oper << '\t' << y << '\t';
        return oss.str();
    #endif
    };

public:
    std::string expression_string;

    MathExpression(double x_in, double y_in, char oper_in)
        : x(x_in), y(y_in), oper(oper_in)
        {  expression_string = to_string(); }
    ~MathExpression (void) = default;
};

class Calculator
{
public:
    Calculator();
    void calculate(double x, double y, char oper)
    {
        switch (oper)
        {
            case '*': // value = 42 (0x2a)
                MathLibrary::Arithmetic::Multiply(x, y); break;

            case '+': // value = 43 (0x2b)
                MathLibrary::Arithmetic::Add(x, y); break;
            
            case '-': // value = 45 (0x2d)
                MathLibrary::Arithmetic::Subtract(x, y); break;
            
            case '/': // value = 47 (0x2f)
                MathLibrary::Arithmetic::Divide(x, y); break;
        };
    }
};
