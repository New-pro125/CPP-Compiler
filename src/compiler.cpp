#include "compiler.h"

/**
 * the section below used to integrate bison parsing engine into the compiler code
 */
extern int yyparse();
extern int yylineno;
struct yy_buffer_state;
typedef struct yy_buffer_state *YY_BUFFER_STATE;
extern YY_BUFFER_STATE yy_scan_string(const char *str);
extern void yy_delete_buffer(YY_BUFFER_STATE buf);

Compiler::Compiler()
{
    this->errorHandler = ErrorHandler();
    this->quadGen = QuadrupleGenerator();
}

bool Compiler::compile(const std::string &sourceCode)
{
    yylineno = 1;
    YY_BUFFER_STATE buffer = yy_scan_string(sourceCode.c_str());
    const int parseResult = yyparse();
    yy_delete_buffer(buffer);
    return parseResult == 0 && !this->errorHandler.hasErrors();
}

void Compiler::printErrors() const
{
    this->errorHandler.print();
}
void Compiler::printQuadrapleTables() const
{
    this->quadGen.print();
}
QuadrupleGenerator *Compiler::getQuadrupleGenerator()
{
    return &this->quadGen;
}
ErrorHandler *Compiler::getErrorHandler()
{
    return &this->errorHandler;
}