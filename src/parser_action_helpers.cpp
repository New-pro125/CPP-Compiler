#include "parser_action_helpers.h"

#include <cstring>
#include <string>

#include "parser_context.h"

namespace
{
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

    SwitchContext *currentSwitchContext(ParserContext *ctx)
    {
        if (ctx->switchContexts.empty())
        {
            return nullptr;
        }
        return &ctx->switchContexts.back();
    }
}

bool validateAndCoerceConditionExpr(ParserContext *ctx, ExprAttr *conditionExpr, int line)
{
    if (!conditionExpr || conditionExpr->type == Type::UNKNOWN || conditionExpr->type == Type::STRING || conditionExpr->type == Type::VOID)
    {
        std::string actualType = (!conditionExpr) ? "unknown" : typeToString(conditionExpr->type);
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
void emitGuardedConditionalJump(ParserContext *ctx, ExprAttr *conditionExpr, const std::string &jumpOp, const std::string &targetLabel, int line)
{
    ctx->quadGenerator->emit(validateAndCoerceConditionExpr(ctx, conditionExpr, line) ? jumpOp : "JMP", conditionExpr ? conditionExpr->place : "-", "-", targetLabel);
}

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
        ctx->semAnalyzer->markExpressionAsRead(*lhs);
        ctx->semAnalyzer->markExpressionAsRead(*rhs);
        temp = ctx->quadGenerator->newTemp();
        ctx->quadGenerator->emit(irOp, lhs->place, rhs->place, temp);
    }

    delete lhs;
    delete rhs;

    auto *result = new ExprAttr(t, temp);
    return result;
}

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
            ctx->semAnalyzer->markExpressionAsRead(rhs);
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
        Type origLhsType = lhs.type;
        Type resultType = ctx->semAnalyzer->checkBinaryOper(lhs, rhs, semanticOp, line);
        if (resultType != Type::UNKNOWN)
        {
            ctx->semAnalyzer->markExpressionAsRead(lhs);
            ctx->semAnalyzer->markExpressionAsRead(rhs);
            std::string temp = ctx->quadGenerator->newTemp();
            ctx->quadGenerator->emit(irOp, lhs.place, rhs.place, temp);

            ExprAttr tempExpr(resultType, temp);
            ctx->semAnalyzer->coerce(tempExpr, origLhsType, line);

            ctx->quadGenerator->emit("ASSIGN", tempExpr.place, "-", ctx->symTable->getIRName(name));
            auto *result = new ExprAttr(origLhsType, ctx->symTable->getIRName(name));
            return result;
        }
    }
    return unknownExprFromName(name);
}

ExprAttr *makeIncDecExpr(ParserContext *ctx,
                         const char *identifier,
                         const std::string &op,
                         int line,
                         bool isPostfix)
{
    const std::string name(identifier);
    bool isAssignable = ctx->semAnalyzer->checkAssignable(name, line);
    if (isAssignable)
    {

        ExprAttr id = ctx->semAnalyzer->resolveIdentifier(name, line);
        Type resultType = ctx->semAnalyzer->checkUnaryOper(id, op, line);
        if (resultType != Type::UNKNOWN)
        {
            std::string finalPlace = id.place;
            if (isPostfix)
            {
                std::string temp = ctx->quadGenerator->newTemp();
                ctx->quadGenerator->emit("ASSIGN", id.place, "-", temp);
                finalPlace = temp;
            }
            ctx->quadGenerator->emit(op, id.place, "-", id.place);
            ctx->semAnalyzer->markExpressionAsRead(id);

            auto *result = new ExprAttr(id.type, finalPlace, id.isLvalue, id.isConst, id.isUsed);
            return result;
        }
    }
    return unknownExprFromName(name);
}

ExprAttr *makeUnaryExpr(ParserContext *ctx,
                        ExprAttr *operand,
                        const std::string &semanticOp,
                        const std::string &irOp,
                        int line)
{
    Type t = ctx->semAnalyzer->checkUnaryOper(*operand, semanticOp, line);
    auto *result = new ExprAttr(t, operand->place);
    if (t != Type::UNKNOWN)
    {

        if (t != operand->type)
        {
            ctx->semAnalyzer->coerce(*operand, t, line);
        }
        ctx->semAnalyzer->markExpressionAsRead(*operand);
        std::string temp = ctx->quadGenerator->newTemp();
        ctx->quadGenerator->emit(irOp, operand->place, "-", temp);
        result->place = temp;
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
    if (retType == Type::UNKNOWN)
    {
        return unknownExprFromName(fn);
    }
    std::size_t emittedArgCount = 0;
    for (auto &arg : currentArgs)
    {
        ctx->quadGenerator->emit("PARAM", arg.place, "-", "-");
        emittedArgCount++;
    }

    Symbol *callee = ctx->symTable->lookup(fn);
    if (callee != nullptr && callee->isFunction)
    {
        for (std::size_t i = currentArgs.size(); i < callee->defaultValues.size(); i++)
        {
            if (callee->defaultValues[i].empty())
            {
                break;
            }
            ctx->quadGenerator->emit("PARAM", callee->defaultValues[i], "-", "-");
            emittedArgCount++;
        }
    }
    std::string quadResult = retType == Type::VOID ? "-" : ctx->quadGenerator->newTemp();
    ctx->quadGenerator->emit("CALL", fn, std::to_string(emittedArgCount), quadResult);
    auto *result = new ExprAttr(retType, quadResult);
    return result;
}

ExprAttr *makeIdentifierExpr(ParserContext *ctx,
                             const char *identifier,
                             int line)
{
    auto *result = new ExprAttr(ctx->semAnalyzer->resolveIdentifier(identifier, line));
    ctx->semAnalyzer->markExpressionAsRead(*result);
    return result;
}

void leaveScopeWithUnusedWarnings(ParserContext *ctx)
{
    if (ctx->currFunction.inFn && ctx->currFunction.isInvalid)
    {
        ctx->symTable->removeCurrentScopeSymbols();
        ctx->symTable->LeaveScope();
        return;
    }

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
        ctx->errHandler->addSemanticError(line,
                                          "Const variable '" + name +
                                              "' must be initialized at declaration");
        return;
    }
    if (!declTypeOk)
    {
        return;
    }

    Symbol sym = Symbol(name, name, ctx->currDeclType, ctx->currDeclConst);
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
    bool declTypeOk = validateDeclaratorType(ctx, name, line);
    if (!declTypeOk)
        return;
    ExprAttr rhs = *initExpr;
    delete initExpr;
    bool initOk = ctx->semAnalyzer->validateAssignment(rhs, ctx->currDeclType, line);
    if (!initOk)
        return;
    initOk = ctx->semAnalyzer->coerce(rhs, ctx->currDeclType, line);
    if (initOk)
    {
        ctx->semAnalyzer->markExpressionAsRead(rhs);
    }
    Symbol sym = Symbol(name, name, ctx->currDeclType, ctx->currDeclConst, initOk);
    sym.declaredLine = line;
    if (!ctx->symTable->insert(name, sym))
    {
        ctx->errHandler->addSemanticError(line,
                                          "Redeclaration of variable '" + name + "'");
        return;
    }
    if (initOk)
        ctx->quadGenerator->emit("ASSIGN", rhs.place, "-", ctx->symTable->getIRName(name));
}

void resetFunctionParamContext(ParserContext *ctx)
{
    ctx->currFunction.params = FunctionParamContext();
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
        ctx->currFunction.params.hasError = true;
        return;
    }

    ctx->currFunction.params.params.push_back(FunctionParamSpec(paramName, defaultValue, paramType, isConst));
}

void markCurrentFunctionInvalid(ParserContext *ctx)
{
    if (!ctx->currFunction.inFn || (ctx->currFunction.inFn && ctx->currFunction.name == "main"))
        return;
    if (!ctx->currFunction.isInvalid)
        ctx->currFunction.isInvalid = true;
    if (!ctx->currFunction.isSuppressed)
    {
        ctx->quadGenerator->beginSuppression();
        ctx->currFunction.isSuppressed = true;
    }
}

bool validateStatementPlacement(ParserContext *ctx,
                                int line)
{
    if (ctx->currFunction.inFn && ctx->currFunction.isInvalid)
    {
        return false;
    }

    if (!ctx->currFunction.inFn)
    {
        ctx->errHandler->addSemanticError(
            line,
            "Only declarations and function definitions are allowed at global scope");
        return true;
    }

    return false;
}

void beginFunctionDefinition(ParserContext *ctx,
                             const char *functionName,
                             Type returnType,
                             int line)
{
    const std::string name(functionName);
    FunctionParamContext paramsCtx = ctx->currFunction.params;
    ctx->currFunction = CurrentFunctionContext(
        name,
        paramsCtx,
        true,
        false,
        false,
        false,
        ctx->quadGenerator->nextQuad());
    const auto &params = ctx->currFunction.params.params;

    bool sawDefault = false;
    for (std::size_t i = 0; i < params.size(); i++)
    {
        if (!params[i].defaultValue.empty())
        {
            sawDefault = true;
        }
        else if (sawDefault)
        {
            ctx->errHandler->addSemanticError(
                line,
                "Missing default argument on Parameter '" + params[i].name + "'");
            ctx->currFunction.params.hasError = true;
            break;
        }
    }

    if (ctx->currFunction.params.hasError)
    {
        markCurrentFunctionInvalid(ctx);
    }

    if (!ctx->currFunction.isInvalid)
    {
        Symbol sym = Symbol(name, name, returnType, false, true, false, true, line, 0, returnType);
        for (const auto &param : params)
        {
            sym.paramTypes.push_back(param.dataType);
            sym.paramNames.push_back(param.name);
            sym.defaultValues.push_back(param.defaultValue);
        }
        if (!ctx->symTable->insert(name, sym))
        {
            ctx->errHandler->addSemanticError(line,
                                              "Redeclaration of function '" + name + "'");
        }
        else
        {
            ctx->currFunction.isInserted = true;
        }
    }

    ctx->semAnalyzer->setCurrentFunction(name, returnType);
    if (!ctx->currFunction.isInvalid)
        ctx->quadGenerator->emit("FUNC_BEGIN", name, "-", "-");
    ctx->symTable->addScope();

    for (const auto &param : params)
    {

        Symbol paramSym = Symbol(param.name, param.name, param.dataType, param.isConst, true);
        paramSym.declaredLine = line;
        ctx->symTable->insert(param.name, paramSym);
    }
}

void endFunctionDefinition(ParserContext *ctx,
                           const char *functionName)
{
    if (!ctx->currFunction.isInvalid)
    {
        ctx->quadGenerator->emit("FUNC_END", functionName, "-", "-");
    }
    else
    {
        if (ctx->currFunction.isInserted)
            ctx->symTable->removeCurrentScopeSymbol(functionName);
        ctx->quadGenerator->rollbackTo(ctx->currFunction.quadStart);
    }
    if (ctx->currFunction.isSuppressed)
        ctx->quadGenerator->endSuppression();

    ctx->semAnalyzer->clearCurrentFunction();
    ctx->currFunction = CurrentFunctionContext();
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
    ctx->switchContexts.emplace_back(validSwitchType ? switchExpr->place : "",
                                     dispatchLabel,
                                     "",
                                     validSwitchType ? switchExpr->type : Type::UNKNOWN);
    ctx->switchContexts.back().isInvalid = !validSwitchType;
    if (!validSwitchType)
    {
        ctx->quadGenerator->beginSuppression();
    }
    ctx->quadGenerator->emit("JMP", "-", "-", dispatchLabel);
    delete switchExpr;
    return strdup(endLabel.c_str());
}

void endSwitchStatement(ParserContext *ctx,
                        const char *endLabel)
{
    const std::string end(endLabel);
    SwitchContext *switchCtx = currentSwitchContext(ctx);
    const bool suppressSwitchIR = switchCtx && switchCtx->isInvalid;

    if (!suppressSwitchIR)
    {
        ctx->quadGenerator->emit("JMP", "-", "-", end);

        std::string switchExpr;
        if (switchCtx)
        {
            ctx->quadGenerator->emit("LABEL", switchCtx->dispatchLabel, "-", "-");
            switchExpr = switchCtx->exprPlace;
        }

        if (switchCtx && !switchExpr.empty())
        {
            for (const auto &entry : switchCtx->dispatchCases)
            {
                std::string temp = ctx->quadGenerator->newTemp();
                ctx->quadGenerator->emit("EQ", switchExpr, entry.literalPlace, temp);
                ctx->quadGenerator->emit("JMP_TRUE", temp, "-", entry.caseLabel);
            }
        }

        if (switchCtx && !switchCtx->defaultLabel.empty())
        {
            ctx->quadGenerator->emit("JMP", "-", "-", switchCtx->defaultLabel);
        }
        else
        {
            ctx->quadGenerator->emit("JMP", "-", "-", end);
        }

        ctx->quadGenerator->emit("LABEL", end, "-", "-");
    }
    else
    {
        ctx->quadGenerator->endSuppression();
    }

    if (!ctx->breakLabels.empty())
    {
        ctx->breakLabels.pop_back();
    }
    if (switchCtx)
    {
        ctx->switchContexts.pop_back();
    }
    ctx->semAnalyzer->leaveSwitchContext();
}

void beginCaseClause(ParserContext *ctx,
                     ExprAttr *literal,
                     int line)
{
    SwitchContext *switchCtx = currentSwitchContext(ctx);
    if (!switchCtx)
    {
        delete literal;
        return;
    }

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

    if (!skipCase)
    {
        Type switchType = switchCtx->exprType;
        if (switchType != Type::UNKNOWN)
        {
            skipCase = !ctx->semAnalyzer->coerce(*literal, switchType, line);
        }
    }

    if (!skipCase)
    {
        skipCase = !ctx->semAnalyzer->validateCaseLabel(*literal, line);
    }

    switchCtx->skipCase.push_back(skipCase);
    if (skipCase)
    {
        ctx->quadGenerator->beginSuppression();
    }
    else
    {
        switchCtx->dispatchCases.emplace_back(literal->place, caseLabel);
        ctx->quadGenerator->emit("LABEL", caseLabel, "-", "-");
    }
    delete literal;
}

void beginDefaultClause(ParserContext *ctx,
                        int line)
{
    SwitchContext *switchCtx = currentSwitchContext(ctx);
    if (!switchCtx)
    {
        return;
    }

    bool skipDefault = !ctx->semAnalyzer->validateDefaultLabel(line);
    switchCtx->skipCase.push_back(skipDefault);
    if (skipDefault)
    {
        ctx->quadGenerator->beginSuppression();
    }
    else
    {
        std::string defLabel = ctx->quadGenerator->newLabel();
        switchCtx->defaultLabel = defLabel;
        ctx->quadGenerator->emit("LABEL", defLabel, "-", "-");
    }
}

void endCaseOrDefaultClause(ParserContext *ctx)
{
    SwitchContext *switchCtx = currentSwitchContext(ctx);
    if (switchCtx && !switchCtx->skipCase.empty())
    {
        bool skip = switchCtx->skipCase.back();
        switchCtx->skipCase.pop_back();
        if (skip)
        {
            ctx->quadGenerator->endSuppression();
        }
    }
}
