// TreeBuilder.cpp

#include "TreeBuilder.h"
#include <log.hpp>

TreeBuilder::TreeBuilder(vector<Tokenizer::Token> &tokens) : tokens(tokens) {}

BaseType::BaseType()
{
    this->i = Index::None;
}

BaseType::BaseType(Number num)
{
    this->d.num = num;
    this->i = BaseType::Index::Number;
}

BaseType::BaseType(Operation op)
{
    this->d.op = op;
    this->i = BaseType::Index::Operation;
}

BaseType::BaseType(vector<BaseType> l)
{
    this->d.l = l;
    this->i = BaseType::Index::List;
}

BaseType::BaseType(string s, Index i)
{
    this->i = i;
    switch (i)
    {
    case Index::String:
    case Index::Keyword:
    case Index::Identifier:
        // all theese 3 are the same type just named differently
        // it is the same inside of union
        // s chosen arbitrary
        this->d.s = s;
        break;
    default:
        LOG("Co ja robie tuu?");
        abort();
        break;
    }
}

BaseType::~BaseType()
{
    switch (this->i)
    {
    case Index::None:
        break;
    case Index::Operation:
    case Index::Number:
        break;
    case Index::String:
    case Index::Keyword:
    case Index::Identifier:
    {
        auto s = std::move(this->d.s);
    }
    break;
    case Index::List:
    {
        auto s = std::move(this->d.l);
    }
    break;
    default:
        LOG("Co ja robie tuu?");
        abort();
        break;
    }
}

constexpr BaseType &BaseType::operator=(const BaseType &o)
{
    memmove(&this->d, &o.d, sizeof(Data));
    this->i = o.i;
}

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
                // switch (tokens[token_index].type)
                // {
                // case Tokenizer::TokenType::Plus:
                //     expr.operation = Expression::OperationType::Add;
                //     break;
                // case Tokenizer::TokenType::Minus:
                //     expr.operation = Expression::OperationType::Sub;
                //     break;
                // case Tokenizer::TokenType::Multiply:
                //     expr.operation = Expression::OperationType::Mul;
                //     break;
                // case Tokenizer::TokenType::Divide:
                //     expr.operation = Expression::OperationType::Div;
                //     break;
                // case Tokenizer::TokenType::Number:
                //     expr.args.push_back(get<float>(tokens[token_index].value));
                //     break;
                //  case Tokenizer::TokenType::Opening_bracket:
                //  expr.args.push_back(BuildTree());
                //  break;
                // }

                BaseType new_exp;
                switch (tokens[token_index].type)
                {
                case Tokenizer::TokenType::Opening_bracket:
                    expr.push_back(BuildTree());
                    break;
                case Tokenizer::TokenType::Func:
                    new_exp = BaseType::BaseType("func", BaseType::Index::Keyword);
                    break;
                case Tokenizer::TokenType::let:
                    new_exp = BaseType::BaseType("let", BaseType::Index::Keyword);
                    break;
                case Tokenizer::TokenType::Identifier:
                    new_exp = BaseType::BaseType(get<string>(tokens[token_index].value), BaseType::Index::Identifier);
                    break;
                case Tokenizer::TokenType::String:
                    new_exp = BaseType::BaseType(get<string>(tokens[token_index].value), BaseType::Index::String);
                    break;
                case Tokenizer::TokenType::Number:
                    new_exp = BaseType::BaseType(get<float>(tokens[token_index].value));
                    break;
                case Tokenizer::TokenType::Plus:
                    new_exp = BaseType::BaseType(Operation::Add);
                    break;
                case Tokenizer::TokenType::Minus:
                    new_exp = BaseType::BaseType(Operation::Subtract);
                    break;
                case Tokenizer::TokenType::Multiply:
                    new_exp = BaseType::BaseType(Operation::Multiply);
                    break;
                case Tokenizer::TokenType::Divide:
                    new_exp = BaseType::BaseType(Operation::Divide);
                    break;
                }
                if (tokens[token_index].type != Tokenizer::TokenType::Opening_bracket)
                {
                    expr.push_back(new_exp);
                }

                token_index++;
            }
            return expr;
        }
    }
    return {};
}

// void TreeBuilder::show(TreeBuilder::Expression &expr, int depth = 0)
// {
//     for (int i = 0; i < depth; i++)
//         cout << "     ";
//     switch (expr.operation)
//     {
//     case Expression::OperationType::Add:
//         cout << "+" << endl;
//         break;
//     case Expression::OperationType::Sub:
//         cout << "-" << endl;
//         break;
//     case Expression::OperationType::Div:
//         cout << "/" << endl;
//         break;
//     case Expression::OperationType::Mul:
//         cout << "*" << endl;
//         break;
//     }
//     for (auto arg : expr.args)
//     {
//         switch (arg.index())
//         {
//         case 0:
//             show(get<Expression>(arg), depth + 1);
//             break;
//         case 1:
//             for (int i = 0; i < depth; i++)
//                 cout << "     ";
//             cout << get<float>(arg) << endl;
//             break;
//         }
//     }
// }