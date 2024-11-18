// main.cpp
#include "src/Tokenizer.h"
#include "src/TreeBuilder.h"

#include <iostream>

int main()
{

    // string user_input = "(- set zmienna 33 (- zmienna 10) )";
    // string user_input = "((set test 322) test 3)";

    string user_input = R"""(
(func square (x) 
    (* x x))
(square 4)
)""";

    string program = "(" + user_input + ")";

    Tokenizer tokenizer(program);

    vector<Tokenizer::Token> tokens = tokenizer.Tokenize();

    auto treebuilder = TreeBuilder(tokens);
    auto tree = treebuilder.BuildTree();

    cout << ExpressionNode{tree};

    return 0;
}