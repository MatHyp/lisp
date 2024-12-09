#include <cassert>
#include <iostream>

#include "Runtime.h"
#include "FuncImpl.h"

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

ExpressionNode RunTime::handleFunctionDefinition(vector<ExpressionNode> &vec)
{
    if (vec.size() <= 3)
    {
        logError("Function definition requires at least 4 elements.");
        return ExpressionNode{monostate{}, Tokenizer::TokenType::Null}; // No contribution to result
    }

    if (vec[1].value.index() != 1 || vec[1].type != Tokenizer::TokenType::Identifier)
    {
        logError("Function definition requires a valid identifier.");
        return ExpressionNode{monostate{}, Tokenizer::TokenType::Null}; // No contribution to result
    }

    // return evaluate(vec[2]);

    FuncImpl function = FuncImpl(vec[2], vec[3]);
    globalFunctions[get<string>(vec[1].value)] = function;

    return ExpressionNode{monostate{}, Tokenizer::TokenType::Null};
}

// Handle `set` operations
ExpressionNode RunTime::handleSetOperation(const vector<ExpressionNode> &vec)
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

    globalVariables[get<string>(vec[1].value)] = vec[2];
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
            // Check global functions

            if (globalFunctions.count(get<string>(expr.value)))
            {

                // globalFunctions[get<string>(expr.value)].evaluateFunc(expr);

                auto &funcImpl = globalFunctions[get<std::string>(expr.value)];
                funcImpl.evaluateFunc(expr); // This
                return evaluate(globalFunctions[get<string>(expr.value)].instructions);
            }

            if (globalVariables.count(get<string>(expr.value)))
            {
                return globalVariables.at(get<string>(expr.value));
            }
            logError("Undefined variable: ");
            return ExpressionNode{monostate{}, Tokenizer::TokenType::Null};
        }
        return expr;
    }

    auto &vec = get<std::vector<ExpressionNode>>(expr.value);
    assert(!vec.empty());

    auto &fn = vec[0];

    if (fn.type == Tokenizer::TokenType::Func)
        return handleFunctionDefinition(vec);

    if (fn.type == Tokenizer::TokenType::set)
        return handleSetOperation(vec);

    if (fn.type == Tokenizer::TokenType::Plus || fn.type == Tokenizer::TokenType::Multiply ||
        fn.type == Tokenizer::TokenType::Minus || fn.type == Tokenizer::TokenType::Divide)
        return handleArithmeticOperation(vec, fn.type);

    logError("Unknown operation.");
    return ExpressionNode{monostate{}, Tokenizer::TokenType::Null};
}
