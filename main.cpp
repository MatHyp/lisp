#include <iostream>
#include <string>
#include <vector>
#include <variant>
#include <optional>
#include <cctype>

using namespace std;

class Tokenizer
{
public:
    enum class TokenType
    {
        Opening_bracket,
        Closing_bracket,
        Plus,
        Minus,
        Multiply,
        Divide,
        Number,
    };

    using TokenValue = variant<monostate, float>;

    struct Token
    {
        TokenType type;
        TokenValue value;

        string toString() const
        {
            switch (type)
            {
            case TokenType::Opening_bracket:
                return "(";
            case TokenType::Closing_bracket:
                return ")";
            case TokenType::Plus:
                return "+";
            case TokenType::Minus:
                return "-";
            case TokenType::Multiply:
                return "*";
            case TokenType::Divide:
                return "/";
            case TokenType::Number:
                return to_string(get<float>(value));
            }
            return "";
        }
    };

    Tokenizer(const string &src) : _src(src) {}

    vector<Token> Tokenize()
    {
        vector<Token> tokens;
        optional<Token> token;

        while ((token = nextToken()).has_value())
        {
            cout << token->toString() << endl;
            tokens.push_back(token.value());
        }

        return tokens;
    }

private:
    optional<Token> nextToken()
    {
        if (begin >= _src.size())
        {
            return nullopt;
        }

        while (begin < _src.size() && isspace(_src[begin]))
        {
            ++begin;
        }

        end = begin;

        if (begin >= _src.size())
        {
            return nullopt;
        }

        switch (_src[begin])
        {
        case '(':
            ++begin;
            return Token{TokenType::Opening_bracket, {}};
        case ')':
            ++begin;
            return Token{TokenType::Closing_bracket, {}};
        case '+':
            ++begin;
            return Token{TokenType::Plus, {}};
        case '-':
            ++begin;
            return Token{TokenType::Minus, {}};
        case '*':
            ++begin;
            return Token{TokenType::Multiply, {}};
        case '/':
            ++begin;
            return Token{TokenType::Divide, {}};
        default:
            if (isdigit(_src[begin]))
            {
                // Parse a number
                while (end < _src.size() && isdigit(_src[end]))
                {
                    ++end;
                }
                string numberStr = _src.substr(begin, end - begin);
                float number = stof(numberStr);

                // Move `begin` to the end of the parsed number
                begin = end;
                return Token{TokenType::Number, number};
            }
            return nullopt;
        }
    }

    string _src;
    size_t begin = 0, end = 0;
};

class TreeBuilder
{
private:
    struct Expression
    {
        enum class OperationType
        {
            Add,
            Sub,
            Div,
            Mul
        };
        OperationType operation;
        vector<variant<Expression, float>> args;
    };
    vector<Tokenizer::Token> &tokens;

public:
    TreeBuilder(vector<Tokenizer::Token> &tokens) : tokens(tokens) {};
    Expression BuildTree()
    {
        vector<variant<Expression, float>> expressions;

        for (size_t i = 0; i < tokens.size(); i++)
        {
            Expression::OperationType operation;
            switch (tokens[i].type)
            {
            case Tokenizer::TokenType::Plus:
                operation = Expression::OperationType::Add;
                {
                }
                break;
            case Tokenizer::TokenType::Minus:
                operation = Expression::OperationType::Sub;
                {
                }
                break;
            case Tokenizer::TokenType::Multiply:
                operation = Expression::OperationType::Mul;
                {
                }
                break;
            case Tokenizer::TokenType::Divide:
                operation = Expression::OperationType::Div;
                {
                }
                break;
            case Tokenizer::TokenType::Number:
                expressions.push_back(get<float>(tokens[i].value));
                continue;
            case Tokenizer::TokenType::Closing_bracket:
                return;
            case Tokenizer::TokenType::Opening_bracket:
            {
            }
            default:
                break;
            }
        }
    }
};

int main()
{

    Tokenizer token("(+ 2200000002 10)");

    vector<Tokenizer::Token> tokens = token.Tokenize();

    for (int i = 0; i < tokens.size(); i++)
    {
        cout << tokens[i].toString();
    }
    return 0;
}