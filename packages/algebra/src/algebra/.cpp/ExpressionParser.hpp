//  @file ExpressionParser.hpp
#pragma once

#include <string>
#include <vector>

#include "Calculator.hpp"
#include "MathToken.hpp"


class ExpressionParser 
{
public: 
    static std::vector<Token> tokenize(const std::string& expression);
    // friend std::vector<Token> ...; 
    
    static void validateBrackets(const std::vector<Token>& tokens);

    static int getPrecedence(char op);
    static std::vector<Token> infixToPostfix (const std::vector<Token>& infixTokens);

    static double evaluateRPN (const std::vector<Token>& postfix, BaseCalculator& calc);

};

