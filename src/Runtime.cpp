#include <cassert>
#include "Runtime.h"
// tam gdzie jest assert to program w założeniu ma przestać sie interpretować
// tam gdzie jest abort to trzeba kodu dopisać

ExpressionNode evaluate(ExpressionNode &expr)
{
    if (expr.value.index() != 2)
    {
        return expr;
    }

    auto &vec = get<vector<ExpressionNode>>(expr.value);
    assert(vec.size() > 0);

    auto &fn = vec[0];
    assert(fn.value.index() == 3 || fn.value.index() == 1);
    if (fn.value.index() == 1)
    {
        assert(fn.type == Tokenizer::TokenType::Identifier);
        {
            cout << "funkcje nie zaimplementowane";
            abort();
        }
    }

    switch (fn.type)
    {
    case Tokenizer::TokenType::Plus:
    {
        Number sum = 0;
        for (int i = 1; i < vec.size(); i++)
        {
            auto item = vec[i].value;
            Number val;
            if (item.index() == 2)
            {
                ExpressionNode sub_vec = ExpressionNode{.value = item};
                auto temp = evaluate(sub_vec);
                assert(temp.value.index() == 0);
                val = get<Number>(temp.value);
            }
            else if (item.index() == 0)
            {
                val = get<Number>(item);
            }
            else
            {
                assert(!"Type is not number!");
            }
            sum += val;
        }
        return ExpressionNode{.value = sum, .type = Tokenizer::TokenType::Number};
    }
    break;
    case Tokenizer::TokenType::Multiply:
    {
        Number mul = 1;
        for (int i = 1; i < vec.size(); i++)
        {
            auto item = vec[i].value;
            Number val;
            if (item.index() == 2)
            {
                ExpressionNode sub_vec = ExpressionNode{.value = item};
                auto temp = evaluate(sub_vec);
                assert(temp.value.index() == 0);
                val = get<Number>(temp.value);
            }
            else if (item.index() == 0)
            {
                val = get<Number>(item);
            }
            else
            {
                assert(!"type is not number!");
            }
            mul *= val;
        }
        return ExpressionNode{.value = mul, .type = Tokenizer::TokenType::Number};
    }
    break;
    case Tokenizer::TokenType::Minus:
    {
        assert(vec.size() >= 2);
        auto first = vec[1].value;
        assert(first.index() == 0 || first.index() == 2);
        ExpressionNode diff_val = ExpressionNode{.value = first};
        auto temp = evaluate(diff_val);
        Number diff = get<Number>(temp.value);

        for (int i = 2; i < vec.size(); i++)
        {
            auto item = vec[i].value;
            Number val;
            if (item.index() == 2)
            {
                ExpressionNode sub_vec = ExpressionNode{.value = item};
                auto temp = evaluate(sub_vec);
                assert(temp.value.index() == 0);
                val = get<Number>(temp.value);
            }
            else if (item.index() == 0)
            {
                val = get<Number>(item);
            }
            else
            {
                assert(!"type is not number!");
            }
            diff -= val;
        }
        return ExpressionNode{.value = diff, .type = Tokenizer::TokenType::Number};
    }
    break;
    case Tokenizer::TokenType::Divide:
    {
        assert(vec.size() >= 2);
        auto first = vec[1].value;
        assert(first.index() == 0 || first.index() == 2);
        ExpressionNode div_val = ExpressionNode{.value = first};
        auto temp = evaluate(div_val);
        Number div = get<Number>(temp.value);

        for (int i = 2; i < vec.size(); i++)
        {
            auto item = vec[i].value;
            Number val;
            if (item.index() == 2)
            {
                ExpressionNode sub_vec = ExpressionNode{.value = item};
                auto temp = evaluate(sub_vec);
                assert(temp.value.index() == 0);
                val = get<Number>(temp.value);
            }
            else if (item.index() == 0)
            {
                val = get<Number>(item);
            }
            else
            {
                assert(!"type is not number!");
            }
            div /= val;
        }
        return ExpressionNode{.value = div, .type = Tokenizer::TokenType::Number};
    }
    break;
    case Tokenizer::TokenType::let:
        cout << "let not implemented" << endl;
        abort();

    case Tokenizer::TokenType::Func:
        cout << "Func not implemented" << endl;
        abort();

    default:
        assert(!"This is not supposed to happen!");
    }
}