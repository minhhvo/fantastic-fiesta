// @file InfixToPostfix.cpp 
// Converts an infix expression to a postfix expression.


#include <stack>
#include <unordered_map>
#include <string>
#include <vector>

std::string infixToPostfix(const std::string& infix_expr) 
{
    std::unordered_map <char, int> prec;
    prec['*']=3;
    prec['/']=3;
    prec['+']=2;
    prec['-']=2;
    prec['(']=1;
    std::stack<char> opStack;
    std::vector<char> postfixVector;
    
    if (infix_expr.empty()) return 0; // quick exit if infix_expr (@param) is an empty string;
    for (char token:infix_expr) 
    {
        if (token == ' ') { continue; 
        
        } else if (infix_expr.find(token) <= infix_expr.length())
        {
            postfixVector.emplace_back(token);

        } else if (token == '(') {
            opStack.push(token);

        } else if (token == ')') {
            char topToken;
            topToken = opStack.top();
            opStack.pop();

            while (topToken != '(')
            {
                postfixVector.emplace_back(topToken);
                topToken = opStack.top();
                opStack.pop();
            } // end while-loop
        } else {
            while ( !opStack.empty() &&
                    (prec[opStack.top()] >= prec[token])
                )
            {
                postfixVector.emplace_back(opStack.top());
                opStack.pop();
            } // end while-loop
            opStack.push(token);
        }
    }
    while (!opStack.empty()) 
    {
        postfixVector.emplace_back(opStack.top());
        opStack.pop();
    } // end while-loop

    return std::string (postfixVector.begin(), postfixVector.end());
    /** Original implementation: 
    std::string S(postfixVector.begin(), postfixVector.end()));
    return S; 
    */ // Q: what's the differences? Any potential memory bug with the shortcut (current) approach?
}

// FUTURE: Add `infixToPrefix () {}`.

#ifdef UNIT_TEST
#include <iostream>


int main()
{
    std::cout <<"infix: A * B + C * D\n" << "postfix: ";
    std::cout << infixToPostfix("A * B + C * D") << std::endl;
    std::cout << "infix: ( A + B ) * C - ( D - E ) * ( F + G )\n" << "postfix: ";
    std::cout << infixToPostfix("( A + B ) * C - ( D - E ) * ( F + G )") << std::endl;

    return 0;
}
#endif