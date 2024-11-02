// main.cpp
#include "src/Tokenizer.h"
#include "src/TreeBuilder.h"
#include <iostream>

typedef TreeBuilder::Expression::OperationType OperationType;

float evaluateTree(TreeBuilder::Expression &tree)
{
    float result = 0;
    switch (tree.operation)
    {
    case OperationType::Add:
        for (auto arg : tree.args)
        {
            if (arg.index() == 1)
            {
                result += get<float>(arg);
            }
            else
            {
                result += evaluateTree(get<TreeBuilder::Expression>(arg));
            }
        }
        break;
    case OperationType::Sub:
        for (auto arg : tree.args)
        {
            if (arg.index() == 1)
            {
                result -= get<float>(arg);
            }
            else
            {
                result -= evaluateTree(get<TreeBuilder::Expression>(arg));
            }
        }
        break;
    case OperationType::Mul:
        for (auto arg : tree.args)
        {
            if (arg.index() == 1)
            {
                result *= get<float>(arg);
            }
            else
            {
                result *= evaluateTree(get<TreeBuilder::Expression>(arg));
            }
        }
        break;
    case OperationType::Div:
        for (auto arg : tree.args)
        {
            if (arg.index() == 1)
            {
                result /= get<float>(arg);
            }
            else
            {
                result /= evaluateTree(get<TreeBuilder::Expression>(arg));
            }
        }
        break;
    }

    return result;
};

int main()
{

    // string user_input = "fff \"fffff\" Func let (+ 12 (- 4  4) 5) ";

    string user_input = "(Func (add x y) .233 (+ x y))";

    // getline (std::cin,user_input);

    Tokenizer tokenizer(user_input);
    vector<Tokenizer::Token> tokens = tokenizer.Tokenize();

    for (auto token : tokens)
    {
        cout << token.toString() << endl;
    }

    // auto treebuilder = TreeBuilder(tokens);
    // auto tree = treebuilder.BuildTree();

    // cout << evaluateTree(tree) << endl;
    return 0;
}