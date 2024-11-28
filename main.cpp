// main.cpp
#include "src/Tokenizer.h"
#include "src/TreeBuilder.h"
#include "src/Runtime.h"

#include <iostream>

int main()
{
    // string user_input = R"""(
    //         (
    //         Func square () (

    //         )
    //         )""";

    // string program = "(" + user_input + ")";
    // string user_input = "((- 3 20 (+ 1 2 (set zmienna 23)) zmienna ))";

    // string user_input = "((+ (set zmienna 30)  (Func test () (+ 10 20 zmienna (+ 10 20))) test test zmienna (- 20 test)))";
    string user_input = "((+ (set zmienna 30) 20 30 (- zmienna 20)))";

    Tokenizer tokenizer(user_input);

    vector<Tokenizer::Token> tokens = tokenizer.Tokenize();

    auto treebuilder = TreeBuilder(tokens);
    auto tree = treebuilder.BuildTree();

    cout << ExpressionNode{tree} << "\n -----------------------------" << endl;

    RunTime runExpr(tree);

    runExpr.run();

    return 0;
}