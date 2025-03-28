#ifndef FUNCIMPL_H
#define FUNCIMPL_H
#include <map>
#include <string>
#include <vector>

#include "Runtime.h"
#include "TreeBuilder.h"

class RunTime;

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

    // ExpressionNode evaluateFunc(ExpressionNode &expr,map<string, ExpressionNode> &parentVariables, map<string, ExpressionNode> &parentFunctions );
    // ExpressionNode evaluateFunc(ExpressionNode &expr);
    ExpressionNode evaluateFunc(const std::vector<ExpressionNode> &args, RunTime &runtime);

private:
};

#endif // FUNCIMPL_H
