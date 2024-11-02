#pragma once
#include "Tokenizer.h"
#include <vector>
#include <variant>

class TreeBuilder
{
public:
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

    TreeBuilder(vector<Tokenizer::Token> &tokens);
    Expression BuildTree();
    static void show(Expression &expr, int depth);

private:
    vector<Tokenizer::Token> &tokens;
    Expression expr = {};
    int32_t token_index = 0;
};
