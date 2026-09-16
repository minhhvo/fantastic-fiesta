// @file: BracketPairSorting.cpp

#include <vector>
#include <stack>
#include <string>

#include <algorithm>

using namespace std;
using pairVec = vector<pair<string, char>>; // currently unused variable assignment;


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
int main () 
{
      string s="[()()]{}";
      cout<<(isBalanced(s)?"true":"false");
} // end unit test */
#endif

class PairedBraces
{
    const std::string openingBraces = "{[(";
    const std::string closingBraces = "}])";

    int traverse (pairVec& brackets, string& S, int64_t& ct)
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
                            else 
                            {

                            }

                        }

                    }

                } // end for-loop
            }
        }
        return 0;
    }
};
