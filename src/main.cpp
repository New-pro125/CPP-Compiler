#include <iostream>
#include <fstream>
#include "compiler.h"

std::string readFile(const std::string path)
{
    char ch;
    std::ifstream file(path);
    if (!file.is_open())
    {
        std::cerr << "Failed to Open File: " << path << "\n";
        return "";
    }
    std::string file_content;
    file >> std::noskipws;
    while (file >> ch)
        file_content += ch;
    file.close();
    return file_content;
}
int main(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cerr << "Usage: ./compiler <file>.cpp" << "\n";
        return 1;
    }
    std::string source_text = readFile(argv[1]);
    if (source_text.empty())
    {
        std::cerr << "Error: Compiling Empty file" << "\n";
        return 1;
    }
    Compiler *inst = new Compiler();
    const bool compiled = inst->compile(source_text);
    inst->printErrors();
    std::cout << "_____________________________\n";
    inst->printQuadrapleTables();
    delete inst;
    return compiled ? 0 : 2;
}