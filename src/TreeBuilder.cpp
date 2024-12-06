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
                    node = ExpressionNode{BuildTree(), tokens[token_index].type};

                    break;
                case Tokenizer::TokenType::Func:

                    node = ExpressionNode{monostate{}, Tokenizer::TokenType::Func};
                    break;
                case Tokenizer::TokenType::Null:

                    node = ExpressionNode{monostate{}, Tokenizer::TokenType::Null};
                    break;
                case Tokenizer::TokenType::set:
                    node = ExpressionNode{monostate{}, tokens[token_index].type};

                    break;
                case Tokenizer::TokenType::Identifier:
                    node = ExpressionNode{get<String>(tokens[token_index].value), tokens[token_index].type};

                    break;
                case Tokenizer::TokenType::String:

                    node = ExpressionNode{get<String>(tokens[token_index].value), tokens[token_index].type};

                    break;
                case Tokenizer::TokenType::Number:

                    node = ExpressionNode{get<float>(tokens[token_index].value), tokens[token_index].type};

                    break;
                case Tokenizer::TokenType::Plus:

                    node = ExpressionNode{monostate{}, tokens[token_index].type};

                    break;
                case Tokenizer::TokenType::Minus:
                    node = ExpressionNode{monostate{}, tokens[token_index].type};

                    break;
                case Tokenizer::TokenType::Multiply:
                    node = ExpressionNode{monostate{}, tokens[token_index].type};

                    break;
                case Tokenizer::TokenType::Divide:

                    node = ExpressionNode{monostate{}, tokens[token_index].type};
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
ostream &printExpressionNode(ostream &os, const ExpressionNode &expr, int depth = 0)
{
    // Helper to add indentation based on the depth
    auto indent = [&os, depth]()
    {
        os << std::string(depth * 4, ' '); // 4 spaces per depth level
    };

    indent(); // Apply current depth indentation

    switch (expr.value.index())
    {
    case 0: // Number
        os << "number: " << get<Number>(expr.value);
        break;
    case 1: // String or Identifier
        os << ((expr.type == Tokenizer::TokenType::String) ? "string: " : "identifier: ")
           << get<string>(expr.value);
        break;
    case 2: // Nested Expression
    {
        os << "(\n"; // Opening for nested expression
        for (const auto &item : get<vector<ExpressionNode>>(expr.value))
        {
            printExpressionNode(os, item, depth + 1); // Recursively print with increased depth
            os << "\n";
        }
        indent();  // Close indentation
        os << ")"; // Closing for nested expression
        break;
    }
    case 3: // Operators and Declarations
        switch (expr.type)
        {
        case Tokenizer::TokenType::Divide:
            os << "operator: /";
            break;
        case Tokenizer::TokenType::Plus:
            os << "operator: +";
            break;
        case Tokenizer::TokenType::Multiply:
            os << "operator: *";
            break;
        case Tokenizer::TokenType::Minus:
            os << "operator: -";
            break;
        case Tokenizer::TokenType::set:
            os << "declaration: set";
            break;
        case Tokenizer::TokenType::Func:
            os << "declaration: func";
            break;
        case Tokenizer::TokenType::Null:
            os << "null";
            break;
        default:
            os << "unknown operator or declaration";
            break;
        }
        break;
    default:
        os << "unknown expression node";
        break;
    }

    return os;
}

ostream &operator<<(ostream &os, const ExpressionNode &expr)
{
    return printExpressionNode(os, expr, 0); // Start with depth 0
}