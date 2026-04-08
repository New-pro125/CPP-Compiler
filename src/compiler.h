#ifndef COMPILER_H
#define COMPILER_H
#include <string>
#include "quadruple_generator.h"
#include "error_handler.h"
class Compiler
{
private:
    QuadrupleGenerator quadGen;
    ErrorHandler errorHandler;

public:
    Compiler();
    bool compile(const std::string &sourceCode);
    void printErrors() const;
    void printQuadrapleTables() const;
    QuadrupleGenerator *getQuadrupleGenerator();
    ErrorHandler *getErrorHandler();
};
#endif