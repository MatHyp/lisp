// main.cpp
#include "src/Tokenizer.h"
#include "src/TreeBuilder.h"
#include "src/Runtime.h"

#include <iostream>

int main()
{

    // string user_input = "(- set zmienna 33 (- zmienna 10) )";
    // string user_input = "((set test 322) test 3)";

    string user_input = "((- 3 20 (+ 1 2 (set zmienna 23)) zmienna ))";

    Tokenizer tokenizer(user_input);

    vector<Tokenizer::Token> tokens = tokenizer.Tokenize();

    auto treebuilder = TreeBuilder(tokens);
    auto tree = treebuilder.BuildTree();

    RunTime runExpr(tree);

    runExpr.run();

    return 0;
}