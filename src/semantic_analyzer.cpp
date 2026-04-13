#include "semantic_analyzer.h"
#include <unordered_set>

SemanticAnalyzer::SemanticAnalyzer(SymbolTable *st, QuadrupleGenerator *qg, ErrorHandler *eh)
    : symTable(st),
      quadGen(qg),
      errorHandler(eh)
{
}

Type SemanticAnalyzer::promoteType(Type a, Type b) const
{
    int ra = typeRank(a);
    int rb = typeRank(b);
    if (ra < 0 || rb < 0)
        return Type::UNKNOWN;
    return (ra >= rb) ? a : b;
}

bool SemanticAnalyzer::isIntegerType(Type t) const
{
    return t == Type::INT ||
           t == Type::CHAR ||
           t == Type::BOOL;
}

int SemanticAnalyzer::typeRank(Type t) const
{
    switch (t)
    {
    case Type::BOOL:
        return 0;
    case Type::CHAR:
        return 1;
    case Type::INT:
        return 2;
    case Type::FLOAT:
        return 3;
    default:
        return -1;
    }
}

bool SemanticAnalyzer::coerce(ExprAttr &expr, Type targetType, int line)
{
    if (expr.type == targetType)
        return true;
    if (expr.type == Type::STRING || targetType == Type::STRING)
        return false;

    if (expr.type == Type::VOID || targetType == Type::VOID)
        return false;

    int fromRank = typeRank(expr.type);

    int toRank = typeRank(targetType);
    if (fromRank < 0 || toRank < 0)
        return false;
    // warn on narrowing
    if (fromRank > toRank)
    {
        errorHandler->addWarning(line, "Implicit narrowing conversion from '" +
                                           typeToString(expr.type) +
                                           "' to '" + typeToString(targetType) + "'");
    }
    std::string convOp;
    if (targetType == Type::INT && expr.type == Type::BOOL)
        convOp = "BTOI";
    else if (targetType == Type::INT && expr.type == Type::CHAR)
        convOp = "CTOI";
    else if (targetType == Type::FLOAT && isIntegerType(expr.type))
        convOp = "ITOF";

    // narrowing
    else if (targetType == Type::INT && expr.type == Type::FLOAT)
        convOp = "FTOI";

    else if (targetType == Type::CHAR && (expr.type == Type::INT || expr.type == Type::BOOL))
        convOp = "ITOC";

    else if (targetType == Type::CHAR && expr.type == Type::FLOAT)
    {
        // FLOAT ==> INT
        std::string temp1 = quadGen->newTemp();
        quadGen->emit("FTOI", expr.place, "-", temp1);
        expr.place = temp1;
        // INT ==> CHAR
        convOp = "ITOC";
    }

    else if (targetType == Type::BOOL && expr.type == Type::FLOAT)
    {
        // FLOAT==> INT ==>BOOL
        std::string temp1 = quadGen->newTemp();
        quadGen->emit("FTOI", expr.place, "-", temp1);
        expr.place = temp1;
        convOp = "ITOB";
    }

    else if (targetType == Type::BOOL)
        convOp = "ITOB";
    else
    {
        this->errorHandler->addSemanticError(line, "Cannot convert from " + typeToString(expr.type) + " to " + typeToString(targetType));
        return false;
    }
    std::string temp = quadGen->newTemp();
    quadGen->emit(convOp, expr.place, "-", temp);
    expr.place = temp;
    expr.type = targetType;
    return true;
}

ExprAttr SemanticAnalyzer::resolveIdentifier(const std::string &symbol_name, int line)
{
    ExprAttr result;
    Symbol *sym = symTable->lookup(symbol_name);
    if (sym == nullptr)
    {
        errorHandler->addSemanticError(line, "Undeclared identifier '" + symbol_name + "'");
        result.type = Type::UNKNOWN;
        result.place = symbol_name;
        result.isLvalue = false;
        return result;
    }
    sym->isUsed = true;
    if (!sym->isFunction && !sym->isInitialized)
    {
        errorHandler->addSemanticError(line, "Variable '" + symbol_name + "' used before being initialized");
        result.type = Type::UNKNOWN;
    }
    else
    {
        result.type = sym->dataType;
    }
    result.place = sym->irName;

    result.isLvalue = !sym->isConst && !sym->isFunction;
    result.isConst = sym->isConst;
    return result;
}

Type SemanticAnalyzer::validateFunctionCall(const std::string &name, std::vector<ExprAttr> &args, int line)
{
    Symbol *sym = symTable->lookup(name);
    if (sym == nullptr)
    {
        errorHandler->addSemanticError(line, "Undeclared function '" + name + "'");
        return Type::UNKNOWN;
    }
    if (!sym->isFunction)
    {
        errorHandler->addSemanticError(line, "'" + name +
                                                 "' is not a function");
        return Type::UNKNOWN;
    }
    sym->isUsed = true;
    size_t requiredParams = sym->paramTypes.size();
    size_t providedArgs = args.size();
    // counte default values
    size_t defaultCount = 0;
    for (size_t i = 0; i < sym->defaultValues.size(); i++)
    {
        if (!sym->defaultValues[i].empty())
            defaultCount++;
    }
    size_t minArgs = requiredParams - defaultCount;
    if (providedArgs < minArgs)
    {
        errorHandler->addSemanticError(line, "Too few arguments to function '" + name + "': expected at least " +
                                                 std::to_string(minArgs) + ", got " + std::to_string(providedArgs));
        return sym->returnType;
    }
    if (providedArgs > requiredParams)
    {
        errorHandler->addSemanticError(line, "Too many arguments to function '" + name + "': expected at most " +
                                                 std::to_string(requiredParams) + ", got " + std::to_string(providedArgs));
        return sym->returnType;
    }
    // check type for each arg
    for (size_t i = 0; i < providedArgs; i++)
    {
        if (args[i].type != sym->paramTypes[i])
        {
            if (args[i].type == Type::STRING || sym->paramTypes[i] == Type::STRING)
            {
                errorHandler->addSemanticError(line, "Incompatible type for argument " + std::to_string(i + 1) +
                                                         " in call to '" + name + "': expected '" + typeToString(sym->paramTypes[i]) + "', got '" +
                                                         typeToString(args[i].type) + "'");
            }
            // coercion
            else if (isNumericLike(args[i].type) && isNumericLike(sym->paramTypes[i]))
            {
                if (!coerce(args[i], sym->paramTypes[i], line))
                {
                    errorHandler->addSemanticError(line, "Cannot convert argument " + std::to_string(i + 1) +
                                                             " from '" + typeToString(args[i].type) + "' to '" +
                                                             typeToString(sym->paramTypes[i]) + "' in call to '" + name + "'");
                }
            }
            // incompatible
            else
            {
                errorHandler->addSemanticError(line,
                                               "Incompatible type for argument " + std::to_string(i + 1) +
                                                   " in call to '" + name + "': expected '" + typeToString(sym->paramTypes[i]) + "', got '" +
                                                   typeToString(args[i].type) + "'");
            }
        }
    }
    return sym->returnType;
}

bool SemanticAnalyzer::checkAssignable(const std::string &name, int line)
{
    Symbol *sym = symTable->lookup(name);
    if (sym == nullptr)
    {
        errorHandler->addSemanticError(line, "Undeclared variable '" + name + "'");
        return false;
    }
    if (sym->isFunction)
    {
        errorHandler->addSemanticError(line,
                                       "Cannot assign to function '" + name + "'");
        return false;
    }

    if (sym->isConst)
    {
        errorHandler->addSemanticError(line, "Cannot assign to const variable '" + name + "'");
        return false;
    }
    return true;
}
bool SemanticAnalyzer::checkConstInitialized(const std::string &name, bool hasInitializer, int line)
{
    if (!hasInitializer)
    {
        errorHandler->addSemanticError(line,
                                       "Const variable '" + name +
                                           "' must be initialized at declaration");
        return false;
    }
    return true;
}

bool SemanticAnalyzer::validateBreak(int line)
{
    if (loopDepth == 0 && switchDepth == 0)
    {
        errorHandler->addSemanticError(line, "'break' statement not within a loop or switch");
        return false;
    }
    return true;
}

bool SemanticAnalyzer::validateContinue(int line)
{

    if (loopDepth == 0)
    {
        errorHandler->addSemanticError(line, "'continue' statement not within a loop");
        return false;
    }
    return true;
}

void SemanticAnalyzer::enterLoop()
{
    loopDepth++;
}
void SemanticAnalyzer::exitLoop()
{
    loopDepth--;
}
void SemanticAnalyzer::enterSwitch()
{
    switchDepth++;
}
void SemanticAnalyzer::exitSwitch()
{
    switchDepth--;
}

void SemanticAnalyzer::setCurrentFunction(const std::string &name, Type returnType)
{
    insideFunction = true;
    currentFunctionName = name;
    currentFunctionReturnType = returnType;
}

void SemanticAnalyzer::clearCurrentFunction()
{
    insideFunction = false;
    currentFunctionName = "";
    currentFunctionReturnType = Type::VOID;
}

Type SemanticAnalyzer::getCurrentFunctionReturnType() const
{
    return currentFunctionReturnType;
}

bool SemanticAnalyzer::validateReturn(Type expected, ExprAttr *value, int line)
{
    if (!insideFunction)
    {
        errorHandler->addSemanticError(line, "'return' statement not inside a function");
        return false;
    }

    if (expected == Type::VOID && value == nullptr)
        return true;
    if (expected == Type::VOID && value != nullptr)
    {
        errorHandler->addSemanticError(line, "Void function should not return a value");
        return false;
    }
    if (expected != Type::VOID && value == nullptr)
    {
        errorHandler->addSemanticError(line, "Non-void function must return a value of type '" +
                                                 typeToString(expected) + "'");
        return false;
    }
    if (value->type == expected)
        return true;

    // strings=>exact match only
    if (expected == Type::STRING || value->type == Type::STRING)
    {
        errorHandler->addSemanticError(line, "Cannot convert return type from '" + typeToString(value->type) +
                                                 "' to '" + typeToString(expected) + "'");
        return false;
    }

    // numeric=> allow coercion
    if (isNumericLike(value->type) && isNumericLike(expected))
    {
        if (coerce(*value, expected, line))
            return true;
    }

    errorHandler->addSemanticError(line,
                                   "Cannot convert return type from '" + typeToString(value->type) + "' to '" +
                                       typeToString(expected) + "'");
    return false;
}

Type SemanticAnalyzer::checkBinaryOper(const ExprAttr &left, const ExprAttr &right, const std::string &op, int line)
{
    // Make local mutable copies for coercion
    ExprAttr l = left;
    ExprAttr r = right;
    std::unordered_set<std::string> int_ops = {"BITWISEAND", "BITWISEOR", "BITWISEXOR", "RSHIFT", "LSHIFT", "MOD", "LSHIFTASSIGN", "RSHIFTASSIGN", "XORASSIGN", "ANDASSIGN", "ORASSIGN", "MODASSIGN", "BITWISENOT"};
    std::unordered_set<std::string> mathematical_ops = {"PLUSASSIGN", "MINUSASSIGN", "STARASSIGN", "DIVASSIGN", "PLUS", "MINUS", "STAR", "DIV"};
    // TODO: Change the operators into the names used inside the parser
    // bitwise,mod => require integer types
    if (int_ops.count(op)) // if operator exists then get into here
    {
        if (l.type == Type::STRING || r.type == Type::STRING)
        {
            errorHandler->addSemanticError(line, "Operator '" + op + "' cannot be applied to string type");
            return Type::UNKNOWN;
        }
        if (!isIntegerType(l.type))
        {
            errorHandler->addSemanticError(line,
                                           "Left operand of '" + op + "' must be integer type, got '" +
                                               typeToString(l.type) + "'");
            return Type::UNKNOWN;
        }
        if (!isIntegerType(r.type))
        {
            errorHandler->addSemanticError(line, "Right operand of '" + op + "' must be integer type, got '" +
                                                     typeToString(r.type) + "'");
            return Type::UNKNOWN;
        }
        if (l.type != Type::INT)
            coerce(l, Type::INT, line);
        if (r.type != Type::INT)
            coerce(r, Type::INT, line);
        return Type::INT;
    }

    // logical
    if (op == "AND" || op == "OR")
    {
        if (l.type == Type::STRING || r.type == Type::STRING)
        {
            errorHandler->addSemanticError(line, "Operator '" + op + "' cannot be applied to string type");
            return Type::UNKNOWN;
        }
        if (!isNumericLike(l.type))
        {
            errorHandler->addSemanticError(line, "Left operand of '" + op + "' is not a valid type, got '" +
                                                     typeToString(l.type) + "'");
            return Type::UNKNOWN;
        }
        if (!isNumericLike(r.type))
        {
            errorHandler->addSemanticError(line,
                                           "Right operand of '" + op + "' is not a valid type, got '" + typeToString(r.type) + "'");
            return Type::UNKNOWN;
        }
        return Type::BOOL;
    }

    // relational
    if (op == "EQ" || op == "NEQ" ||
        op == "GT" || op == "LT" ||
        op == "GEQ" || op == "LEQ")
    {
        if (l.type == Type::STRING && r.type == Type::STRING)
        {
            return Type::BOOL;
        }

        if (l.type == Type::STRING || r.type == Type::STRING)
        {
            errorHandler->addSemanticError(line, "Cannot compare '" + typeToString(l.type) +
                                                     "' with '" + typeToString(r.type) + "'");
            return Type::UNKNOWN;
        }
        // both numeric
        if (!isNumericLike(l.type) || !isNumericLike(r.type))
        {
            errorHandler->addSemanticError(line, "Cannot compare '" + typeToString(l.type) +
                                                     "' with '" + typeToString(r.type) + "'");
            return Type::UNKNOWN;
        }
        Type promoted = promoteType(l.type, r.type);
        if (l.type != promoted)
            coerce(l, promoted, line);
        if (r.type != promoted)
            coerce(r, promoted, line);
        return Type::BOOL;
    }

    if (mathematical_ops.count(op))
    {
        // string concatenation
        if (l.type == Type::STRING || r.type == Type::STRING)
        {
            if ((op == "PLUS" || op == "PLUSASSIGN") && (l.type == Type::STRING && (r.type == Type::STRING || r.type == Type::CHAR)))
            {
                return Type::STRING;
            }
            errorHandler->addSemanticError(line, "Operator '" + op + "' cannot be applied between '" +
                                                     typeToString(l.type) + "' and '" + typeToString(r.type) + "'");
            return Type::UNKNOWN;
        }
        if (!isNumericLike(l.type))
        {
            errorHandler->addSemanticError(line,
                                           "Left operand of '" + op + "' has invalid type '" + typeToString(l.type) + "'");
            return Type::UNKNOWN;
        }
        if (!isNumericLike(r.type))
        {
            errorHandler->addSemanticError(line,
                                           "Right operand of '" + op + "' has invalid type '" + typeToString(r.type) + "'");
            return Type::UNKNOWN;
        }
        Type promoted = promoteType(l.type, r.type);
        if (l.type != promoted)
            coerce(l, promoted, line);
        if (r.type != promoted)
            coerce(r, promoted, line);
        return promoted;
    }
    errorHandler->addSemanticError(line, "Unknown binary operator '" + op + "'");
    return Type::UNKNOWN;
}

bool SemanticAnalyzer::validateAssignment(ExprAttr rhs, Type lhsType, int line)
{
    if (rhs.type == lhsType)
        return true;
    if (lhsType == Type::STRING || rhs.type == Type::STRING)
    {
        errorHandler->addSemanticError(line,
                                       "Cannot assign '" + typeToString(rhs.type) + "' to '" + typeToString(lhsType) + "'");
        return false;
    }
    if (lhsType == Type::VOID || rhs.type == Type::VOID)
    {
        errorHandler->addSemanticError(line, "Cannot assign void type");
        return false;
    }
    // numeric=> implicit conversion
    if (isNumericLike(lhsType) && isNumericLike(rhs.type))
        return true;

    errorHandler->addSemanticError(line,
                                   "Incompatible types in assignment: '" + typeToString(rhs.type) + "' to '" + typeToString(lhsType) + "'");
    return false;
}
void SemanticAnalyzer::beginSwitchCaseTracking()
{
    switchCaseLabel.emplace_back();
    switchHasDefault.push_back(false);
}
void SemanticAnalyzer::endSwitchCaseTracking()
{
    if (!switchCaseLabel.empty())
    {
        switchCaseLabel.pop_back();
    }
    if (!switchHasDefault.empty())
    {
        switchHasDefault.pop_back();
    }
}
bool SemanticAnalyzer::validateCaseLabel(const ExprAttr &label, int line)
{
    if (switchCaseLabel.empty())
    {
        return true;
    }
    std::string caseKey = typeToString(label.type) + ":" + label.place;
    auto &seen = switchCaseLabel.back();
    if (seen.find(caseKey) != seen.end())
    {
        this->errorHandler->addSemanticError(
            line,
            "Duplicate case label '" + label.place + "' in same switch");
        return false;
    }
    seen.insert(caseKey);
    return true;
}
bool SemanticAnalyzer::validateDefaultLabel(int line)
{
    if (switchCaseLabel.empty())
    {
        return true;
    }

    if (switchHasDefault.back())
    {
        this->errorHandler->addSemanticError(
            line,
            "Duplicate default in the same switch");
        return false;
    }
    switchHasDefault.back() = true;
    return true;
}
void SemanticAnalyzer::enterSwitchContext()
{
    this->enterSwitch();
    this->symTable->addScope();
    this->beginSwitchCaseTracking();
}
void SemanticAnalyzer::leaveSwitchContext()
{
    this->endSwitchCaseTracking();
    this->symTable->LeaveScope();
    this->exitSwitch();
}