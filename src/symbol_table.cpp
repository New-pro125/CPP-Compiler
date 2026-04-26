#include "symbol_table.h"
#include <iostream>
#include <iomanip>

SymbolTable::SymbolTable()
{
    currentScopeLevel = 0;
    scopes.push_back(std::unordered_map<std::string, Symbol *>());
}
std::string SymbolTable::getIRName(const std::string &symbol_name)
{
    Symbol *sym = this->lookup(symbol_name);
    return sym ? sym->irName : symbol_name;
}
bool SymbolTable::insert(const std::string &symbol_name, Symbol sym)
{
    if (scopes.back().find(symbol_name) != scopes.back().end())
        // symbol exists
        return false;
    sym.name = symbol_name;
    sym.scopeLevel = currentScopeLevel;
    // Added to handle name mangling for symbols
    sym.irName = symbol_name;

    if (!sym.isFunction)
    {
        if (symbolVersions.find(symbol_name) == symbolVersions.end())
        {
            symbolVersions[symbol_name] = 0;
        }
        else
        {
            if (symbolVersions[symbol_name] == 0)
            {
                for (Symbol &oldSym : archive)
                {
                    if (!oldSym.isFunction && oldSym.name == symbol_name && oldSym.irName == oldSym.name)
                    {
                        oldSym.irName = oldSym.name + "@0";
                        renameEvents.push_back({oldSym.name, oldSym.irName});
                    }
                }
            }
            symbolVersions[symbol_name]++;
            sym.irName = sym.name + "@" + std::to_string(symbolVersions[symbol_name]);
        }
    }

    this->archive.push_back(sym);

    scopes.back()[symbol_name] = &this->archive.back();
    return true;
}

const std::vector<std::pair<std::string, std::string>> &SymbolTable::getRenameEvents() const
{
    return renameEvents;
}

std::vector<Symbol> SymbolTable::getUnusedSymbolsInCurrentScope()
{
    std::vector<Symbol> unused;
    for (auto &pair : scopes.back())
        // loop only in current scope
        if (!(pair.second)->isUsed && !(pair.second)->isFunction)
            unused.push_back(*pair.second);
    return unused;
}

void SymbolTable::addScope()
{
    currentScopeLevel++;
    scopes.push_back(std::unordered_map<std::string, Symbol *>());
}

Symbol *SymbolTable::lookup(const std::string &symbol_name)
{
    for (int i = (int)(scopes.size()) - 1; i >= 0; i--)
    {
        auto it = scopes[i].find(symbol_name);
        if (it != scopes[i].end())
            return (it->second);
    }
    return nullptr;
}

void SymbolTable::printSymbolTable()
{
    std::cout << "\nSymbol Table\n";
    std::cout << std::left << std::setw(20) << "Name" << std::setw(10) << "Type" << std::setw(8)

              << "Scope" << std::setw(8) << "Const" << std::setw(8) << "Init" << std::setw(8) << "Used"
              << std::setw(8) << "Func" << std::setw(8) << "Line" << std::endl;
    std::cout << std::string(78, '-') << std::endl;
    for (int i = 0; i < (int)this->archive.size(); i++)
    {
        const Symbol &sym = this->archive[i];
        if (sym.isRemoved)
            continue;
        std::cout << std::left << std::setw(20) << sym.irName << std::setw(10) << typeToString(sym.dataType) << std::setw(8)
                  << sym.scopeLevel << std::setw(8)
                  << (sym.isConst ? "yes" : "no")
                  << std::setw(8) << (sym.isInitialized ? "yes" : "no") << std::setw(8) << (sym.isUsed ? "yes" : "no")
                  << std::setw(8) << (sym.isFunction ? "yes" : "no") << std::setw(8) << sym.declaredLine << std::endl;
        if (sym.isFunction)
        {
            std::cout << "Return: " << typeToString(sym.returnType) << "| Params: ";
            for (size_t p = 0; p < sym.paramTypes.size(); p++)
            {
                if (p > 0)
                    std::cout << ", ";
                std::cout << typeToString(sym.paramTypes[p]) << " " << sym.paramNames[p];
                if (p < sym.defaultValues.size() && !sym.defaultValues[p].empty())
                    std::cout << " = " << sym.defaultValues[p];
            }
            std::cout << std::endl;
        }
    }
}

bool SymbolTable::removeCurrentScopeSymbol(const std::string &symbol_name)
{
    auto it = scopes.back().find(symbol_name);
    if (it == scopes.back().end())
        return false;
    if (it->second)
        it->second->isRemoved = true;
    scopes.back().erase(it);
    return true;
}

void SymbolTable::removeCurrentScopeSymbols()
{
    for (auto &entry : scopes.back())
    {
        if (entry.second)
            entry.second->isRemoved = true;
    }
    scopes.back().clear();
}

void SymbolTable::LeaveScope()
{
    if (scopes.size() > 1)
    {
        // don't pop the global scope
        scopes.pop_back();
        currentScopeLevel--;
    }
}
