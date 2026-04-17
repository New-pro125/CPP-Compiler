#ifndef PARSER_CONTEXT_H
#define PARSER_CONTEXT_H

#include "symbol_table.h"
#include "semantic_analyzer.h"
#include "quadruple_generator.h"
#include "error_handler.h"

struct SwitchCaseDispatch
{
    std::string literalPlace;
    std::string caseLabel;
};

struct SwitchContext
{
    std::string exprPlace;
    Type exprType = Type::UNKNOWN;
    std::vector<SwitchCaseDispatch> dispatchCases;
    std::string dispatchLabel;
    std::string defaultLabel;
    std::vector<bool> skipCaseStack;
};

struct FunctionParamSpec
{
    Type dataType = Type::UNKNOWN;
    std::string name;
    std::string defaultValue;
    bool isConst = false;
};

struct FunctionParamContext
{
    std::vector<FunctionParamSpec> params;
    bool hasError = false;
};

struct CurrentFunctionContext
{
    bool inFn = false;
    std::string name;
    Type returnType = Type::VOID;
    FunctionParamContext params;
    bool isInvalid = false;
    bool isSuppressed = false;
    bool isInserted = false;
    int quadStart = -1;
};

struct ParserContext
{
    SymbolTable *symTable = nullptr;
    SemanticAnalyzer *semAnalyzer = nullptr;
    QuadrupleGenerator *quadGenerator = nullptr;
    ErrorHandler *errHandler = nullptr;
    bool currDeclConst = false;
    Type currDeclType = Type::UNKNOWN;
    int loopDepth = 0, switchDepth = 0;
    CurrentFunctionContext currFunction;
    std::vector<std::vector<ExprAttr>> passedArgs;
    std::vector<SwitchContext> switchContexts;
    std::vector<std::string> breakLabels, continueLabels;
};
extern ParserContext *parserContext;
#endif
