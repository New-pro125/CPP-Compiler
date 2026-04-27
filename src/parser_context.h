#ifndef PARSER_CONTEXT_H
#define PARSER_CONTEXT_H

#include "symbol_table.h"
#include "semantic_analyzer.h"
#include "quadruple_generator.h"
#include "error_handler.h"

struct SwitchCaseDispatch
{
    string literalPlace;
    string caseLabel;
    SwitchCaseDispatch() = default;
    SwitchCaseDispatch(const string &literalPlace, const string &caseLabel)
        : literalPlace(literalPlace), caseLabel(caseLabel) {}
};

struct SwitchContext
{
    string exprPlace;
    Type exprType = Type::UNKNOWN;
    vector<SwitchCaseDispatch> dispatchCases;
    string dispatchLabel;
    string defaultLabel;
    vector<bool> skipCase;
    bool isInvalid = false;
    SwitchContext() = default;
    SwitchContext(const string &exprPlace,
                  const string &dispatchLabel,
                  const string &defaultLabel = "",
                  Type exprType = Type::UNKNOWN)
        : exprPlace(exprPlace), exprType(exprType), dispatchCases(), dispatchLabel(dispatchLabel), defaultLabel(defaultLabel), skipCase() {}
};

struct FunctionParamSpec
{
    Type dataType;
    string name;
    string defaultValue;
    bool isConst;
    FunctionParamSpec() : dataType(Type::UNKNOWN), name(), defaultValue(), isConst(false) {}
    FunctionParamSpec(const string &name,
                      const string &defaultValue,
                      Type dataType = Type::UNKNOWN,
                      bool isConst = false)
        : dataType(dataType), name(name), defaultValue(defaultValue), isConst(isConst) {}
};

struct FunctionParamContext
{
    vector<FunctionParamSpec> params;
    bool hasError;
    FunctionParamContext() : params(), hasError(false) {}
};

struct CurrentFunctionContext
{
    bool inFn;
    string name;
    FunctionParamContext params;
    bool isInvalid;
    bool isSuppressed;
    bool isInserted;
    int quadStart;
    CurrentFunctionContext()
        : inFn(false), name(), params(), isInvalid(false), isSuppressed(false), isInserted(false), quadStart(-1) {}
    CurrentFunctionContext(const string &name,
                           const FunctionParamContext &params,
                           bool inFn = false,
                           bool isInvalid = false,
                           bool isSuppressed = false,
                           bool isInserted = false,
                           int quadStart = -1)
        : inFn(inFn), name(name), params(params), isInvalid(isInvalid), isSuppressed(isSuppressed), isInserted(isInserted), quadStart(quadStart) {}
};

struct ParserContext
{
    SymbolTable *symTable = nullptr;
    SemanticAnalyzer *semAnalyzer = nullptr;
    QuadrupleGenerator *quadGenerator = nullptr;
    ErrorHandler *errHandler = nullptr;
    bool currDeclConst = false;
    Type currDeclType = Type::UNKNOWN;
    CurrentFunctionContext currFunction;
    vector<vector<ExprAttr>> passedArgs;
    vector<SwitchContext> switchContexts;
    vector<string> breakLabels, continueLabels;
};
extern ParserContext *parserContext;
#endif
