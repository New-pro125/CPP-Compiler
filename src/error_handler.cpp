#include "error_handler.h"

#include <iostream>
#include <algorithm>
void ErrorHandler::addSemanticError(int line, const std::string &msg)
{
    auto error = CompilerError{
        line, msg, ErrorType::Semantic};
    std::pair<int, int> errorKey = std::make_pair(error.line, error.errorType);
    this->errors.insert(std::make_pair(errorKey, error));
}
void ErrorHandler::addSyntaxError(int line, const std::string &msg)
{
    auto error = CompilerError{
        line, msg, ErrorType::Syntax};
    std::pair<int, int> errorKey = std::make_pair(error.line, error.errorType);
    this->errors.insert(std::make_pair(errorKey, error));
}
void ErrorHandler::addWarning(int line, const std::string &msg)
{
    auto error = CompilerError{
        line, msg, ErrorType::Warning};
    std::pair<int, int> errorKey = std::make_pair(error.line, error.errorType);
    this->errors.insert(std::make_pair(errorKey, error));
}
bool ErrorHandler::hasErrors() const
{
    for (const auto &[_, v] : errors)
    {
        if (v.errorType == ErrorType::Semantic || v.errorType == ErrorType::Syntax)
        {
            return true;
        }
    }
    return false;
}
const std::multimap<std::pair<int, int>, CompilerError> &ErrorHandler::getErrors() const
{
    return errors;
}
void ErrorHandler::print() const
{
    // Not Optimized

    for (const auto &[_, v] : this->errors)
    {
        if (v.errorType == ErrorType::Warning)
        {
            std::cout << "\033[33m" << "Warning at Line " << v.line << ": " << v.message << "\n";
            std::cout << "\033[0m";
        }
        else
        {
            std::string error_type = (v.errorType == ErrorType::Semantic) ? "Semantic" : "Syntax";
            std::cout << "\033[31m" << error_type << " Error at Line " << v.line << ": " << v.message << "\n";
            std::cout << "\033[0m";
        }
    }
}