// Tokenizer.cpp
#include "Tokenizer.h"

Tokenizer::Tokenizer(const string &src) : _src(src) {}

vector<Tokenizer::Token> Tokenizer::Tokenize()
{
    vector<Token> tokens;
    optional<Token> token;

    while ((token = nextToken()).has_value())
    {
        tokens.push_back(token.value());
    }

    return tokens;
}

optional<Tokenizer::Token> Tokenizer::nextToken()
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
            while (end < _src.size() && isdigit(_src[end]))
            {
                ++end;
            }
            string numberStr = _src.substr(begin, end - begin);
            float number = stof(numberStr);

            begin = end;
            return Token{TokenType::Number, number};
        }
        return nullopt;
    }
}

string Tokenizer::Token::toString() const
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
