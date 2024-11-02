#pragma once
#include "Tokenizer.h"
#include <vector>

enum class Operation
{
    Add,
    Subtract,
    Divide,
    Multiply
};
typedef float Number;
typedef string Identifier;
typedef string String;
typedef string Keyword;

/// @brief this is very bad hack, dont write code that way ever again, unless necessary
struct BaseType
{

    enum class Index
    {
        None,
        Operation,
        Number,
        Identifier,
        String,
        Keyword,
        List,
    };

    union Data
    {
        Operation op;
        Number num;
        Identifier id;
        String s;
        Keyword k;
        vector<BaseType> l;
        Data();
        ~Data();
    };

    Data d;
    Index i = Index::None;
    BaseType();
    BaseType(Number num);
    BaseType(Operation op);
    BaseType(vector<BaseType> l);
    BaseType(string s, Index i);
    ~BaseType();
    BaseType &BaseType::operator=(const BaseType &);
};

class TreeBuilder
{
public:
    using Expression = vector<BaseType>;

    TreeBuilder(vector<Tokenizer::Token> &tokens);
    Expression BuildTree();
    static void show(Expression &expr, int depth);

private:
    vector<Tokenizer::Token> &tokens;
    Expression expr = {};
    int32_t token_index = 0;
};
