
#include "Calculator.hpp"
#include <cmath>

double BaseCalculator::calculate(double x, double y, char oper)
{
    switch (oper)
    {
        case '*': return x * y;

        case '+': return x + y;
        
        case '-': return x - y;
        
        case '/': 
            if (y == 0.0) throw std::domain_error("DomainError: Division by zero.");
            return x / y;
        
        case '^': return std::pow(x, y);

        default:
            throw std::invalid_argument(std::string("Unknown operator: ") + oper);
    
    }
}