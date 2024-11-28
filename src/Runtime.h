#include "TreeBuilder.h"
#include "Tokenizer.h"
#include <map>
#include <vector>

class RunTime
{
public:
    struct FuncStruct
    {
        ExpressionNode instructions;
        ExpressionNode args;
    };

    RunTime(Expression &expr);
    ExpressionNode evaluate(ExpressionNode &exprNode);

    void run();

private:
    // Variables
    Expression &expr;                        // Reference to the input expression tree
    map<string, ExpressionNode> variables;   // Variable storage
    map<string, FuncStruct> globalFunctions; // Function storage

    // Helper Methods
    Number evaluateNumber(const ExpressionNode &item);                                                         // Extract and evaluate a number
    ExpressionNode evaluateNonVector(ExpressionNode &expr);                                                    // Handle non-vector (simple) expressions
    ExpressionNode evaluateBinaryOperation(const vector<ExpressionNode> &vec, Tokenizer::TokenType operation); // Perform binary operations
    ExpressionNode handleSetOperation(const vector<ExpressionNode> &vec);                                      // Handle variable assignment
    void handleFunctionDefinition(const vector<ExpressionNode> &vec);                                          // Handle variables and funcions calls

    // Error handling
    void logError(const std::string &message); // Log error without breaking execution
};