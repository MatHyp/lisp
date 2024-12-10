#include "FuncImpl.h"
#include "Runtime.h"

// Constructor initializes arguments and instructions
FuncImpl::FuncImpl(ExpressionNode &args, ExpressionNode &instructions)
    : args(args), instructions(instructions)
{
    auto &vec = get<vector<ExpressionNode>>(args.value);

    if (vec.size() != 0)
    {

        for (int i = 0; i < vec.size(); i++)
        {

            localVariables[get<string>(vec[i].value)] = ExpressionNode{monostate{}, Tokenizer::TokenType::Null};
        }
    }
}

FuncImpl::FuncImpl() : args(), instructions() // Initialize members with default constructors
{
}

ExpressionNode FuncImpl::evaluateFunc(ExpressionNode &expr)
{

    cout << "TEST" << endl;

    return ExpressionNode{monostate{}, Tokenizer::TokenType::Null};
}