// @file BracketParser.hpp

#pragma once
#include <string>
#include <vector>
#include <string>



#include "MathToken.hpp"

class BracketParser
{
private:
    static bool isBalanced(const std::vector<Token>& tokens);

public:
    enum class BracketType { Parentheses, SquareBrackets, CurlyBraces, AngleBrackets };
    struct SubExpression
    {
        BracketType type;
        std::string value;
    };

    static void validate(const std::vector<Token>& tokens, bool isPaired = true);
};

