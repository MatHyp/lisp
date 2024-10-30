// Tokenizer.h
#pragma once
#include <string>
#include <vector>
#include <variant>
#include <optional>
#include <cctype>
#include <iostream>

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

        string toString() const;
    };

    Tokenizer(const string &src);
    vector<Token> Tokenize();

private:
    optional<Token> nextToken();
    string _src;
    size_t begin = 0, end = 0;
};
