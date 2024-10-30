// main.cpp
#include "src/Tokenizer.h"
#include "src/TreeBuilder.h"
#include <iostream>

int main()
{
    Tokenizer tokenizer("(- (+ 22000  3)  10)");
    vector<Tokenizer::Token> tokens = tokenizer.Tokenize();
    auto treebuilder = TreeBuilder(tokens);
    auto tree = treebuilder.BuildTree();

    TreeBuilder::show(tree, 0);

    return 0;
}
