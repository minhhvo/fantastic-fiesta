//  @file ExpressionParser.hpp
#pragma once

#include <string>
#include <vector>

#include "Calculator.hpp"
#include "MathToken.hpp"


// Proposed changes/refactor:
/*
enum class TokenType
{
    Operands, Operator, 
    InnerGroup // or 'SubExpression'
};

struct Token
{
    TokenType type;
    std::string value;
};

enum class BinaryOperator
{
    Plus, Multiply, 
    Minus, Divide
};

enum class UnaryOperator
{
};

enum class MathOperators
{
    BinaryOperator, UnaryOperator
};
*/

class ExpressionParser 
{
public: 
    static std::vector<Token> tokenize(const std::string& expression);
    // friend std::vector<Token> ...; 
    
    static void validateBrackets(const std::vector<Token>& tokens);

    static int getPrecedence(const std::string& op);
    static std::vector<Token> infixToPostfix (const std::vector<Token>& infixTokens);

    static double evaluateRPN (const std::vector<Token>& postfix, BaseCalculator& calc);

};

