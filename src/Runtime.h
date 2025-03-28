#ifndef RUNTIME_H
#define RUNTIME_H

#include "TreeBuilder.h"
#include "Tokenizer.h"
#include "FuncImpl.h"

#include <map>
#include <memory>

class FuncImpl;

class RunTime
{
public:
    RunTime(Expression &expr);

    ExpressionNode evaluate(ExpressionNode &exprNode);

    void run();

private:
    Expression &expr;

    map<string, ExpressionNode> globalVariables;
    map<string, FuncImpl> globalFunctions;
    std::map<std::string, ExpressionNode> *currentLocals = nullptr;
    std::vector<std::map<std::string, ExpressionNode> *> localsStack;
    // Core operations
    ExpressionNode handleSetOperation(const vector<ExpressionNode> &vec);
    ExpressionNode handleFunctionDefinition(vector<ExpressionNode> &vec);
    ExpressionNode handleArithmeticOperation(std::vector<ExpressionNode> &vec, Tokenizer::TokenType operationType);

    // Arithmetic helpers
    Number evaluateOperand(const ExpressionNode &node);
    ExpressionNode handleAddition(std::vector<ExpressionNode> &vec);
    ExpressionNode handleMultiplication(std::vector<ExpressionNode> &vec);
    ExpressionNode handleSubtraction(std::vector<ExpressionNode> &vec);
    ExpressionNode handleDivision(std::vector<ExpressionNode> &vec);

    // Error handling
    void logError(const std::string &message);
};

#endif
