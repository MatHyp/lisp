// Tokenizer.cpp
#include "Tokenizer.h"
#include "log.hpp"

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
        if (isdigit(_src[begin]) || _src[begin] == '.')
        {
            while (end < _src.size() && (isdigit(_src[end]) || _src[end] == '.'))
            {
                ++end;
            }
            string numberStr = _src.substr(begin, end - begin);
            float number = stof(numberStr);

            begin = end;
            return Token{TokenType::Number, number};
        }

        if (_src.substr(begin, 3) == "set" && _src[begin + 3] == ' ')
        {
            begin += 3;
            end += 3;

            return Token{TokenType::set, {}};
        }
        if (_src.substr(begin, 4) == "Func" && _src[begin + 4] == ' ')
        {
            begin += 4;
            end += 4;

            return Token{TokenType::Func, {}};
        }

        if (_src[begin] == '"')
        {
            end++;
            while (_src[end] != '"')
            {
                ++end;
            }

            string str = _src.substr(begin + 1, (end - begin) - 1);

            end++;
            begin = end;
            return Token{TokenType::String, str};
        }
        if (isalpha(_src[begin]))
        {
            end++;
            while (_src.length() >= (end + 1))
            {
                if (_src[end] == ' ' || _src[end] == ')')
                {
                    break;
                }
                ++end;
            }

            string str = _src.substr(begin, (end - begin));

            begin = end;
            return Token{TokenType::Identifier, str};
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
    case TokenType::set:
        return "set";
    case TokenType::String:
        return "string";
    case TokenType::Func:
        return "Func";
    case TokenType::Identifier:
        return "Identifier " + get<string>(value);
    }
    return "";
}