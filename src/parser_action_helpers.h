#ifndef PARSER_ACTION_HELPERS_H
#define PARSER_ACTION_HELPERS_H

#include <string>
#include "types.h"

struct ParserContext;

ExprAttr *makeBinaryExpr(ParserContext *ctx,
                         ExprAttr *lhs,
                         ExprAttr *rhs,
                         const std::string &semanticOp,
                         const std::string &irOp,
                         int line);

ExprAttr *makeAssignExpr(ParserContext *ctx,
                         const char *identifier,
                         ExprAttr *rhsExpr,
                         int line);

ExprAttr *makeCompoundAssignExpr(ParserContext *ctx,
                                 const char *identifier,
                                 ExprAttr *rhsExpr,
                                 const std::string &semanticOp,
                                 const std::string &irOp,
                                 int line);

ExprAttr *makeIncDecExpr(ParserContext *ctx,
                         const char *identifier,
                         const std::string &op,
                         int line,
                         bool isPostfix = true);

ExprAttr *makeUnaryExpr(ParserContext *ctx,
                        ExprAttr *operand,
                        const std::string &semanticOp,
                        const std::string &irOp,
                        int line);

ExprAttr *makeFunctionCallExpr(ParserContext *ctx,
                               const char *functionName,
                               int line);

ExprAttr *makeIdentifierExpr(ParserContext *ctx,
                             const char *identifier,
                             int line);

void leaveScopeWithUnusedWarnings(ParserContext *ctx);

void handleSimpleDeclarator(ParserContext *ctx,
                            const char *identifier,
                            int line);

void handleInitializedDeclarator(ParserContext *ctx,
                                 const char *identifier,
                                 ExprAttr *initExpr,
                                 int line);

void resetFunctionParamContext(ParserContext *ctx);

void addFunctionParam(ParserContext *ctx,
                      Type paramType,
                      const char *paramName,
                      const std::string &defaultValue,
                      bool isConst = false,
                      int line = -1);

void beginFunctionDefinition(ParserContext *ctx,
                             const char *functionName,
                             Type returnType,
                             int line);

void endFunctionDefinition(ParserContext *ctx,
                           const char *functionName);

void markCurrentFunctionInvalid(ParserContext *ctx);

void validateStatementPlacement(ParserContext *ctx,
                                int line);

char *beginIfCondition(ParserContext *ctx,
                       ExprAttr *conditionExpr, int line);

void endIfWithoutElse(ParserContext *ctx,
                      const char *falseLabel);

char *beginElseBranch(ParserContext *ctx,
                      const char *falseLabel);

void endIfWithElse(ParserContext *ctx,
                   const char *endLabel);

char *beginWhileLoop(ParserContext *ctx);

void emitLoopConditionFalseJump(ParserContext *ctx,
                                ExprAttr *conditionExpr, int line);

void endWhileLoop(ParserContext *ctx,
                  const char *startLabel);

char *beginDoWhileLoop(ParserContext *ctx);

void emitDoWhileConditionLabel(ParserContext *ctx,
                               const char *packedLabels);

void endDoWhileLoop(ParserContext *ctx,
                    const char *packedLabels,
                    ExprAttr *conditionExpr, int line);

char *beginForLoop(ParserContext *ctx);

void emitForConditionAndUpdateLabel(ParserContext *ctx,
                                    const char *packedLabels,
                                    ExprAttr *conditionExpr, int line);

void emitForBackEdgeAndBodyLabel(ParserContext *ctx,
                                 const char *packedLabels);

void endForLoop(ParserContext *ctx,
                const char *packedLabels);

char *beginSwitchStatement(ParserContext *ctx,
                           ExprAttr *switchExpr,
                           int line);

void endSwitchStatement(ParserContext *ctx,
                        const char *endLabel);

void beginCaseClause(ParserContext *ctx,
                     ExprAttr *literal,
                     int line);

void beginDefaultClause(ParserContext *ctx,
                        int line);

void endCaseOrDefaultClause(ParserContext *ctx);

#endif
