#include "TreeBuilder.h"
#include <log.hpp>
#include <variant>

TreeBuilder::TreeBuilder(vector<Tokenizer::Token> &tokens) : tokens(tokens) {}

Expression TreeBuilder::BuildTree()
{
    while (token_index < tokens.size())
    {
        if (tokens[token_index].type == Tokenizer::TokenType::Opening_bracket)
        {
            Expression expr;
            token_index++;
            while (token_index < tokens.size() && tokens[token_index].type != Tokenizer::TokenType::Closing_bracket)
            {
                ExpressionNode node;
                switch (tokens[token_index].type)
                {
                case Tokenizer::TokenType::Opening_bracket:
                    node.value = BuildTree();
                    break;
                case Tokenizer::TokenType::Func:
                    node.value = tokens[token_index].type;
                    break;
                case Tokenizer::TokenType::let:
                    node.value = tokens[token_index].type;
                    break;
                case Tokenizer::TokenType::Identifier:
                    node.value = tokens[token_index].type;
                    break;
                case Tokenizer::TokenType::String:
                    node.value = tokens[token_index].type;
                    break;
                case Tokenizer::TokenType::Number:
                    node.value = get<float>(tokens[token_index].value);
                    break;
                case Tokenizer::TokenType::Plus:
                    node.value = tokens[token_index].type;
                    break;
                case Tokenizer::TokenType::Minus:
                    node.value = tokens[token_index].type;
                    break;
                case Tokenizer::TokenType::Multiply:
                    node.value = tokens[token_index].type;
                    break;
                case Tokenizer::TokenType::Divide:
                    node.value = tokens[token_index].type;
                    break;
                default:
                    break;
                }

                expr.push_back(node);
                token_index++;
            }
            return expr;
        }
        token_index++;
    }
    return {};
}

void TreeBuilder::show(Expression &expr, int depth)
{
    if (expr.empty())
    {
        cout << "Expression is empty." << endl;
        return;
    }
    for (auto &arg : expr)
    {
        switch (arg.value.index())
        {
        case 2:

            show(get<std::vector<ExpressionNode>>(arg.value), depth + 1);

            break;
        case 0: // float
            for (int i = 0; i < depth; i++)
                cout << "     ";
            cout << "Typ Float " << get<float>(arg.value) << endl;

            break;
        case 1:
            for (int i = 0; i < depth; i++)
                cout << "     ";
            cout << "Typ inny (func etc)" << endl;

            break;
        default:
            cerr << "Unexpected variant index in ExpressionNode" << endl;
        }
    }
}