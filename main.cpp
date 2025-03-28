// main.cpp
#include "src/Tokenizer.h"
#include "src/TreeBuilder.h"
#include "src/Runtime.h"

#include <iostream>

int main()
{
    string user_input = "((+ (Func pol (a b) (* a b)) (pol 10 10) (pol 10 10) ))";

    Tokenizer tokenizer(user_input);

    vector<Tokenizer::Token> tokens = tokenizer.Tokenize();

    auto treebuilder = TreeBuilder(tokens);
    auto tree = treebuilder.BuildTree();

    // cout << ExpressionNode{tree};

    RunTime runExpr(tree);

    runExpr.run();

    return 0;
}