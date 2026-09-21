
// Feature design & outline
/** PLAN:
3 core components (described by responsibilities):
- Tokenising (Lexing) | Pass a string into a std::vector
- Shunting-Yard | using std::stack to reorganise the tokens based on the operator precendence
- Iterating Stack-based Evaluation
*/

#include <cctype>
#include <stdexcept>
#include <stack>

#include "ExpressionParser.hpp"
#include "BracketParser.hpp"


std::vector<Token> ExpressionParser::tokenize(const std::string& expression) 
{
    std::vector<Token> tokens;
    size_t i = 0;
    while (i < expression.length()) 
    {
        char c = expression[i];

    // Ignore whitespaces
        if (std::isspace(c)) 
        {
            i++; continue;
        }
    
    // get multi-digit numbers and decimal
        if (std::isdigit(c) || c == '.') 
        {
            std::string num_str;
            while (i < expression.length() && (std::isdigit(expression[i]) || expression[i] == '.')) 
            {
                num_str += expression[i];
                i++;
            }
            tokens.push_back({TokenType::Number, num_str});
            continue;
        }
    // get operators
        if (c == '+' || c == '-' || c == '*' || c == '/') 
        {
            tokens.push_back({TokenType::Operator, std::string(1, c)});
            i++;
            continue;
        }
    // get parentheses and brackets
        if (c == '(' || c == '[' || c == '{') 
        {
            tokens.push_back({TokenType::OpeningBrac, std::string(1, c)});
            i++;
            continue;
        }
        if (c == ')' || c == ']' || c == '}') 
        {
            tokens.push_back({TokenType::ClosingBrac, std::string(1, c)});
            i++;
            continue;
        }

    // else { throw (); }
        throw std::invalid_argument(std::string("SyntaxError: Unknown character '") + c + "'");
    
    } // end while-loop
    
    return tokens;
} // end tokenize();


void ExpressionParser::validateBrackets(const std::vector<Token>& tokens)
{
    BracketParser::validate(tokens);
} // end validateBrackets();

int ExpressionParser::getPrecedence (const std::string&op) 
{
    if (op == "*" || op == "/") return 2;
    if (op == "+" || op == "-") return 1;
    return 0;
} // end getPrecendence();

std::vector<Token> ExpressionParser::infixToPostfix(const std::vector<Token> &infixTokens)
{
    std::vector<Token> postfix;
    std::stack<Token> operators;
    
    for (const auto& token : infixTokens)
    {
        if (token.type == TokenType::Number) { 
            postfix.push_back(token); 
        
        } else if (token.type == TokenType::OpeningBrac) { 
            operators.push(token); 
        
        } else if (token.type == TokenType::ClosingBrac) {
            while ( !operators.empty() && operators.top().type != TokenType::OpeningBrac )
            {
                postfix.push_back(operators.top());
                operators.pop();
            } // end while-loop
            if (!operators.empty()) { operators.pop(); }

        } else if (token.type == TokenType::Operator) {
            while ( !operators.empty() 
                  && operators.top().type == TokenType::Operator 
                  && getPrecedence(operators.top().value) >= getPrecedence(token.value)
                )
            {
                postfix.push_back(operators.top());
                operators.pop();
            } // end while-loop
            
            operators.push(token); // push the current token of type operator onto stack
        }
    } // end for-loop

    while ( !operators.empty() ) // flush remaining ops from stack to output
    {
        postfix.push_back(operators.top());
        operators.pop();
    } // end while-loop
    
    return postfix;
} // end infixToPostfix();

double ExpressionParser::evaluateRPN(const std::vector<Token>& postfix, BaseCalculator& calc)
{
    std::stack<double> values;

    for (const auto& token : postfix)
    {
        if (token.type == TokenType::Number)
        {
            values.push(std::stod(token.value));
        
        } else if (token.type == TokenType::Operator) {
            if (values.size() < 2) throw std::invalid_argument("SyntaxError: Missing operands.");
            
            double right = values.top();
            values.pop();

            double left = values.top();
            values.pop();

            char op = token.value[0];
            
            // Violating D.R.Y principle (repeated elsewhere) 
            if (op == '/' && right == 0.0) throw std::domain_error("Division by zero.");
            
            // Calculate and push the result back onto the stack
            double result = calc.calculate(left, right, op);
            values.push(result);
        }
    } // end for-loop

    if (values.size() != 1) throw std::invalid_argument("SyntaxError: Unbalanced expression.");
    
    return values.top();
} // end evaluateRPN();

#ifdef UNIT_TEST
#include "TimeIt.hpp"
#include "Calculator.hpp"

#define test_expr "3 + 5 / 2 + 4 * 5"
int main()
{
    auto tokens = ExpressionParser::tokenize(test_expr);
    auto rpn_tokens = ExpressionParser::infixToPostfix(tokens);
    BaseCalculator calc;

    PROFILE_EXECUTE(ExpressionParser::tokenize, 5, test_expr);
    PROFILE_EXECUTE(ExpressionParser::infixToPostfix, 5, tokens);
    PROFILE_EXECUTE(ExpressionParser::evaluateRPN, 5, rpn_tokens, calc);

    return 0;
}
#endif // UNIT_TEST