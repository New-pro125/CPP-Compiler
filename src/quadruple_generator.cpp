#include "quadruple_generator.h"
#include <sstream>
#include <iomanip>
void QuadrupleGenerator::emit(const std::string &op, const std::string &arg1, const std::string &arg2, const std::string result)
{
    this->quads.push_back(Quadruple{op, arg1, arg2, result});
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
        if (idx >= 0 && idx < quads.size())
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
const std::vector<Quadruple> &QuadrupleGenerator::getQuadraples() const
{
    return quads;
}
