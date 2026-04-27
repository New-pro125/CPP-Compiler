#include "error_handler.h"

#include <iostream>
#include <algorithm>
void ErrorHandler::addSemanticError(int line, const string &msg)
{
    auto error = CompilerError{
        line, msg, ErrorType::Semantic};
    pair<int, int> errorKey = make_pair(error.line, error.errorType);
    this->errors.insert(make_pair(errorKey, error));
}
void ErrorHandler::addSyntaxError(int line, const string &msg)
{
    auto error = CompilerError{
        line, msg, ErrorType::Syntax};
    pair<int, int> errorKey = make_pair(error.line, error.errorType);
    this->errors.insert(make_pair(errorKey, error));
}
void ErrorHandler::addWarning(int line, const string &msg)
{
    auto error = CompilerError{
        line, msg, ErrorType::Warning};
    pair<int, int> errorKey = make_pair(error.line, error.errorType);
    this->errors.insert(make_pair(errorKey, error));
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
void ErrorHandler::print() const
{

    for (const auto &[_, v] : this->errors)
    {
        if (v.errorType == ErrorType::Warning)
        {
            cout << "\033[33m" << "Warning at Line " << v.line << ": " << v.message << "\n";
            cout << "\033[0m";
        }
        else
        {
            string error_type = (v.errorType == ErrorType::Semantic) ? "Semantic" : "Syntax";
            cout << "\033[31m" << error_type << " Error at Line " << v.line << ": " << v.message << "\n";
            cout << "\033[0m";
        }
    }
}
