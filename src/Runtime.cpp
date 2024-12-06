#include <cassert>
#include "Runtime.h"
#include <iostream>

RunTime::RunTime(Expression &expr) : expr(expr) {}

void RunTime::logError(const std::string &message)
{
    std::cerr << "Runtime Warning: " << message << std::endl;
}

void RunTime::run()
{
    for (size_t i = 0; i < expr.size(); i++)
    {
        std::cout << evaluate(expr[i]) << std::endl;
    }
}

// Evaluate an operand: either a literal or a resolved identifier
Number RunTime::evaluateOperand(const ExpressionNode &node)
{
    auto temp = evaluate(const_cast<ExpressionNode &>(node)); // Evaluate node if necessary

    if (temp.type != Tokenizer::TokenType::Number)
    {
        logError("Operand is not a valid number.");
        throw std::runtime_error("Operand evaluation failed.");
    }

    return get<Number>(temp.value);
}

// Handle `set` operations
ExpressionNode RunTime::handleSetOperation(std::vector<ExpressionNode> &vec)
{
    if (vec.size() != 3 || vec[0].type != Tokenizer::TokenType::set || vec[1].type != Tokenizer::TokenType::Identifier)
    {
        logError("Invalid 'set' operation format.");
        return ExpressionNode{monostate{}, Tokenizer::TokenType::Null};
    }

    if (vec[2].type != Tokenizer::TokenType::Number)
    {
        logError("Assigned value must be a number.");
        return ExpressionNode{monostate{}, Tokenizer::TokenType::Null};
    }

    std::string varName = get<std::string>(vec[1].value);
    variables[varName] = vec[2];
    return ExpressionNode{monostate{}, Tokenizer::TokenType::Null}; // No contribution to result
}

// Handle generic arithmetic operations
ExpressionNode RunTime::handleArithmeticOperation(std::vector<ExpressionNode> &vec, Tokenizer::TokenType operationType)
{
    switch (operationType)
    {
    case Tokenizer::TokenType::Plus:
        return handleAddition(vec);
    case Tokenizer::TokenType::Multiply:
        return handleMultiplication(vec);
    case Tokenizer::TokenType::Minus:
        return handleSubtraction(vec);
    case Tokenizer::TokenType::Divide:
        return handleDivision(vec);
    default:
        logError("Unsupported arithmetic operation.");
        return ExpressionNode{monostate{}, Tokenizer::TokenType::Null};
    }
}

// Addition operation
ExpressionNode RunTime::handleAddition(std::vector<ExpressionNode> &vec)
{
    Number sum = 0;
    for (size_t i = 1; i < vec.size(); i++)
    {
        try
        {
            sum += evaluateOperand(vec[i]);
        }
        catch (...)
        {
        }
    }
    return ExpressionNode{.value = sum, .type = Tokenizer::TokenType::Number};
}

// Multiplication operation
ExpressionNode RunTime::handleMultiplication(std::vector<ExpressionNode> &vec)
{
    Number product = 1;
    for (size_t i = 1; i < vec.size(); i++)
    {
        try
        {
            product *= evaluateOperand(vec[i]);
        }
        catch (...)
        {
        }
    }
    return ExpressionNode{.value = product, .type = Tokenizer::TokenType::Number};
}

// Subtraction operation
ExpressionNode RunTime::handleSubtraction(std::vector<ExpressionNode> &vec)
{
    if (vec.size() < 2)
    {
        logError("'-' operation requires at least one operand.");
        return ExpressionNode{monostate{}, Tokenizer::TokenType::Null};
    }

    Number diff = evaluateOperand(vec[1]);
    for (size_t i = 2; i < vec.size(); i++)
    {
        try
        {
            diff -= evaluateOperand(vec[i]);
        }
        catch (...)
        {
        }
    }
    return ExpressionNode{.value = diff, .type = Tokenizer::TokenType::Number};
}

// Division operation
ExpressionNode RunTime::handleDivision(std::vector<ExpressionNode> &vec)
{
    if (vec.size() < 2)
    {
        logError("'/' operation requires at least one operand.");
        return ExpressionNode{monostate{}, Tokenizer::TokenType::Null};
    }

    Number quotient = evaluateOperand(vec[1]);
    for (size_t i = 2; i < vec.size(); i++)
    {
        try
        {
            Number divisor = evaluateOperand(vec[i]);
            if (divisor == 0)
            {
                logError("Division by zero.");
                return ExpressionNode{monostate{}, Tokenizer::TokenType::Null};
            }
            quotient /= divisor;
        }
        catch (...)
        {
        }
    }
    return ExpressionNode{.value = quotient, .type = Tokenizer::TokenType::Number};
}

// Main evaluation logic
ExpressionNode RunTime::evaluate(ExpressionNode &expr)
{
    if (expr.value.index() != 2)
    {
        if (expr.value.index() == 1 && expr.type == Tokenizer::TokenType::Identifier)
        {
            std::string varName = get<std::string>(expr.value);
            if (variables.count(varName))
            {
                return variables.at(varName);
            }
            logError("Undefined variable: " + varName);
            return ExpressionNode{monostate{}, Tokenizer::TokenType::Null};
        }
        return expr;
    }

    auto &vec = get<std::vector<ExpressionNode>>(expr.value);
    assert(!vec.empty());

    auto &fn = vec[0];
    if (fn.type == Tokenizer::TokenType::set)
        return handleSetOperation(vec);

    if (fn.type == Tokenizer::TokenType::Plus || fn.type == Tokenizer::TokenType::Multiply ||
        fn.type == Tokenizer::TokenType::Minus || fn.type == Tokenizer::TokenType::Divide)
        return handleArithmeticOperation(vec, fn.type);

    logError("Unknown operation.");
    return ExpressionNode{monostate{}, Tokenizer::TokenType::Null};
}
