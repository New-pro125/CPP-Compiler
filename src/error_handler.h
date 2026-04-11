#ifndef ERROR_HANDLER_H
#define ERROR_HANDLER_H
#include <map>
#include <string>

enum ErrorType
{
    Warning = 0,
    Syntax = 1,
    Semantic = 2,
    Unknown = 3,
};
struct CompilerError
{
    int line = -1;
    std::string message;
    ErrorType errorType = ErrorType::Warning;
};

class ErrorHandler
{
private:
    std::multimap<std::pair<int, int>, CompilerError> errors;

public:
    void addSyntaxError(int line, const std::string &msg);
    void addSemanticError(int line, const std::string &msg);
    void addWarning(int line, const std::string &msg);
    bool hasErrors() const;
    const std::multimap<std::pair<int, int>, CompilerError> &getErrors() const;
    void print() const;
};

#endif