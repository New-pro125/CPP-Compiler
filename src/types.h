#ifndef TYPES_H
#define TYPES_H
#include <string>
#include <vector>
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
    std::string name;
    std::string irName;
    Type dataType = Type::UNKNOWN;
    bool isConst = false;
    bool isInitialized = false;
    bool isUsed = false;
    bool isFunction = false;
    int declaredLine = -1;
    int scopeLevel = 0;
    std::vector<Type> paramTypes;
    std::vector<std::string> paramNames;
    std::vector<std::string> defaultValues;
    Type returnType = Type::VOID;
};
inline std::string typeToString(Type type)
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
    std::string place;
    bool isLvalue = false;
    bool isConst = false;
    bool *isUsed = nullptr;
};
struct ParamList
{
    std::vector<Type> types;
    std::vector<std::string> names;
    std::vector<std::string> defaults;
    std::vector<bool> isConst;
};
inline ExprAttr *makeExpr(const std::string &place, Type type)
{
    auto *e = new ExprAttr();
    e->place = place;
    e->type = type;
    return e;
}
inline bool isNumericLike(Type type)
{
    return type == Type::INT || type == Type::FLOAT ||
           type == Type::CHAR || type == Type::BOOL;
}

#endif
