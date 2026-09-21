#include "Calculator.hpp"
#include "ExpressionParser.hpp"
#include "ConsoleApp.hpp"

#include <iostream>
#include <csignal>

int main(void)
{
    BaseCalculator c;
    ConsoleApp::runRepl([&c](const std::string& cmd_line) 
    {
        std::vector<Token> tokens = ExpressionParser::tokenize(cmd_line);
        ExpressionParser::validateBrackets(tokens);

        std::vector<Token> postfix = ExpressionParser::infixToPostfix(tokens);
                
        double result = ExpressionParser::evaluateRPN(postfix, c);

        
        // Display the full expression
        std::cout << cmd_line << " = " << result << "\n"; 
    }
    );
    
    return 0;
}