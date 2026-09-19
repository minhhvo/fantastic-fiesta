// @file MathToken.hpp
#pragma once
#include <string>

enum class TokenType 
{ 
    Number, 
    Operator, 
    OpeningBrac, 
    ClosingBrac 
};

struct Token 
{
    TokenType type;
    std::string value;
};
