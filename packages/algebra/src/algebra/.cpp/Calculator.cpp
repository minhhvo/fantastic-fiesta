
#include "Calculator.hpp"

#include <cmath>
#include <functional>

// void alt_check_denominator(int& denominator)
// {   /* @variant */ 
//     if (denominator > 0) { 
//         cout << denominator << endl; 
//     } else { std::cout << stderr << endl; }
// }

// void check_denominator(int& denominator)
// /* @overload 1 */
// { assert(denominator > 0); cout << denominator << endl; }

// void check_denominator(double& denominator) 
// /* @overload 2 */
// { assert(denominator > 0); cout << denominator << endl; }


// void check_denominator(float& denominator) 
// /* @overload 3 */
// { assert(denominator > 0.0); cout << denominator << endl; }
// void check_denominator(auto& denominator)
// /* @autocast typing*/
// { assert(denominator > 0);  }

BaseCalculator::BaseCalculator() 
{
    operations['+'] = [](double x, double y) { return x + y; };
    operations['-'] = [](double x, double y) { return x - y; };
    operations['*'] = [](double x, double y) { return x * y; };
    operations['/'] = [](double x, double y) {
        if (y == 0.0) 
        {
            throw std::domain_error("Domain Error: Division by zero.");
            return double INFINITY;
        } else { return x / y; }
    };
}

void BaseCalculator::registerOperator(char oper, std::function<double(double, double)> func)
{
    operations[oper] = func;
}

double BaseCalculator::calculate(double x, double y, char oper)
{
    auto it = operations.find(oper);
    if (it != operations.end()) 
    {
        return it->second(x, y); // Execute the lambda
    }
    throw std::invalid_argument("SyntaxError: Unknown operator.");
}

