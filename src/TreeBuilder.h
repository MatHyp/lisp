#pragma once
#include "Tokenizer.h"
#include <vector>
#include <variant>

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
    TreeBuilder(vector<Tokenizer::Token> &tokens);
    Expression BuildTree();
};

