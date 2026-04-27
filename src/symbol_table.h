#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H
#include <string>
#include <vector>
#include <queue>
#include <unordered_map>
#include "types.h"
using namespace std;

class SymbolTable
{

private:
    vector<unordered_map<string, Symbol *>> scopes;
    deque<Symbol> archive;
    int currentScopeLevel;
    unordered_map<string, int> symbolVersions;
    vector<pair<string, string>> renameEvents;

public:
    SymbolTable();
    bool insert(const string &symbol_name, Symbol sym);
    void addScope();
    void LeaveScope();
    vector<Symbol> getUnusedSymbolsInCurrentScope();
    Symbol *lookup(const string &symbol_name);
    bool removeCurrentScopeSymbol(const string &symbol_name);
    void removeCurrentScopeSymbols();
    void printSymbolTable();
    string getIRName(const string &symbol_name);
    const vector<pair<string, string>> &getRenameEvents() const;
};

#endif
