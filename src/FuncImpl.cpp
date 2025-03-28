#include "FuncImpl.h"
#include "Runtime.h" // Now properly included in implementation file

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

// ExpressionNode FuncImpl::evaluateFunc(ExpressionNode &expr)
// {

//     return ExpressionNode{monostate{}, Tokenizer::TokenType::Null};
// }

ExpressionNode FuncImpl::evaluateFunc(const std::vector<ExpressionNode> &args, RunTime &runtime)
{
    auto &params = get<std::vector<ExpressionNode>>(this->args.value);
    if (params.size() != args.size())
    {
        return ExpressionNode{monostate{}, Tokenizer::TokenType::Null};
    }

    // Bind arguments to parameters
    localVariables.clear();
    for (size_t i = 0; i < params.size(); ++i)
    {
        std::string paramName = get<std::string>(params[i].value);
        localVariables[paramName] = args[i];
    }

    // Evaluate the function's instructions with access to localVariables
    return runtime.evaluate(instructions);
}