#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H
#include <string>
#include <vector>
#include <queue>
#include <unordered_map>
#include "types.h"

class SymbolTable
{

private:
    std::vector<std::unordered_map<std::string, Symbol *>> scopes;
    std::deque<Symbol> archive;
    int currentScopeLevel;

public:
    SymbolTable();
    bool insert(const std::string &symbol_name, Symbol sym);
    void addScope();
    void LeaveScope();
    std::vector<Symbol> getUnusedSymbolsInCurrentScope();
    Symbol *lookup(const std::string &symbol_name);
    Symbol *lookupCurrentScope(const std::string &symbol_name);
    void printSymbolTable();
    std::string getIRName(const std::string &symbol_name);
    int getCurrentScopeLevel() const;
};

#endif