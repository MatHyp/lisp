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
             
                LOG( static_cast<int>(tokens[token_index].type));
                switch (tokens[token_index].type)
                {
                case Tokenizer::TokenType::Opening_bracket:
                    node = ExpressionNode{BuildTree(), tokens[token_index].type};    
                    
            

                    break;
                case Tokenizer::TokenType::Func:
                
                    node = ExpressionNode{monostate{}, Tokenizer::TokenType::Func};    
                    break;
                case Tokenizer::TokenType::let:
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

         case 0: // float
            for (int i = 0; i < depth; i++)
                cout << "     ";
            cout << "Typ Float " << get<float>(arg.value) << endl;

            break;
        case 1:
            for (int i = 0; i < depth; i++)
                cout << "     ";
            

            cout << (arg.type == Tokenizer::TokenType::Identifier ? "Identyfikator" : "String") << "  " << get<string>(arg.value) << endl;  
            break;
        case 2:
            show(get<std::vector<ExpressionNode>>(arg.value), depth + 1);
            break;
        case 3:
            cout << static_cast<int>(arg.type) << endl;
            break;
       
        default:
            cerr << "Unexpected variant index in ExpressionNode" << endl;
        }
    }
}