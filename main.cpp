#include <iostream>
#include <variant>
#include <vector>
#include <optional>
#include <cctype>

using namespace std;

class Tokenizer
{

    enum class TokenType
    {
        Opening_bracket,
        Closing_bracket,
        Plus,
        Minus,
        Multiply,
        Divide,
        Number,
    };

    using TokenValue = variant<monostate, int>;

    struct Token
    {
        TokenType type;
        TokenValue value;
    };

public:
    Tokenizer(string src) : _src(src) {};

    vector<Token> Tokenize()
    {
        // auto tokens = vector<Token>();
        // while(token = nextToken()) {
        //     tokens.push_back(token);
        // }
        // return tokens;
    }

    optional<Token> nextToken()
    {
        vector<Token> tokens;

        while (begin < _src.size())
        {
            if (isspace(_src[begin]))
            {
                begin++;
                end++;
                continue;
            }
            switch (_src[begin])
            {
            case '(':
                begin++;
                end++;
                return Token{TokenType::Opening_bracket, {}};
            case ')':
                begin++;
                end++;
                return Token{TokenType::Closing_bracket, {}};
            case '+':
                begin++;
                end++;
                return Token{TokenType::Plus, {}};
            case '-':
                begin++;
                end++;
                return Token{TokenType::Minus, {}};
            case '*':
                begin++;
                end++;
                return Token{TokenType::Multiply, {}};
            case '/':
                begin++;
                end++;
                return Token{TokenType::Divide, {}};
            default:
            {
                if (isdigit(_src[begin]))
                {
                    while (end + 1 <= _src.size() || isdigit(_src[end + 1]))
                    {
                        end++;
                    }
                    
                }


            }
            }
        }
        return nullopt;
    }

private:
    string _src;
    uint32_t begin = 0, end = 0;
};

int main()
{
    cout << "test";
    cout << "test";
    cout << "test";

    Tokenizer token("( * ( + ( 2 4))");

    return 0;
}