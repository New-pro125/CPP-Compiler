#ifndef ERROR_HANDLER_H
#define ERROR_HANDLER_H
#include <map>
#include <string>
using namespace std;
enum ErrorType
{
    Warning = 0,
    Syntax = 1,
    Semantic = 2,
};
struct CompilerError
{
    int line = -1;
    string message;
    ErrorType errorType = ErrorType::Warning;
};

class ErrorHandler
{
private:
    multimap<pair<int, int>, CompilerError> errors;

public:
    void addSyntaxError(int line, const string &msg);
    void addSemanticError(int line, const string &msg);
    void addWarning(int line, const string &msg);
    bool hasErrors() const;
    void print() const;
};

#endif
