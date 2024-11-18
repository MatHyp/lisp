#include "TreeBuilder.h"
#include <log.hpp>
#include <variant>

TreeBuilder::TreeBuilder(vector<Tokenizer::Token> &tokens) : tokens(tokens) {}

using Type = ExpressionNode::Type;

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
                    node = ExpressionNode{BuildTree(), Type::List};
                    break;
                case Tokenizer::TokenType::Func:
                    node = ExpressionNode{monostate{}, Type::Func};
                    break;
                case Tokenizer::TokenType::Set:
                    node = ExpressionNode{monostate{}, Type::Set};
                case Tokenizer::TokenType::Null:
                    node = ExpressionNode{monostate{}, Type::Null};
                    break;
                case Tokenizer::TokenType::Identifier:
                    node = ExpressionNode{get<String>(tokens[token_index].value), Type::Id};
                    break;
                case Tokenizer::TokenType::String:
                    node = ExpressionNode{get<String>(tokens[token_index].value), Type::Str};
                    break;
                case Tokenizer::TokenType::Number:
                    node = ExpressionNode{get<float>(tokens[token_index].value), Type::Num};
                    break;
                default:
                    LOG("Non existant Token type");
                    abort();
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

ostream &operator<<(ostream &os, const ExpressionNode &expr)
{
    switch (expr.type)
    {
    case Type::List:
        os << "( ";
        for (auto &item : get<vector<ExpressionNode>>(expr.value))
        {
            os << item << " ";
        }
        os << " )";
        break;
    case Type::Set:
        os << "keyword: set";
        break;
    case Type::Func:
        os << "keyword: func";
        break;
    case Type::Num:
        os << "number: " << get<Number>(expr.value);
        break;
    case Type::Id:
        os << "identifier: " << get<string>(expr.value);
        break;
    case Type::Str:
        os << "string: " << '"' << get<string>(expr.value) << '"';
        break;
    case Type::Null:
        os << "value: null";
        break;
    default:
        LOG("Invalid expression type");
        abort();
    }
    return os;
}
