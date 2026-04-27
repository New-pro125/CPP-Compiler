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

ParserContext *parserContext = nullptr;

Compiler::Compiler()
    : quadGen(),
      errorHandler(),
      symTable(),
      semanticAnalyzer(&symTable, &quadGen, &errorHandler)
{
    this->ctx.symTable = &this->symTable;
    this->ctx.semAnalyzer = &this->semanticAnalyzer;
    this->ctx.quadGenerator = &this->quadGen;
    this->ctx.errHandler = &this->errorHandler;
}

bool Compiler::compile(const std::string &sourceCode)
{
    parserContext = &this->ctx;
    yylineno = 1;
    YY_BUFFER_STATE buffer = yy_scan_string(sourceCode.c_str());
    const int parseResult = yyparse();
    yy_delete_buffer(buffer);

    quadGen.replaceNames(symTable.getRenameEvents());

    // check unused symbols and give warnings
    std::vector<Symbol> unused = symTable.getUnusedSymbolsInCurrentScope();
    for (const auto &sym : unused)
        errorHandler.addWarning(sym.declaredLine,
                                "Variable '" + sym.irName + "' declared but never used");
    parserContext = nullptr;
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
void Compiler::printSymbolTable()
{
    this->symTable.printSymbolTable();
}

SymbolTable *Compiler::getSymbolTable()
{
    return &symTable;
}

SemanticAnalyzer *Compiler::getSemanticAnalyzer()
{
    return &semanticAnalyzer;
}
