#ifndef COMPILER_H
#define COMPILER_H
#include <string>
#include "quadruple_generator.h"
#include "error_handler.h"
#include "symbol_table.h"
#include "semantic_analyzer.h"
#include "parser_context.h"
class Compiler
{
private:
    QuadrupleGenerator quadGen;
    ErrorHandler errorHandler;
    SymbolTable symTable;
    SemanticAnalyzer semanticAnalyzer;
    ParserContext ctx;

public:
    Compiler();
    bool compile(const std::string &sourceCode);
    void printErrors() const;
    void printQuadrapleTables() const;
    QuadrupleGenerator *getQuadrupleGenerator();
    ErrorHandler *getErrorHandler();
    SymbolTable *getSymbolTable();
    void printSymbolTable();
    SemanticAnalyzer *getSemanticAnalyzer();
};
#endif
