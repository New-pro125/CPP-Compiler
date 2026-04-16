#include "parser_action_helpers.h"

#include <cstring>
#include <string>

#include "parser_context.h"

namespace
{
    /// This function used to create unknown expressions in case of validation failure
    ExprAttr *unknownExprFromName(const std::string &name)
    {
        auto *result = new ExprAttr(Type::UNKNOWN, name);
        return result;
    }

    bool validateDeclaratorType(ParserContext *ctx,
                                const std::string &name,
                                int line)
    {
        if (ctx->currDeclType == Type::VOID)
        {
            ctx->errHandler->addSemanticError(line,
                                              "Identifier '" + name + "' cannot have  " + typeToString(ctx->currDeclType) + "' type");
            return false;
        }
        return true;
    }

    struct DoWhileLabels
    {
        std::string startLabel;
        std::string condLabel;
        std::string endLabel;
    };

    struct ForLabels
    {
        std::string condLabel;
        std::string bodyLabel;
        std::string updateLabel;
        std::string endLabel;
    };
    /// @brief split the do while labels out packed expression
    /// @param packed const char * contains do while labels
    /// @return DoWhileLabels with labels separated
    DoWhileLabels unpackDoWhileLabels(const char *packed)
    {
        std::string labels = packed ? packed : "";
        std::size_t p1 = labels.find(',');
        std::size_t p2 = labels.find(',', p1 == std::string::npos ? 0 : p1 + 1);
        if (p1 == std::string::npos || p2 == std::string::npos)
        {
            return DoWhileLabels{};
        }
        return DoWhileLabels{
            labels.substr(0, p1),
            labels.substr(p1 + 1, p2 - p1 - 1),
            labels.substr(p2 + 1)};
    }
    /// @brief split the packed labels into cond, body, update, end labels
    /// @param packed
    /// @return ForLabels
    ForLabels unpackForLabels(const char *packed)
    {
        std::string labels = packed ? packed : "";
        std::size_t p1 = labels.find(',');
        std::size_t p2 = labels.find(',', p1 == std::string::npos ? 0 : p1 + 1);
        std::size_t p3 = labels.find(',', p2 == std::string::npos ? 0 : p2 + 1);
        if (p1 == std::string::npos || p2 == std::string::npos || p3 == std::string::npos)
        {
            return ForLabels{};
        }
        return ForLabels{
            labels.substr(0, p1),
            labels.substr(p1 + 1, p2 - p1 - 1),
            labels.substr(p2 + 1, p3 - p2 - 1),
            labels.substr(p3 + 1)};
    }
}

/// @brief check the type of condition expression if bool or not
/// @param ctx
/// @param conditionExpr
/// @param line
/// @return true if coditionExpr is boolean-like type
bool validateAndCoerceConditionExpr(ParserContext *ctx, ExprAttr *conditionExpr, int line)
{
    if (conditionExpr == nullptr || conditionExpr->type == Type::UNKNOWN || conditionExpr->type == Type::STRING || conditionExpr->type == Type::VOID)
    {
        std::string actualType = (conditionExpr == nullptr) ? "unknown" : typeToString(conditionExpr->type);
        ctx->errHandler->addSemanticError(
            line,
            "Invalid condition type '" + actualType + "' in conditional expression");
        return false;
    }
    if (conditionExpr->type != Type::BOOL)
    {
        return ctx->semAnalyzer->coerce(*conditionExpr, Type::BOOL, line);
    }
    return true;
}
/// @brief emit the required jump quadruple if conditionExpr is boolean
/// @param ctx
/// @param conditionExpr
/// @param jumpOp
/// @param targetLabel
/// @param line
void emitGuardedConditionalJump(ParserContext *ctx, ExprAttr *conditionExpr, const std::string &jumpOp, const std::string &targetLabel, int line)
{
    ctx->quadGenerator->emit(validateAndCoerceConditionExpr(ctx, conditionExpr, line) ? jumpOp : "JMP", conditionExpr ? conditionExpr->place : "-", "-", targetLabel);
}

/// @brief validate if the binary expression lhs and rhs can use the binary operator
/// @param ctx
/// @param lhs
/// @param rhs
/// @param semanticOp the name of operators as used in `Semantic Analyzer`
/// @param irOp the name of operators as emitted as quadruple
/// @param line
/// @return new ExprAttr
ExprAttr *makeBinaryExpr(ParserContext *ctx,
                         ExprAttr *lhs,
                         ExprAttr *rhs,
                         const std::string &semanticOp,
                         const std::string &irOp,
                         int line)
{
    Type t = ctx->semAnalyzer->checkBinaryOper(*lhs, *rhs, semanticOp, line);
    std::string temp;
    if (t != Type::UNKNOWN)
    {
        temp = ctx->quadGenerator->newTemp();
        ctx->quadGenerator->emit(irOp, lhs->place, rhs->place, temp);
    }

    delete lhs;
    delete rhs;

    auto *result = new ExprAttr();
    result->place = temp;
    result->type = t;
    return result;
}

/// @brief checks if identifier can be assigned to given expression
/// @param ctx
/// @param identifier
/// @param rhsExpr
/// @param line
/// @return new Expression if id to be assigned else new unknown ExprAttr
ExprAttr *makeAssignExpr(ParserContext *ctx,
                         const char *identifier,
                         ExprAttr *rhsExpr,
                         int line)
{
    const std::string name(identifier);
    bool isAssignable = ctx->semAnalyzer->checkAssignable(name, line);

    ExprAttr rhs = *rhsExpr;
    delete rhsExpr;

    Symbol *sym = ctx->symTable->lookup(name);
    bool typeOk = false;

    if (isAssignable && sym)
    {
        typeOk = ctx->semAnalyzer->validateAssignment(rhs, sym->dataType, line);
        if (typeOk)
        {
            ctx->semAnalyzer->coerce(rhs, sym->dataType, line);
            sym->isInitialized = true;
            ctx->quadGenerator->emit("ASSIGN", rhs.place, "-", sym->irName);
            auto *result = new ExprAttr(sym->dataType, sym->irName, false, sym->isConst, &sym->isUsed);
            return result;
        }
    }
    return unknownExprFromName(name);
}

ExprAttr *makeCompoundAssignExpr(ParserContext *ctx,
                                 const char *identifier,
                                 ExprAttr *rhsExpr,
                                 const std::string &semanticOp,
                                 const std::string &irOp,
                                 int line)
{
    const std::string name(identifier);
    bool isAssignable = ctx->semAnalyzer->checkAssignable(name, line);

    ExprAttr rhs = *rhsExpr;
    delete rhsExpr;

    if (isAssignable)
    {
        ExprAttr lhs = ctx->semAnalyzer->resolveIdentifier(name, line);
        Type resultType = ctx->semAnalyzer->checkBinaryOper(lhs, rhs, semanticOp, line);
        if (resultType != Type::UNKNOWN)
        {
            std::string temp = ctx->quadGenerator->newTemp();
            ctx->quadGenerator->emit(irOp, lhs.place, rhs.place, temp);
            ctx->quadGenerator->emit("ASSIGN", temp, "-", lhs.place);
            auto *result = new ExprAttr(resultType, ctx->symTable->getIRName(name));
            return result;
        }
    }
    return unknownExprFromName(name);
}

ExprAttr *makePrefixIncDecExpr(ParserContext *ctx,
                               const char *identifier,
                               const std::string &op,
                               int line)
{
    const std::string name(identifier);
    bool isAssignable = ctx->semAnalyzer->checkAssignable(name, line);
    if (!isAssignable)
    {
        return unknownExprFromName(name);
    }

    ExprAttr id = ctx->semAnalyzer->resolveIdentifier(name, line);
    Type resultType = ctx->semAnalyzer->checkUnaryOper(id, op, line);
    if (resultType == Type::UNKNOWN)
    {
        if (id.isUsed)
        {
            *id.isUsed = false;
        }
        return unknownExprFromName(name);
    }

    ctx->quadGenerator->emit(op, id.place, "-", id.place);
    if (id.isUsed)
    {
        *id.isUsed = true;
    }

    auto *result = new ExprAttr(id.type, id.place, id.isLvalue, id.isConst, id.isUsed);
    return result;
}

ExprAttr *makePostfixIncDecExpr(ParserContext *ctx,
                                const char *identifier,
                                const std::string &op,
                                int line)
{
    const std::string name(identifier);
    bool isAssignable = ctx->semAnalyzer->checkAssignable(name, line);
    if (!isAssignable)
    {
        return unknownExprFromName(name);
    }

    ExprAttr id = ctx->semAnalyzer->resolveIdentifier(name, line);
    Type resultType = ctx->semAnalyzer->checkUnaryOper(id, op, line);
    if (resultType == Type::UNKNOWN)
    {
        if (id.isUsed)
        {
            *id.isUsed = false;
        }
        return unknownExprFromName(name);
    }

    std::string temp = ctx->quadGenerator->newTemp();
    ctx->quadGenerator->emit("ASSIGN", id.place, "-", temp);
    ctx->quadGenerator->emit(op, id.place, "-", id.place);
    if (id.isUsed)
    {
        *id.isUsed = true;
    }

    auto *result = new ExprAttr(id.type, temp, id.isLvalue, id.isConst, id.isUsed);
    return result;
}

ExprAttr *makeUnaryExpr(ParserContext *ctx,
                        ExprAttr *operand,
                        const std::string &semanticOp,
                        const std::string &irOp,
                        int line,
                        Type successType)
{
    Type t = ctx->semAnalyzer->checkUnaryOper(*operand, semanticOp, line);

    auto *result = new ExprAttr();
    if (t != Type::UNKNOWN)
    {
        if ((semanticOp == "UMINUS" && operand->type == Type::CHAR) ||
            (semanticOp == "BITWISENOT" && (operand->type == Type::CHAR || operand->type == Type::BOOL)))
        {
            bool flag = ctx->semAnalyzer->coerce(*operand, Type::INT, line);
            if (flag)
                t = Type::INT;
            else
                t = Type::UNKNOWN;
        }
        if (t != Type::UNKNOWN)
        {
            std::string temp = ctx->quadGenerator->newTemp();
            ctx->quadGenerator->emit(irOp, operand->place, "-", temp);
            result->place = temp;
            result->type = (successType == Type::UNKNOWN) ? t : successType;
        }
        else
        {
            result->place = operand->place;
            result->type = Type::UNKNOWN;
        }
    }
    else
    {
        result->place = operand->place;
        result->type = Type::UNKNOWN;
    }

    delete operand;
    return result;
}

ExprAttr *makeFunctionCallExpr(ParserContext *ctx,
                               const char *functionName,
                               int line)
{
    const std::string fn(functionName);
    std::vector<ExprAttr> currentArgs = ctx->passedArgs.back();
    ctx->passedArgs.pop_back();
    Type retType = ctx->semAnalyzer->validateFunctionCall(fn, currentArgs, line);
    for (auto &arg : currentArgs)
    {
        ctx->quadGenerator->emit("PARAM", arg.place, "-", "-");
    }

    std::string temp = ctx->quadGenerator->newTemp();
    if (retType != Type::VOID)
    {
        ctx->quadGenerator->emit("CALL", fn, std::to_string(currentArgs.size()), temp);
    }
    else
    {
        ctx->quadGenerator->emit("CALL", fn, std::to_string(currentArgs.size()), "-");
    }

    auto *result = new ExprAttr(retType, temp);
    return result;
}

ExprAttr *makeIdentifierExpr(ParserContext *ctx,
                             const char *identifier,
                             int line)
{
    auto *result = new ExprAttr(ctx->semAnalyzer->resolveIdentifier(identifier, line));
    if (result->type != Type::UNKNOWN && result->isUsed)
    {
        *result->isUsed = true;
    }
    else if (result->isUsed)
    {
        *result->isUsed = false;
    }
    return result;
}

void leaveScopeWithUnusedWarnings(ParserContext *ctx)
{
    std::vector<Symbol> unused = ctx->symTable->getUnusedSymbolsInCurrentScope();
    for (const auto &sym : unused)
    {
        ctx->errHandler->addWarning(sym.declaredLine,
                                    "Variable '" + sym.irName + "' declared but never used");
    }
    ctx->symTable->LeaveScope();
}

void handleSimpleDeclarator(ParserContext *ctx,
                            const char *identifier,
                            int line)
{
    const std::string name(identifier);
    bool declTypeOk = validateDeclaratorType(ctx, name, line);
    if (ctx->currDeclConst)
    {
        ctx->semAnalyzer->checkConstInitialized(name, false, line);
    }
    if (!declTypeOk)
    {
        return;
    }

    Symbol sym;
    sym.name = name;
    sym.dataType = ctx->currDeclType;
    sym.isConst = ctx->currDeclConst;
    sym.isInitialized = false;
    sym.declaredLine = line;
    if (!ctx->symTable->insert(name, sym))
    {
        ctx->errHandler->addSemanticError(line,
                                          "Redeclaration of variable '" + name + "'");
    }
}

void handleInitializedDeclarator(ParserContext *ctx,
                                 const char *identifier,
                                 ExprAttr *initExpr,
                                 int line)
{
    const std::string name(identifier);
    if (ctx->currDeclConst)
    {
        ctx->semAnalyzer->checkConstInitialized(name, true, line);
    }

    bool declTypeOk = validateDeclaratorType(ctx, name, line);

    ExprAttr rhs = *initExpr;
    bool initOk = false;
    if (declTypeOk)
    {
        initOk = ctx->semAnalyzer->validateAssignment(*initExpr, ctx->currDeclType, line);
    }
    if (initOk)
    {
        initOk = ctx->semAnalyzer->coerce(rhs, ctx->currDeclType, line);
    }
    delete initExpr;

    if (!declTypeOk)
    {
        return;
    }

    Symbol sym;
    sym.name = name;
    sym.dataType = ctx->currDeclType;
    sym.isConst = ctx->currDeclConst;
    sym.isInitialized = initOk;
    sym.declaredLine = line;
    if (!ctx->symTable->insert(name, sym))
    {
        ctx->errHandler->addSemanticError(line,
                                          "Redeclaration of variable '" + name + "'");
    }
    if (initOk)
    {
        ctx->quadGenerator->emit("ASSIGN", rhs.place, "-", ctx->symTable->getIRName(name));
    }
}

void resetFunctionParamContext(ParserContext *ctx)
{
    ctx->currParam.clear();
    ctx->currParamConst.clear();
    ctx->currParamNames.clear();
    ctx->currParamDefaults.clear();
}

void addFunctionParam(ParserContext *ctx,
                      Type paramType,
                      const char *paramName,
                      const std::string &defaultValue,
                      bool isConst,
                      int line)
{
    if (paramType == Type::VOID)
    {
        ctx->errHandler->addSemanticError(line,
                                          "Parameter '" + std::string(paramName) + "' cannot have type '" + typeToString(paramType) + "'");
        return;
    }

    ctx->currParam.push_back(paramType);
    ctx->currParamConst.push_back(isConst);
    ctx->currParamNames.push_back(paramName);
    ctx->currParamDefaults.push_back(defaultValue);
}

void beginFunctionDefinition(ParserContext *ctx,
                             const char *functionName,
                             Type returnType,
                             int line)
{
    const std::string name(functionName);

    bool sawDefault = false;
    for (std::size_t i = 0; i < ctx->currParamDefaults.size(); i++)
    {
        if (!ctx->currParamDefaults[i].empty())
        {
            sawDefault = true;
        }
        else if (sawDefault)
        {
            ctx->errHandler->addSemanticError(
                line,
                "Parameter '" + ctx->currParamNames[i] + "' must have a default value because a previous parameter does");
            break;
        }
    }

    Symbol sym;
    sym.name = name;
    sym.dataType = returnType;
    sym.returnType = returnType;
    sym.isFunction = true;
    sym.paramTypes = ctx->currParam;
    sym.paramNames = ctx->currParamNames;
    sym.defaultValues = ctx->currParamDefaults;
    sym.declaredLine = line;
    sym.isInitialized = true;
    if (!ctx->symTable->insert(name, sym))
    {
        ctx->errHandler->addSemanticError(line,
                                          "Redeclaration of function '" + name + "'");
    }

    ctx->semAnalyzer->setCurrentFunction(name, returnType);
    ctx->quadGenerator->emit("FUNC_BEGIN", name, "-", "-");
    ctx->symTable->addScope();

    for (std::size_t i = 0; i < ctx->currParam.size(); i++)
    {
        Symbol paramSym;
        paramSym.name = ctx->currParamNames[i];
        paramSym.dataType = ctx->currParam[i];
        paramSym.isConst = (i < ctx->currParamConst.size()) ? ctx->currParamConst[i] : false;
        paramSym.isInitialized = true;
        paramSym.declaredLine = line;
        ctx->symTable->insert(ctx->currParamNames[i], paramSym);
    }
}

void endFunctionDefinition(ParserContext *ctx,
                           const char *functionName)
{
    ctx->quadGenerator->emit("FUNC_END", functionName, "-", "-");
    ctx->semAnalyzer->clearCurrentFunction();
}

char *beginIfCondition(ParserContext *ctx,
                       ExprAttr *conditionExpr, int line)
{
    std::string falseLabel = ctx->quadGenerator->newLabel();
    emitGuardedConditionalJump(ctx, conditionExpr, "JMP_FALSE", falseLabel, line);
    delete conditionExpr;
    return strdup(falseLabel.c_str());
}

void endIfWithoutElse(ParserContext *ctx,
                      const char *falseLabel)
{
    ctx->quadGenerator->emit("LABEL", falseLabel, "-", "-");
}

char *beginElseBranch(ParserContext *ctx,
                      const char *falseLabel)
{
    std::string endLabel = ctx->quadGenerator->newLabel();
    ctx->quadGenerator->emit("JMP", "-", "-", endLabel);
    ctx->quadGenerator->emit("LABEL", falseLabel, "-", "-");
    return strdup(endLabel.c_str());
}

void endIfWithElse(ParserContext *ctx,
                   const char *endLabel)
{
    ctx->quadGenerator->emit("LABEL", endLabel, "-", "-");
}

char *beginWhileLoop(ParserContext *ctx)
{
    std::string startLabel = ctx->quadGenerator->newLabel();
    std::string endLabel = ctx->quadGenerator->newLabel();
    ctx->quadGenerator->emit("LABEL", startLabel, "-", "-");
    ctx->continueLabels.push_back(startLabel);
    ctx->breakLabels.push_back(endLabel);
    ctx->semAnalyzer->enterLoop();
    return strdup(startLabel.c_str());
}

void emitLoopConditionFalseJump(ParserContext *ctx,
                                ExprAttr *conditionExpr, int line)
{
    emitGuardedConditionalJump(ctx, conditionExpr, "JMP_FALSE", ctx->breakLabels.back(), line);
    delete conditionExpr;
}

void endWhileLoop(ParserContext *ctx,
                  const char *startLabel)
{
    ctx->quadGenerator->emit("JMP", "-", "-", startLabel);
    ctx->quadGenerator->emit("LABEL", ctx->breakLabels.back(), "-", "-");
    ctx->breakLabels.pop_back();
    ctx->continueLabels.pop_back();
    ctx->semAnalyzer->exitLoop();
}

char *beginDoWhileLoop(ParserContext *ctx)
{
    std::string startLabel = ctx->quadGenerator->newLabel();
    std::string endLabel = ctx->quadGenerator->newLabel();
    std::string condLabel = ctx->quadGenerator->newLabel();
    ctx->quadGenerator->emit("LABEL", startLabel, "-", "-");
    ctx->continueLabels.push_back(condLabel);
    ctx->breakLabels.push_back(endLabel);
    ctx->semAnalyzer->enterLoop();
    return strdup((startLabel + "," + condLabel + "," + endLabel).c_str());
}

void emitDoWhileConditionLabel(ParserContext *ctx,
                               const char *packedLabels)
{
    DoWhileLabels labels = unpackDoWhileLabels(packedLabels);
    ctx->quadGenerator->emit("LABEL", labels.condLabel, "-", "-");
}

void endDoWhileLoop(ParserContext *ctx,
                    const char *packedLabels,
                    ExprAttr *conditionExpr, int line)
{
    DoWhileLabels labels = unpackDoWhileLabels(packedLabels);
    emitGuardedConditionalJump(ctx, conditionExpr, "JMP_TRUE", labels.startLabel, line);
    delete conditionExpr;
    ctx->quadGenerator->emit("LABEL", labels.endLabel, "-", "-");
    ctx->breakLabels.pop_back();
    ctx->continueLabels.pop_back();
    ctx->semAnalyzer->exitLoop();
}

char *beginForLoop(ParserContext *ctx)
{
    std::string condLabel = ctx->quadGenerator->newLabel();
    std::string bodyLabel = ctx->quadGenerator->newLabel();
    std::string updateLabel = ctx->quadGenerator->newLabel();
    std::string endLabel = ctx->quadGenerator->newLabel();
    ctx->quadGenerator->emit("LABEL", condLabel, "-", "-");
    ctx->continueLabels.push_back(updateLabel);
    ctx->breakLabels.push_back(endLabel);
    ctx->semAnalyzer->enterLoop();
    return strdup((condLabel + "," + bodyLabel + "," + updateLabel + "," + endLabel).c_str());
}

void emitForConditionAndUpdateLabel(ParserContext *ctx,
                                    const char *packedLabels,
                                    ExprAttr *conditionExpr, int line)
{
    ForLabels labels = unpackForLabels(packedLabels);
    if (conditionExpr->place != "")
    {
        emitGuardedConditionalJump(ctx, conditionExpr, "JMP_FALSE", labels.endLabel, line);
    }
    delete conditionExpr;
    ctx->quadGenerator->emit("JMP", "-", "-", labels.bodyLabel);
    ctx->quadGenerator->emit("LABEL", labels.updateLabel, "-", "-");
}

void emitForBackEdgeAndBodyLabel(ParserContext *ctx,
                                 const char *packedLabels)
{
    ForLabels labels = unpackForLabels(packedLabels);
    ctx->quadGenerator->emit("JMP", "-", "-", labels.condLabel);
    ctx->quadGenerator->emit("LABEL", labels.bodyLabel, "-", "-");
}

void endForLoop(ParserContext *ctx,
                const char *packedLabels)
{
    ForLabels labels = unpackForLabels(packedLabels);
    ctx->quadGenerator->emit("JMP", "-", "-", labels.updateLabel);
    ctx->quadGenerator->emit("LABEL", labels.endLabel, "-", "-");
    ctx->breakLabels.pop_back();
    ctx->continueLabels.pop_back();
    ctx->semAnalyzer->exitLoop();
    ctx->symTable->LeaveScope();
}

char *beginSwitchStatement(ParserContext *ctx,
                           ExprAttr *switchExpr,
                           int line)
{
    ctx->semAnalyzer->enterSwitchContext();
    std::string endLabel = ctx->quadGenerator->newLabel();
    std::string dispatchLabel = ctx->quadGenerator->newLabel();
    ctx->breakLabels.push_back(endLabel);
    bool validSwitchType = switchExpr != nullptr && (switchExpr->type == Type::INT || switchExpr->type == Type::BOOL || switchExpr->type == Type::CHAR);
    if (!validSwitchType)
    {
        std::string actualType = switchExpr ? typeToString(switchExpr->type) : "unknown";
        ctx->errHandler->addSemanticError(line, "Switch expression must be integral type (int, char or bool), got '" + actualType + "'");
    }
    ctx->switchExprStack.push_back(validSwitchType ? switchExpr->place : "");
    ctx->switchExprTypeStack.push_back(validSwitchType ? switchExpr->type : Type::UNKNOWN);
    ctx->switchDispatchCases.emplace_back();
    ctx->switchDispatchLabel.push_back(dispatchLabel);
    ctx->switchDefaultLabel.push_back("");
    ctx->quadGenerator->emit("JMP", "-", "-", dispatchLabel);
    delete switchExpr;
    return strdup(endLabel.c_str());
}

void endSwitchStatement(ParserContext *ctx,
                        const char *endLabel)
{
    const std::string end(endLabel);
    ctx->quadGenerator->emit("JMP", "-", "-", end);
    std::string dispatchLabel = ctx->switchDispatchLabel.back();
    ctx->quadGenerator->emit("LABEL", dispatchLabel, "-", "-");
    std::string switchExpr = ctx->switchExprStack.back();
    if (!switchExpr.empty())
    {
        for (const auto &entry : ctx->switchDispatchCases.back())
        {
            std::string temp = ctx->quadGenerator->newTemp();
            ctx->quadGenerator->emit("EQ", switchExpr, entry.literalPlace, temp);
            ctx->quadGenerator->emit("JMP_TRUE", temp, "-", entry.caseLabel);
        }
    }

    if (!ctx->switchDefaultLabel.back().empty())
    {
        ctx->quadGenerator->emit("JMP", "-", "-", ctx->switchDefaultLabel.back());
    }
    else
    {
        ctx->quadGenerator->emit("JMP", "-", "-", end);
    }

    ctx->quadGenerator->emit("LABEL", end, "-", "-");
    ctx->breakLabels.pop_back();
    ctx->switchExprStack.pop_back();
    ctx->switchExprTypeStack.pop_back();
    ctx->switchDispatchCases.pop_back();
    ctx->switchDispatchLabel.pop_back();
    ctx->switchDefaultLabel.pop_back();
    ctx->semAnalyzer->leaveSwitchContext();
}

void beginCaseClause(ParserContext *ctx,
                     ExprAttr *literal,
                     int line)
{
    std::string caseLabel = ctx->quadGenerator->newLabel();
    bool isIntegralLiteral = literal != nullptr &&
                             (literal->type == Type::INT || literal->type == Type::CHAR || literal->type == Type::BOOL);
    bool skipCase = false;

    if (!isIntegralLiteral)
    {
        std::string actualType = literal ? typeToString(literal->type) : "unknown";
        ctx->errHandler->addSemanticError(
            line,
            "Case label must be an integral type (int, char, or bool), got '" + actualType + "'");
        skipCase = true;
    }

    if (!skipCase && !ctx->switchExprTypeStack.empty())
    {
        Type switchType = ctx->switchExprTypeStack.back();
        if (switchType != Type::UNKNOWN)
        {
            skipCase = !ctx->semAnalyzer->coerce(*literal, switchType, line);
        }
    }

    if (!skipCase)
    {
        skipCase = !ctx->semAnalyzer->validateCaseLabel(*literal, line);
    }

    ctx->switchSkipCaseStack.push_back(skipCase);
    if (skipCase)
    {
        ctx->quadGenerator->beginSuppression();
    }
    else
    {
        ctx->switchDispatchCases.back().push_back(SwitchCaseDispatch{literal->place, caseLabel});
        ctx->quadGenerator->emit("LABEL", caseLabel, "-", "-");
    }
    delete literal;
}

void beginDefaultClause(ParserContext *ctx,
                        int line)
{
    bool skipDefault = !ctx->semAnalyzer->validateDefaultLabel(line);
    ctx->switchSkipCaseStack.push_back(skipDefault);
    if (skipDefault)
    {
        ctx->quadGenerator->beginSuppression();
    }
    else
    {
        std::string defLabel = ctx->quadGenerator->newLabel();
        ctx->switchDefaultLabel.back() = defLabel;
        ctx->quadGenerator->emit("LABEL", defLabel, "-", "-");
    }
}

void endCaseOrDefaultClause(ParserContext *ctx)
{
    if (!ctx->switchSkipCaseStack.empty())
    {
        bool skip = ctx->switchSkipCaseStack.back();
        ctx->switchSkipCaseStack.pop_back();
        if (skip)
        {
            ctx->quadGenerator->endSuppression();
        }
    }
}
