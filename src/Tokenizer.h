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
        Number,
        Identifier,
        String,
        Set,
        Func,
    };

    using TokenValue = variant<monostate, float, string>;

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
