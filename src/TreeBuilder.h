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
    Expression expr = {};
    uint32_t token_index = 0;

public:
    TreeBuilder(vector<Tokenizer::Token> &tokens);
    Expression BuildTree();
    static void show(Expression &expr, int depth );
};
