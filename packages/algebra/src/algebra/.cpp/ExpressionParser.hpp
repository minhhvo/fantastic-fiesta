//  @file ExpressionParser.hpp
#pragma once

#include "Calculator.hpp"
#include <string>
#include <vector>

/* @TODO: Adding support for [ ] and { }
    - Add definitions into TokenType LeftBracket, RightBracket, LeftBrace, and RightBrace.
*/
enum class TokenType
{ Number, Operator, LeftParen, RightParen };


struct Token {
    TokenType type;
    std::string value;
};

class ExpressionParser 
{
public: 
    static std::vector<Token> tokenize(const std::string& expression);

    static void validateBrackets(const std::vector<Token>& tokens);

    static int getPrecedence(const std::string& op);
    static std::vector<Token> infixToPostfix (const std::vector<Token>& infixTokens);

    static double evaluateRPN (const std::vector<Token>& postfix, BaseCalculator& calc);
};

