
// TreeBuilder.cpp
#include "TreeBuilder.h"

TreeBuilder::TreeBuilder(vector<Tokenizer::Token> &tokens) : tokens(tokens) {}

TreeBuilder::Expression TreeBuilder::BuildTree()
{
    while (token_index < tokens.size())
    {
        if (tokens[token_index].type == Tokenizer::TokenType::Opening_bracket)
        {
            token_index++;
            Expression expr = {};
            while (token_index < tokens.size() && tokens[token_index].type != Tokenizer::TokenType::Closing_bracket)
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
                
                token_index++;
            }

            return expr;
        }
    }
    return {};
}

void TreeBuilder::show(TreeBuilder::Expression &expr, int depth = 0)
{
    for (int i = 0; i < depth; i++)
        cout << "     ";
    switch (expr.operation)
    {
    case Expression::OperationType::Add:
        cout << "+" << endl;
        break;
    case Expression::OperationType::Sub:
        cout << "-" << endl;
        break;
    case Expression::OperationType::Div:
        cout << "/" << endl;
        break;
    case Expression::OperationType::Mul:
        cout << "*" << endl;
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
                cout << "     ";
            cout << get<float>(arg) << endl;
            break;
        }
    }
}