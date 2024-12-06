#include "TreeBuilder.h"
#include "Tokenizer.h"
#include <map>

// ExpressionNode evaluate(ExpressionNode &expr);

class RunTime
{
public:
    RunTime(Expression &expr);
    ExpressionNode evaluate(ExpressionNode &exprNode);
    ExpressionNode handleSetOperation(vector<ExpressionNode> &vec);

    void logError(const std::string &message); // Log error without breaking execution

    void run()
    {
        for (size_t i = 0; i < expr.size(); i++)
        {

            cout << this->evaluate(expr[i]) << endl;
        }
    }

private:
    Expression &expr;
    map<string, ExpressionNode> variables;
};