#include <iostream>
#include <fstream>
#include "compiler.h"
using namespace std;
string readFile(const string path)
{
    char ch;
    ifstream file(path);
    if (!file.is_open())
    {
        cerr << "Failed to Open File: " << path << "\n";
        return "";
    }
    string file_content;
    file >> noskipws;
    while (file >> ch)
        file_content += ch;
    file.close();
    return file_content;
}
int main(int argc, char **argv)
{
    if (argc < 2)
    {
        cerr << "Usage: ./compiler <file>.cpp" << "\n";
        return 1;
    }
    string source_text = readFile(argv[1]);
    if (source_text.empty())
    {
        cerr << "Error: Compiling Empty file" << "\n";
        return 1;
    }
    Compiler *inst = new Compiler();
    const bool compiled = inst->compile(source_text);
    inst->printErrors();
    cout << "_____________________________\n";
    inst->printQuadrapleTables();
    cout << "______________________________\n";
    inst->printSymbolTable();
    delete inst;
    return compiled ? 0 : 2;
}
