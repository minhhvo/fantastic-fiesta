#pragma once

#include <cmath>
#include <string>

class BaseCalculator
{
public:
    BaseCalculator() = default;
    ~BaseCalculator() = default;
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
    std::string expression;

    MathExpression(double x_in, double y_in, char oper_in)
        : x(x_in), y(y_in), oper(oper_in)
        {  expression = to_string(); }
    ~MathExpression (void) = default;
};
