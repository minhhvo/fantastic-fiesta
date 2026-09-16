
#include <iosfwd>
#include <iostream>

#include <bits/std_thread.h>
#include <bits/types/cookie_io_functions_t.h>
#include <stdexcept>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "Calculator.hpp"

void endprocess (int signum)
{
    std::cout << "\nInterrupt signal (" << signum << ") received. Exiting gracefully..." << std::endl;
    exit(0);
}


int main(void)
{
#ifdef SIGQUIT
    signal(SIGQUIT, endprocess); 
#endif
    signal(SIGINT, endprocess);
    
    
    BaseCalculator c;
    std::string cmd_line;

    /* commented out because the interprocess pipes function are POSIX IPC that fail to compile on WINDOWS */
    // int (*fptr) (int, char**);   //declaring <function ptr>
    // fptr = &argparser;           // variable binding of <function ptr> to the function defined outside of main function.

    
    std::cout << "Calculator Console Application\n" << std::endl;
    std::cout << "Enter any expression to start\n\n"<< "To exit, enter 'quit' or 'Q'." << std::endl;
    std::cout << "Press 'Ctrl + \\' (Linux) or 'Ctrl + C (Windows)' to force quit." << std::endl << std::endl;


    while (true)
    {   
        std::cout << "> [Enter]: ";
        if (!getline(std::cin, cmd_line)) break;
        if (cmd_line == "quit" || cmd_line == "Q")
        {
            std::cout << "Exiting program..." << std::endl;
            exit(0);
        }

        std::istringstream stream (cmd_line);
        double l_operand, r_operand;
        char operation;
        if (stream >> l_operand >> operation >> r_operand) 
        {
        
            if (operation == '/' && r_operand == 0)
            {
                std::cout << "INFINITY\n" << std::endl;
                continue;
            }

            try 
            {
                double result = c.calculate(l_operand, r_operand, operation);
                MathExpression expr(l_operand, r_operand, operation);
                
                // Display the full expression
                std::cout << expr.expression_string << "\t=\t" << result << std::endl << std::endl; 
            } catch (const std::invalid_argument& e)
            { std::cerr << e.what() << std::endl << std::endl; }
        }
        else if (!cmd_line.empty()) 
        {
            std::cerr << "Syntax Error: Please format as [number] [operator] [number]." << std::endl << std::endl;
        }

    } // end while-loop
    
    return 0;
}