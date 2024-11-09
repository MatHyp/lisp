// main.cpp
#include "src/Tokenizer.h"
#include "src/TreeBuilder.h"
#include "src/Runtime.h"

#include <iostream>



int main()
{

    string user_input = "(- (/ 38 (+ 4 (* 5 3))) 3 )";

    Tokenizer tokenizer(user_input);

    vector<Tokenizer::Token> tokens = tokenizer.Tokenize();

    auto treebuilder = TreeBuilder(tokens);
    auto tree = treebuilder.BuildTree();

    auto expr = ExpressionNode{.value = tree};
    cout << expr << endl;
    cout << evaluate(expr) << endl;
    return 0;
}