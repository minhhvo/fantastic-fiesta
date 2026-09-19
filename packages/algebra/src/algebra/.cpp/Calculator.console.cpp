// @file: Calculator.console.cpp

#include <iosfwd>
#include <iostream>

#include <bits/std_thread.h>
#include <bits/types/cookie_io_functions_t.h>
#include <stdexcept>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "Calculator.hpp"

namespace ErrorReporter {
    // Intercepts specific exception types and formats standard user messages
    void handleException(const std::exception& e) {
        std::string errorMsg = e.what();
        
        if (errorMsg.find("Syntax") != std::string::npos) {
            std::cerr << "[SyntaxError]: " << errorMsg << "\n\n";
        } 
        else if (errorMsg.find("Domain") != std::string::npos) 
        {
            std::cerr << "[MathError]: " << errorMsg << "\n\n";
        } 
        else 
        {
            std::cerr << "[InputError]: " << errorMsg << "\n\n";
        }
    }
}

void endProcess (int signum)
{
    std::cout << "\nInterrupt signal (" << signum << ") received. Exiting gracefully..." << std::endl;
    exit(0);
}

int main(void)
{
#ifdef SIGQUIT
    signal(SIGQUIT, endProcess);
#endif
    signal(SIGINT, endProcess);
    
    
    BaseCalculator c;
    std::string cmd_line;
    
    /* === CONSOLE APPLICATION HEADER === */
    std::cout << "Calculator Console Application\n" << std::endl;
    std::cout << "Enter any expression to start\n\n"<< "To exit, enter 'quit' or 'Q'." << std::endl;
    std::cout << "Press 'Ctrl + \\' (Linux) or 'Ctrl + C (Windows)' to force quit." << std::endl << std::endl;


    while (true)
    {   
        
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
                
                std::cout << "> [Enter]: ";
            } catch (const std::invalid_argument& e)
            { ErrorReporter::handleException(e); }
        }
        else if (!cmd_line.empty()) 
        {
            std::cerr << "Syntax Error: Please format as [number] [operator] [number]." << std::endl;
            std::cout << "> [Enter]: ";
        }

    } // end while-loop
    
    return 0;
}