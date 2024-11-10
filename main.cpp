// main.cpp
#include "src/Tokenizer.h"
#include "src/TreeBuilder.h"
#include "src/Runtime.h"

#include <iostream>

int main()
{

    string user_input = "((set test \"dds\" ) test 3)";

    Tokenizer tokenizer(user_input);

    vector<Tokenizer::Token> tokens = tokenizer.Tokenize();

    auto treebuilder = TreeBuilder(tokens);
    auto tree = treebuilder.BuildTree();

    RunTime runExpr(tree);

    runExpr.run();

    return 0;
}