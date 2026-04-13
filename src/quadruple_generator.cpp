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
void QuadrupleGenerator::backpatch(std::vector<int> &indices, const std::string &label)
{
    for (int idx : indices)
    {
        if (idx >= 0 && idx < (int)quads.size())
        {
            quads[idx].result = label;
        }
    }
}
std::vector<int> QuadrupleGenerator::merge(const std::vector<int> &left, const std::vector<int> &right) const
{
    std::vector<int> out(left.begin(), left.end());
    out.insert(out.end(), right.begin(), right.end());
    return out;
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
const std::vector<Quadruple> &QuadrupleGenerator::getQuadraples() const
{
    return quads;
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