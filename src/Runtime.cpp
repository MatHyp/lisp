#include <cassert>
#include "Runtime.h"

RunTime::RunTime(Expression &expr) : expr(expr) {}

void RunTime::logError(const std::string &message)
{
    std::cerr << "Runtime Warning: " << message << std::endl;
}

ExpressionNode RunTime::evaluateNonVector(ExpressionNode &expr)
{
    if (expr.value.index() == 1 && expr.type == Tokenizer::TokenType::Identifier)
    {
        // Check global functions
        auto identifier = get<string>(expr.value);
        if (globalFunctions.count(identifier))
        {
            return evaluate(globalFunctions[identifier].instructions);
        }

        // Check variables
        if (variables.count(identifier) == 0)
        {
            logError("Undefined variable: " + identifier);
            return ExpressionNode{.value = Number(0), .type = Tokenizer::TokenType::Number};
        }
        return variables.at(identifier);
    }
    return expr;
}

// Helper: Evaluate Numbers
Number RunTime::evaluateNumber(const ExpressionNode &item)
{
    if (item.value.index() == 2)
    {
        auto temp = evaluate(const_cast<ExpressionNode &>(item)); // Remove const qualifier
        if (temp.value.index() != 0)
        {
            logError("Expected a number after evaluation, but found something else.");
            return 0; // Return default value
        }
        return get<Number>(temp.value);
    }
    else if (item.value.index() == 0)
    {
        return get<Number>(item.value);
    }
    else
    {
        logError("Item is not a number!");
        return 0;
    }
}

ExpressionNode RunTime::evaluateBinaryOperation(const vector<ExpressionNode> &vec, Tokenizer::TokenType operation)
{
    if (vec.size() < 2)
    {
        logError("Insufficient arguments for binary operation.");
        return ExpressionNode{.value = Number(0), .type = Tokenizer::TokenType::Number};
    }

    Number result = evaluateNumber(vec[1]);
    for (size_t i = 2; i < vec.size(); i++)
    {
        Number val = evaluateNumber(vec[i]);
        switch (operation)
        {
        case Tokenizer::TokenType::Plus:
            result += val;
            break;
        case Tokenizer::TokenType::Minus:
            result -= val;
            break;
        case Tokenizer::TokenType::Multiply:
            result *= val;
            break;
        case Tokenizer::TokenType::Divide:
            if (val == 0)
            {
                logError("Division by zero. Skipping this operation.");
                continue;
            }
            result /= val;
            break;
        default:
            logError("Unsupported operation.");
            return ExpressionNode{.value = Number(0), .type = Tokenizer::TokenType::Number};
        }
    }
    return ExpressionNode{.value = result, .type = Tokenizer::TokenType::Number};
}

ExpressionNode RunTime::handleSetOperation(const vector<ExpressionNode> &vec)
{
    if (vec.size() != 3)
    {
        logError("Invalid number of arguments for 'set' operation.");
        return ExpressionNode{.value = Number(0), .type = Tokenizer::TokenType::Number};
    }

    if (vec[1].value.index() != 1 || vec[1].type != Tokenizer::TokenType::Identifier)
    {
        logError("The first argument of 'set' must be an identifier.");
        return ExpressionNode{.value = Number(0), .type = Tokenizer::TokenType::Number};
    }

    string variableName = get<string>(vec[1].value);

    // Create a mutable copy of vec[2] for evaluation
    ExpressionNode mutableNode = vec[2];
    ExpressionNode value = evaluate(mutableNode);

    // Assign the evaluated value to the variable
    variables[variableName] = value;

    return value;
}

void RunTime::handleFunctionDefinition(const vector<ExpressionNode> &vec)
{
    if (vec.size() <= 3)
    {
        logError("Function definition requires at least 4 elements.");
        return;
    }

    if (vec[1].value.index() != 1 || vec[1].type != Tokenizer::TokenType::Identifier)
    {
        logError("Function definition requires a valid identifier.");
        return;
    }

    FuncStruct functionStructOnStack;
    functionStructOnStack.args = vec[2];
    functionStructOnStack.instructions = vec[3];

    string funcName = get<string>(vec[1].value);
    globalFunctions[funcName] = functionStructOnStack;
}

ExpressionNode RunTime::evaluate(ExpressionNode &expr)
{
    // Evaluate variables and funcions calls
    if (expr.value.index() != 2)
    {
        return evaluateNonVector(expr);
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
    case Tokenizer::TokenType::Multiply:
    case Tokenizer::TokenType::Minus:
    case Tokenizer::TokenType::Divide:
        return evaluateBinaryOperation(vec, fn.type);

    case Tokenizer::TokenType::set:
        return handleSetOperation(vec);

    case Tokenizer::TokenType::Func:
        handleFunctionDefinition(vec);
        return ExpressionNode{};
        break;
    default:
        assert(!"This is not supposed to happen!");
    }
}

void RunTime::run()
{
    for (size_t i = 0; i < expr.size(); i++)
    {
        try
        {
            cout << this->evaluate(expr[i]) << endl;
        }
        catch (const std::exception &e)
        {
            logError(e.what());
        }
    }
}