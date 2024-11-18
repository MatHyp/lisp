#include "TreeBuilder.h"
#include <map>

ExpressionNode &evalLiteral(ExpressionNode &literal);
ExpressionNode createSymbolValue(ExpressionNode &symbol, map<string, ExpressionNode> &symbols);
ExpressionNode evalSymbolValue(ExpressionNode &symbol, map<string, ExpressionNode> &symbols);
ExpressionNode createFunction(ExpressionNode &func, map<string, ExpressionNode> &symbols);


