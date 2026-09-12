#include "Calculator.hpp"

#include <bits/std_thread.h>
#include <bits/types/cookie_io_functions_t.h>
#include <cmath>

#include <cstdio>
#include <cstdlib>
#include <ctgmath>
#include <cassert>

#include <functional>
#include <iosfwd>
#include <iostream>

#include <stdexcept>
#include <sys/types.h>
#include <sys/wait.h>

#include <unistd.h>


using namespace std;

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
    throw std::invalid_argument("Syntax Error: Unknown operator.");
}

void endprocess (int signum)
{
    cout << "\nInterrupt signal (" << signum << ") received. Exiting gracefully..." << endl;
    exit(0);
}

int main(void)
{
#ifdef SIGQUIT
    signal(SIGQUIT, endprocess); 
#endif
    signal(SIGINT, endprocess);
    
    
    BaseCalculator c;
    string cmd_line;

    /* commented out because the interprocess pipes function are POSIX IPC that fail to compile on WINDOWS */
    // int (*fptr) (int, char**);   //declaring <function ptr>
    // fptr = &argparser;           // variable binding of <function ptr> to the function defined outside of main function.

    
    cout << "Calculator Console Application\n" << endl << endl;
    cout << "Enter any expression to start\n\n" << "\t'quit' or 'Q' to exit." << endl;
    cout << "Press 'Ctrl + \\' (Linux) or 'Ctrl + C (Windows)' to force quit." << endl << endl;


    while (true)
    {   
        cout << "> [Enter]: ";
        if (!getline(cin, cmd_line)) break;
        if (cmd_line == "quit" || cmd_line == "Q")
        {
            cout << "Exiting program..." << endl;
            exit(0);
        }

        istringstream stream (cmd_line);
        double l_operand, r_operand;
        char operation;
        double resultant;
        
        if (operation == '/' && r_operand == 0)
        {
            cout << INFINITY << endl;
            continue;
        } else if (stream >> l_operand >> operation >> r_operand) 
        {
            try {
            resultant = c.calculate(l_operand, r_operand, operation);
            // Display the full expression
            cout << l_operand << " " << operation << " " << r_operand << " = " 
            << resultant << endl << endl; 
            } catch (const invalid_argument& e)
            { cerr << e.what() << endl << endl; }
        }

    } // end while-loop
    return 0;
}