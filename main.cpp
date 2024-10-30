// main.cpp
#include "src/Tokenizer.h"
#include "src/TreeBuilder.h"
#include <iostream>

int main()
{
    Tokenizer tokenizer("22000 + 3 - 10");
    vector<Tokenizer::Token> tokens = tokenizer.Tokenize();

    for (size_t i = 0; i < tokens.size(); i++)
    {
        cout << tokens[i].toString();
    }

    return 0;
}
