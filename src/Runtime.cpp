#include <cassert>
#include "Runtime.h"

RunTime::RunTime(Expression &expr) : expr(expr) {}

void RunTime::logError(const std::string &message)
{
    std::cerr << "Runtime Warning: " << message << std::endl;
}

ExpressionNode RunTime::handleSetOperation(std::vector<ExpressionNode> &vec)
{
    if (vec.size() != 3)
    {
        logError("Invalid number of arguments for 'set' operation.");
        return ExpressionNode{monostate{}, Tokenizer::TokenType::Null};
    }

    if (vec[0].type != Tokenizer::TokenType::set)
    {
        logError("First element is not 'set'.");
        return ExpressionNode{monostate{}, Tokenizer::TokenType::Null};
    }

    if (vec[1].type != Tokenizer::TokenType::Identifier)
    {
        logError("Second element is not an Identifier.");
        return ExpressionNode{monostate{}, Tokenizer::TokenType::Null};
    }

    auto value = vec[2];
    if (value.type != Tokenizer::TokenType::Number)
    {
        logError("Assigned value must be a number.");
        return ExpressionNode{monostate{}, Tokenizer::TokenType::Null};
    }

    std::string varName = get<std::string>(vec[1].value);
    variables[varName] = value;

    return ExpressionNode{monostate{}, Tokenizer::TokenType::Null};
}

ExpressionNode RunTime::evaluate(ExpressionNode &expr)
{
    if (expr.value.index() != 2)
    {
        if (expr.value.index() == 1 && expr.type == Tokenizer::TokenType::Identifier)
        {
            std::string varName = get<std::string>(expr.value);
            std::cout << "Accessing variable '" << varName << "' with value: " << get<Number>(variables.at(varName).value) << std::endl;

            try
            {
                return variables.at(varName);
            }
            catch (const std::out_of_range &)
            {
                logError("Undefined variable: " + varName);
                return ExpressionNode{monostate{}, Tokenizer::TokenType::Null};
            }
        }

        return expr;
    }

    auto &vec = get<std::vector<ExpressionNode>>(expr.value);
    assert(!vec.empty());

    auto &fn = vec[0];
    switch (fn.type)
    {
    case Tokenizer::TokenType::set:
        return handleSetOperation(vec);
    case Tokenizer::TokenType::Plus:
    {
        Number sum = 0;
        for (size_t i = 1; i < vec.size(); i++)
        {
            auto temp = evaluate(vec[i]);

            if (temp.type == Tokenizer::TokenType::Null)
                continue;

            if (temp.type != Tokenizer::TokenType::Number)
            {
                logError("Unexpected type in '+' operation.");
                return ExpressionNode{monostate{}, Tokenizer::TokenType::Null};
            }
            sum += get<Number>(temp.value);
        }
        return ExpressionNode{.value = sum, .type = Tokenizer::TokenType::Number};
    }
    case Tokenizer::TokenType::Multiply:
    {
        Number mul = 1;

        for (size_t i = 1; i < vec.size(); i++)
        {
            auto temp = evaluate(vec[i]);
            if (temp.type == Tokenizer::TokenType::Null)
                continue;

            if (temp.type != Tokenizer::TokenType::Number)
            {
                logError("Unexpected type in '*' operation.");
                return ExpressionNode{monostate{}, Tokenizer::TokenType::Null};
            }

            mul *= get<Number>(temp.value);
        }

        return ExpressionNode{.value = mul, .type = Tokenizer::TokenType::Number};
    }
    case Tokenizer::TokenType::Minus:
    {
        if (vec.size() < 2)
        {
            logError("'-' operation requires at least one operand.");
            return ExpressionNode{monostate{}, Tokenizer::TokenType::Null};
        }

        // Evaluate the first operand
        auto temp = evaluate(vec[1]);
        if (temp.type != Tokenizer::TokenType::Number)
        {
            logError("Unexpected type for first operand in '-' operation.");
            return ExpressionNode{monostate{}, Tokenizer::TokenType::Null};
        }

        Number diff = get<Number>(temp.value);

        // Subtract subsequent operands
        for (size_t i = 2; i < vec.size(); i++)
        {
            auto temp = evaluate(vec[i]);

            // Skip NoContribution or Null values
            if (temp.type == Tokenizer::TokenType::Null)
                continue;

            if (temp.type != Tokenizer::TokenType::Number)
            {
                logError("Unexpected type in '-' operation.");
                return ExpressionNode{monostate{}, Tokenizer::TokenType::Null};
            }

            diff -= get<Number>(temp.value);
        }

        return ExpressionNode{.value = diff, .type = Tokenizer::TokenType::Number};
    }
    case Tokenizer::TokenType::Divide:
    {
        // Ensure at least one operand is present
        if (vec.size() < 2)
        {
            logError("'/' operation requires at least one operand.");
            return ExpressionNode{monostate{}, Tokenizer::TokenType::Null};
        }

        // Evaluate the first operand
        auto temp = evaluate(vec[1]);
        if (temp.type != Tokenizer::TokenType::Number)
        {
            logError("Unexpected type for first operand in '/' operation.");
            return ExpressionNode{monostate{}, Tokenizer::TokenType::Null};
        }

        Number div = get<Number>(temp.value);

        // Divide by subsequent operands
        for (size_t i = 2; i < vec.size(); i++)
        {
            auto temp = evaluate(vec[i]);

            // Skip NoContribution or Null values
            if (temp.type == Tokenizer::TokenType::Null)
                continue;

            if (temp.type != Tokenizer::TokenType::Number)
            {
                logError("Unexpected type in '/' operation.");
                return ExpressionNode{monostate{}, Tokenizer::TokenType::Null};
            }

            Number divisor = get<Number>(temp.value);

            // Handle division by zero
            if (divisor == 0)
            {
                logError("Division by zero encountered.");
                return ExpressionNode{monostate{}, Tokenizer::TokenType::Null};
            }

            div /= divisor;
        }

        return ExpressionNode{.value = div, .type = Tokenizer::TokenType::Number};
    }

    default:
        logError("Unknown or unsupported operation.");
        return ExpressionNode{monostate{}, Tokenizer::TokenType::Null};
    }
}
