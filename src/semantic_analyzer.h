#ifndef SEMANTIC_ANALYZER_H
#define SEMANTIC_ANALYZER_H
#include <string>
#include <vector>
#include <unordered_set>
#include "types.h"
#include "symbol_table.h"
#include "quadruple_generator.h"
#include "error_handler.h"

class SemanticAnalyzer
{
private:
    SymbolTable *symTable;
    QuadrupleGenerator *quadGen;
    ErrorHandler *errorHandler;
    vector<unordered_set<string>> switchCaseLabel;
    vector<bool> switchHasDefault;

    int typeRank(Type t) const;
    Type promoteType(Type a, Type b) const;

    bool isIntegerType(Type t) const;
    int loopDepth = 0;

    int switchDepth = 0;

    Type currentFunctionReturnType = Type::VOID;

    bool insideFunction = false;

public:
    SemanticAnalyzer(SymbolTable *st, QuadrupleGenerator *qg, ErrorHandler *eh);
    Type checkBinaryOper(ExprAttr &left, ExprAttr &right, const string &op, int line);
    Type checkUnaryOper(const ExprAttr &expr, const string &op, int line);
    bool coerce(ExprAttr &expr, Type targetType, int line);
    bool validateAssignment(ExprAttr rhs, Type lhsType, int line);
    ExprAttr resolveIdentifier(const string &symbol_name, int line);
    void markExpressionAsRead(const ExprAttr &expr);
    void markArgumentsAsRead(const vector<ExprAttr> &args);
    Type validateFunctionCall(const string &name, vector<ExprAttr> &args, int line);
    bool validateReturn(Type expected, ExprAttr *value, int line);
    bool checkAssignable(const string &name, int line);
    bool validateBreak(int line);
    bool validateContinue(int line);
    void enterSwitchContext();
    void leaveSwitchContext();
    void enterLoop();
    void exitLoop();
    void enterSwitch();
    void exitSwitch();
    void beginSwitchCaseTracking();
    void endSwitchCaseTracking();
    bool validateCaseLabel(const ExprAttr &label, int line);
    bool validateDefaultLabel(int line);
    void setCurrentFunction(Type returnType);
    void clearCurrentFunction();
    Type getCurrentFunctionReturnType() const;
};

#endif
