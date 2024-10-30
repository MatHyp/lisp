
// TreeBuilder.cpp
#include "TreeBuilder.h"

TreeBuilder::TreeBuilder(vector<Tokenizer::Token> &tokens) : tokens(tokens) {}

// TreeBuilder::Expression TreeBuilder::BuildTree()
// {
//     vector<variant<Expression, float>> expressions;

// }

TreeBuilder::Expression TreeBuilder::BuildTree()
{
    for (; token_index < tokens.size(); token_index++)
    {
        switch (tokens[token_index].type)
        {
        case Tokenizer::TokenType::Opening_bracket:
        {

            Expression expr = {};
            while (tokens[token_index].type != Tokenizer::TokenType::Closing_bracket)
            {
                switch (tokens[token_index].type)
                {
                case Tokenizer::TokenType::Plus:
                    expr.operation = Expression::OperationType::Add;
                    break;
                case Tokenizer::TokenType::Minus:
                    expr.operation = Expression::OperationType::Sub;
                    break;
                case Tokenizer::TokenType::Multiply:
                    expr.operation = Expression::OperationType::Mul;
                    break;
                case Tokenizer::TokenType::Divide:
                    expr.operation = Expression::OperationType::Div;
                    break;
                case Tokenizer::TokenType::Number:
                    expr.args.push_back(get<float>(tokens[token_index].value));
                    break;
                case Tokenizer::TokenType::Opening_bracket:
                    expr.args.push_back(BuildTree());
                    break;
                }
            }

            return expr;
        }
        }
    }
    return {};
}

void TreeBuilder::show(TreeBuilder::Expression &expr, int depth = 0)
{
    for (int i = 0; i < depth; i++)
        cout << " ";
    switch (expr.operation)
    {
    case Expression::OperationType::Add:
        cout << "+";
        break;
    case Expression::OperationType::Sub:
        cout << "-";
        break;
    case Expression::OperationType::Div:
        cout << "/";
        break;
    case Expression::OperationType::Mul:
        cout << "*";
        break;
    }
    for (auto arg : expr.args)
    {
        switch (arg.index())
        {
        case 0:
            show(get<Expression>(arg), depth + 1);
            break;
        case 1:
            for (int i = 0; i < depth; i++)
                cout << " ";
            cout << get<float>(arg) << endl;
            break;
        }
    }
}