#ifndef TYPES_H
#define TYPES_H
#include <string>
#include <vector>
using namespace std;
enum class Type
{
    INT,
    FLOAT,
    CHAR,
    BOOL,
    STRING,
    VOID,
    UNKNOWN,
};
struct Symbol
{
    string name;
    string irName;
    Type dataType = Type::UNKNOWN;
    bool isConst = false;
    bool isInitialized = false;
    bool isUsed = false;
    bool isFunction = false;
    bool isRemoved = false;
    int declaredLine = -1;
    int scopeLevel = 0;
    vector<Type> paramTypes;
    vector<string> paramNames;
    vector<string> defaultValues;
    Type returnType = Type::VOID;
    Symbol(const string &name,
           const string &irName,
           Type dataType = Type::UNKNOWN,
           bool isConst = false,
           bool isInitialized = false,
           bool isUsed = false,
           bool isFunction = false,
           int declaredLine = -1,
           int scopeLevel = 0, Type returnType = Type::VOID)
        : name(name), irName(irName), dataType(dataType),
          isConst(isConst), isInitialized(isInitialized),
          isUsed(isUsed), isFunction(isFunction),
          declaredLine(declaredLine), scopeLevel(scopeLevel),
          returnType(returnType)
    {
    }
};
inline string typeToString(Type type)
{
    switch (type)
    {
    case Type::INT:
        return "int";
    case Type::FLOAT:
        return "float";
    case Type::CHAR:
        return "char";
    case Type::BOOL:
        return "bool";
    case Type::STRING:
        return "string";
    case Type::VOID:
        return "void";
    default:
        return "unknown";
    }
}

struct ExprAttr
{
    Type type = Type::UNKNOWN;
    string place;
    bool isLvalue;
    bool isConst;
    bool *isUsed;
    ExprAttr(Type exprType, const string &exprPlace, bool isLvalue = false, bool isConst = false, bool *isUsed = nullptr) : type(exprType), place(exprPlace), isLvalue(isLvalue), isConst(isConst), isUsed(isUsed) {}
};
inline bool isNumericLike(Type type)
{
    return type == Type::INT || type == Type::FLOAT ||
           type == Type::CHAR || type == Type::BOOL;
}

#endif
