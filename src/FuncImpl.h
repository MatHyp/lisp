#ifndef FUNCIMPL_H
#define FUNCIMPL_H

#include "Runtime.h"
#include "TreeBuilder.h"
#include <map>
#include <string>

class FuncImpl
{
public:
    // Constructor
    FuncImpl(ExpressionNode &args, ExpressionNode &instructions);

    FuncImpl();

    ExpressionNode args;
    ExpressionNode instructions;
    std::map<string, ExpressionNode> localVariables;
    std::map<string, ExpressionNode> localFunctions;

    ExpressionNode evaluateFunc(ExpressionNode &expr); // Accepts one argument

private:
};

#endif // FUNCIMPL_H
