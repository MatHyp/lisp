#pragma once
#include "Tokenizer.h"
#include <vector>
#include <variant>

using namespace std;

using Number = float;
using String = string;

struct ExpressionNode
{
    std::variant<Number, String, std::vector<ExpressionNode>, monostate> value;
    Tokenizer::TokenType type;
};

ostream &operator<<(ostream &os, const ExpressionNode &);

using Expression = std::vector<ExpressionNode>;

class TreeBuilder
{
public:
    TreeBuilder(vector<Tokenizer::Token> &tokens);
    Expression BuildTree();
    static void show(Expression &expr, int depth = 0);

private:
    vector<Tokenizer::Token> &tokens;
    int32_t token_index = 0;
};