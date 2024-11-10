#include "TreeBuilder.h"
#include "Tokenizer.h"
#include <map>

// ExpressionNode evaluate(ExpressionNode &expr);

class RunTime
{
public:
    RunTime(Expression &expr);
    ExpressionNode evaluate(ExpressionNode &exprNode);

    void run()
    {

        for (int i = 0; i < expr.size(); i++)
        {
            cout << this->evaluate(expr[i]) << endl;
        }
    }

private:
    Expression &expr;
    map<string, ExpressionNode> variables;
};