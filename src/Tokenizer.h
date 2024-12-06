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
        Opening_bracket, // 0
        Closing_bracket, //(Func (add x y) 233 Func (ff x y))
        Plus,
        Minus,
        Multiply,
        Divide,
        Number,
        Identifier,
        String,
        set,
        Func,
        Null,
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
