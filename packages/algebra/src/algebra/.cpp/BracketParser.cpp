// @file: BracketPairSorting.cpp

#include <stdexcept>
#include <vector>
#include <stack>
#include <string>
#include <algorithm>

#include "BracketParser.hpp"

namespace 
{
    bool isMatchingPair (char open, char close)
    {
        return 
        ( open == '(' && close == ')' ) ||
        ( open == '[' && close == ']' ) ||
        ( open == '{' && close == '}' );
    }
}

void BracketParser::validate(const std::vector<Token>& tokens, bool isPaired) // future-proofing; reusable for balanced expression with unpaired bracket. For example: `[a, b)`.
{
    std::stack<char> brackets;

    for (const auto& token : tokens) 
    {
        if (token.type == TokenType::OpeningBrac) { brackets.push(token.value[0]); }
        else if (token.type == TokenType::ClosingBrac) 
        {
            if (brackets.empty()) { throw std::invalid_argument("SyntaxError: Unexpected closing bracket."); }

            char top = brackets.top();
            char current = token.value[0];
            brackets.pop();

            if (isPaired && !isMatchingPair(top, current)) 
            { throw std::invalid_argument("SyntaxError: Mismatched brackets."); }
        }
    } // end for-loop
    
    if (!brackets.empty())
    { throw std::invalid_argument("SyntaxError: Missing closing bracket."); }
}

bool isBalanced(std::string& s) 
{
    signed int top = -1;
    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] == '(' || s[i] == '{' || s[i] == '[')
        {
            s[++top] = s[i];
        } else if (s[i] == ')' || s[i] == '}' || s[i] == ']')
        {
            if (top == -1) return false;
            if (  
                (s[i] == ')' && s[top] != '(') ||
                (s[i] == '}' && s[top] != '{') ||
                (s[i] == ']' && s[top] != '[')
            ) return false;
        }
        top--;
    } // end for-loop
    
    return top == -1;
} // end isBalanced

#ifdef UNIT_TEST
#include <iostream>
#include "TimeIt.hpp"

int main () 
{
    std::string s="[()()]{}";

    std::vector<Token> mock = {
        {TokenType::OpeningBrac, "["}, {TokenType::OpeningBrac, "("},
        {TokenType::ClosingBrac, ")"}, {TokenType::OpeningBrac, "("},
        {TokenType::ClosingBrac, ")"}, {TokenType::ClosingBrac, "]"},
        {TokenType::OpeningBrac, "{"}, {TokenType::ClosingBrac, "}"}
    };

    std::cout<<(isBalanced(s)?"true":"false") << std::endl;
    
    PROFILE_EXECUTE(BracketParser::validate, 1, mock, true);

    return 0;
} // end unit test */
#endif

// sampled recipe from StackOverflow

class PairedBraces
{
private:
    const std::string openingBraces = "{[(";
    const std::string closingBraces = "}])";
public:
    using pairVec = std::vector<std::pair<std::string, char>>;

    bool pop_if_possible(std::stack<char>, char); /** ==Quoted recommendation==
    """
    Perhaps you should have a `bool pop_if_possible(std::stack<char>, char)` method so you can write
        ```
        if (  c==')' && 
            !pop_if_possible(stack, '(')
        ) { return false; }
        ```
    to improve on source code redundancy.
    """
    */

    int traverse (pairVec& brackets, std::string& S)
    {
        for ( int i = 0; i + 1 < brackets.size(); i++ )
        {
            char currentChar;
            std::stack<int> stack;

            if (std::find(openingBraces.begin(), openingBraces.end(), currentChar) 
                != openingBraces.end() ) 
            { stack.push(currentChar); } 
            else if (std::find(closingBraces.begin(), closingBraces.end(), currentChar)
                    != closingBraces.end() )
            {
                char d;
                // check if currentChar is matching the one on top of your stack-- d
                for (int i = 0; i < S.length(); i++)
                {
                    char c = S[i];

                    if (c == '(') { stack.push(c); }
                    else if (c == '[') {stack.push(c); }
                    else if (c == '{') {stack.push(c); }

                    else if (c == ')')
                    {
                        if (stack.empty()) { return false; }
                        else 
                        {
                            d = stack.top();
                            stack.pop();
                            if (d != '(') { return false; } 
                            
                            return true;
                        }

                    }

                } // end for-loop
            }
        }
        return 0;
    }
};
