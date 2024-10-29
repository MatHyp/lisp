#include <iostream>
using namespace std;

enum class TokenTypes {
    
};

class Tokenizer {
public:
    Tokenizer(string src) : _src(src) {};



private:

    string _src;
};

int main() {
    cout << "test";
    cout << "test";
    cout << "test";

    Tokenizer token("( * ( + ( 2, 4))");

    return 0;
}