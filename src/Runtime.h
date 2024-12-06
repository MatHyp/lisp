#ifndef RUNTIME_H
#define RUNTIME_H

#include "TreeBuilder.h"
#include "Tokenizer.h"
#include <map>

class RunTime
{
public:
    explicit RunTime(Expression &expr);

    // Evaluate an expression node
    ExpressionNode evaluate(ExpressionNode &exprNode);

    // Run all expressions in the tree
    void run();

private:
    Expression &expr;
    std::map<std::string, ExpressionNode> variables;

    // Core operations
    ExpressionNode handleSetOperation(std::vector<ExpressionNode> &vec);
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

#endif // RUNTIME_H
