
// TreeBuilder.cpp
#include "TreeBuilder.h"

TreeBuilder::TreeBuilder(vector<Tokenizer::Token> &tokens) : tokens(tokens) {}

TreeBuilder::Expression TreeBuilder::BuildTree()
{
    vector<variant<Expression, float>> expressions;

    for (size_t i = 0; i < tokens.size(); i++)
    {
        Expression::OperationType operation;
        switch (tokens[i].type)
        {
        case Tokenizer::TokenType::Plus:
            operation = Expression::OperationType::Add;
            break;
        case Tokenizer::TokenType::Minus:
            operation = Expression::OperationType::Sub;
            break;
        case Tokenizer::TokenType::Multiply:
            operation = Expression::OperationType::Mul;
            break;
        case Tokenizer::TokenType::Divide:
            operation = Expression::OperationType::Div;
            break;
        case Tokenizer::TokenType::Number:
            expressions.push_back(get<float>(tokens[i].value));
            continue;
        case Tokenizer::TokenType::Closing_bracket:
            break;
        case Tokenizer::TokenType::Opening_bracket:
            break;
        default:
            break;
        }
    }
    return Expression{};
}
