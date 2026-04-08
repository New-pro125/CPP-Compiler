#ifndef ERROR_HANDLER_H
#define ERROR_HANDLER_H
#include <vector>
#include <string>

enum ErrorType
{
    Semantic,
    Syntax,
    Warning,
    Unknown,
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
    std::vector<CompilerError> errors;

public:
    void addSyntaxError(int line, const std::string &msg);
    void addSemanticError(int line, const std::string &msg);
    void addWarning(int line, const std::string &msg);
    bool hasErrors() const;
    const std::vector<CompilerError> &getErrors() const;
    void print() const;
};

#endif