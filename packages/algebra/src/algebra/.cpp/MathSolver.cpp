#include "Calculator.hpp"
#include "ExpressionParser.hpp"

#include <iostream>
#include <csignal>


namespace ErrorReporter {
    // Intercepts specific exception types and formats standard user messages
    void handleException(const std::exception& e) 
    {
        std::string errorMsg = e.what();
        
        if (errorMsg.find("Syntax") != std::string::npos) 
        {
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
    
    std::cout << "Calculator Console Application\n" << std::endl << std::endl;
    std::cout << "Enter any expression to start\n\n" << "\t'quit' or 'Q' to exit." << "\n\n";
    std::cout << "Press 'Ctrl + \\' (Linux) or 'Ctrl + C (Windows)' to force quit." << std::endl;

    while (true)
    {   
        
        if (!getline(std::cin, cmd_line)) break;
        if (cmd_line == "quit" || cmd_line == "Q")
        {
            std::cout << "Exiting program..." << std::endl;
            exit(0);
        }

        if (cmd_line.empty())
        {
            std::cout << "> [Enter]: ";
            continue;
        }
        // else
        try 
            {
                std::vector<Token> tokens = ExpressionParser::tokenize(cmd_line);
                ExpressionParser::validateBrackets(tokens);

                std::vector<Token> postfix = ExpressionParser::infixToPostfix(tokens);
                
                double result = ExpressionParser::evaluateRPN(postfix, c);

                // Display the full expression
                std::cout << cmd_line << "\t=\t" << result << std::endl; 
            
            } catch (const std::exception& e) { ErrorReporter::handleException(e); }

    } // end while-loop
    
    return 0;
}