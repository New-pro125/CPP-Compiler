#include "quadruple_generator.h"
#include <iostream>
#include <iomanip>
void QuadrupleGenerator::emit(const std::string &op, const std::string &arg1, const std::string &arg2, const std::string result)
{
    if (this->suppressionDepth > 0)
        return;
    this->quads.push_back(Quadruple{op, arg1, arg2, result});
}
void QuadrupleGenerator::beginSuppression()
{
    this->suppressionDepth++;
}
void QuadrupleGenerator::endSuppression()
{
    if (this->suppressionDepth > 0)
        this->suppressionDepth--;
}
int QuadrupleGenerator::nextQuad() const
{
    return quads.size();
}
std::string QuadrupleGenerator::newTemp()
{
    this->tempCounter++;
    return "t" + std::to_string(tempCounter);
}
std::string QuadrupleGenerator::newLabel()
{
    this->labelCounter++;
    return "L" + std::to_string(labelCounter);
}

void QuadrupleGenerator::rollbackTo(int index)
{
    if (index < 0)
        index = 0;
    if (index < (int)quads.size())
        quads.resize((int)index);
}

void QuadrupleGenerator::replaceNames(const std::vector<std::pair<std::string, std::string>> &renameEvents)
{
    for (Quadruple &q : quads)
    {
        for (const auto &event : renameEvents)
        {
            if (q.arg1 == event.first)
                q.arg1 = event.second;
            if (q.arg2 == event.first)
                q.arg2 = event.second;
            if (q.result == event.first)
                q.result = event.second;
        }
    }
}

void QuadrupleGenerator::print() const
{
    std::cout << "\nQuadruples\n";
    std::cout << std::left << std::setw(7) << "INDEX" << std::setw(12) << "OPERATOR" << std::setw(12)
              << "ARG1" << std::setw(12) << "ARG2" << std::setw(12) << "RESULT" << "\n";
    std::cout << "-------------------------------------------------------\n";
    for (size_t i = 0; i < quads.size(); ++i)
    {
        const auto &q = quads[i];
        std::cout << std::left << std::setw(7) << i + 1 << std::setw(12) << q.oper << std::setw(12) << q.arg1
                  << std::setw(12) << q.arg2 << std::setw(12) << q.result << "\n";
    }
}
