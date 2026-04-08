#include "error_handler.h"

#include <iostream>

void ErrorHandler::addSemanticError(int line, const std::string &msg)
{
    auto error = CompilerError{
        line, msg, ErrorType::Semantic};
    this->errors.emplace_back(error);
}
void ErrorHandler::addSyntaxError(int line, const std::string &msg)
{
    auto error = CompilerError{
        line, msg, ErrorType::Syntax};
    this->errors.emplace_back(error);
}
void ErrorHandler::addWarning(int line, const std::string &msg)
{
    auto error = CompilerError{
        line, msg, ErrorType::Warning};
    this->errors.emplace_back(error);
}
bool ErrorHandler::hasErrors() const
{
    for (const auto &e : errors)
    {
        if (e.errorType == ErrorType::Semantic || e.errorType == ErrorType::Syntax)
        {
            return true;
        }
    }
    return false;
}
const std::vector<CompilerError> &ErrorHandler::getErrors() const
{
    return errors;
}
void ErrorHandler::print() const
{
    for (const auto &e : errors)
    {
        if (e.errorType == ErrorType::Warning)
        {
            std::cout << "\033[33m" << "Warning at Line" << e.line << ": " << e.message << "\n";
            std::cout << "\033[0m";
        }
        std::string error_type = (e.errorType == ErrorType::Semantic) ? "Semantic" : "Syntax";
        std::cout << "\033[31m" << error_type << " Error at Line" << e.line << ": " << e.message << "\n";
        std::cout << "\033[0m";
    }
}