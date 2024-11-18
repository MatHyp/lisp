#include "Runtime.h"
#include <cassert>
#include <algorithm>
#include <span>

using Type = ExpressionNode::Type;
/// a function to map value literal to value of it (does nothing but fancily)
ExpressionNode &evalLiteral(ExpressionNode &literal)
{
    assert(literal.type == Type::Str ||
           literal.type == Type::Num ||
           literal.type == Type::Null ||
           literal.type == Type::List);
    return literal;
}

/// creates a symbolic name for value (implementation of set command)
ExpressionNode createSymbolValue(ExpressionNode &symbol, map<string, ExpressionNode> &symbols)
{
    assert(symbol.type == Type::List);
    auto &vec = get<Expression>(symbol.value);
    assert(vec.size() == 3);
    assert(vec[0].type == Type::Set);
    assert(vec[1].type == Type::Id);

    symbols[get<string>(vec[1].value)] = vec[2];
    return ExpressionNode{monostate{}, Type::Null};
}

/// reads value of symbolic name or returns null and sets the value to null
ExpressionNode evalSymbolValue(ExpressionNode &symbol, map<string, ExpressionNode> &symbols)
{
    assert(symbol.type == Type::Id);
    auto [it, inserted] = symbols.try_emplace(get<string>(symbol.value), ExpressionNode{monostate{}, Type::Null});
    return it->second;
}

/// creates a new function
ExpressionNode createFunction(ExpressionNode &func, map<string, ExpressionNode> &symbols)
{
    assert(func.type == Type::List);
    auto &vec = get<Expression>(func.value);
    // check if has all necessery components (func keyword, name, arguments list, at least 1 more expression)
    assert(vec.size() >= 4);
    // check if given expression is a function declaration
    assert(vec[0].type == Type::Func);
    // check if has name
    assert(vec[1].type == Type::Id);
    // check if has arguments
    assert(vec[2].type == Type::List);
    auto &args = get<Expression>(vec[2].value);
    auto arg_names = vector<string>(args.size());
    for_each(args.begin(), args.end(), [&](auto &expr)
             { assert(expr.type == Type::Id); arg_names.push_back( get<string>(expr.value)); });

    vec.pop_back();
    vec.pop_back();
    vec.pop_back();

    symbols[get<string>(vec[1].value)] = ExpressionNode{Func{move(arg_names), move(vec)}, Type::Func};
    return ExpressionNode{monostate{}, Type::Null};
}

struct FunctionCall {
    
};