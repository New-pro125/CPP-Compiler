#ifndef PARSER_CONTEXT_H
#define PARSER_CONTEXT_H

#include "symbol_table.h"
#include "semantic_analyzer.h"
#include "quadruple_generator.h"
#include "error_handler.h"

struct ParserContext
{
    SymbolTable *symTable = nullptr;
    SemanticAnalyzer *semAnalyzer = nullptr;
    QuadrupleGenerator *quadGenerator = nullptr;
    ErrorHandler *errHandler = nullptr;
    Type currDeclType = Type::UNKNOWN;
    bool currDeclConst = false, inFn = false;
    std::string currFnName;
    Type currFnReturn = Type::VOID;
    int loopDepth = 0, switchDepth = 0;
    std::vector<Type> currParam;
    std::vector<std::string> currParamNames, currParamDefaults;
    std::vector<ExprAttr> passedArgs;
    std::vector<std::string> breakLabels, continueLabels;
};
extern ParserContext *parserContext;
#endif