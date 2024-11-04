#pragma once
#include "Tokenizer.h"
#include <vector>
#include <variant>

using namespace std;

using Number = float;
struct ExpressionNode
{
    std::variant<Number, Tokenizer::TokenType, std::vector<ExpressionNode>> value;
};

using Expression = std::vector<ExpressionNode>;

class TreeBuilder
{
public:
    TreeBuilder(vector<Tokenizer::Token> &tokens);
    Expression BuildTree();
    static void show(Expression &expr, int depth = 0);

private:
    vector<Tokenizer::Token> &tokens;
    int32_t token_index = 0; // Index for tracking token position

};