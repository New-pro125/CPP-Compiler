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
void QuadrupleGenerator::backpatch(std::list<int> &indices, const std::string &label)
{
    for (int idx : indices)
    {
        if (idx >= 0 && idx < quads.size())
        {
            quads[idx].result = label;
        }
    }
}
std::list<int> QuadrupleGenerator::merge(const std::list<int> &left, const std::list<int> &right) const
{
    std::list<int> out = left;
    out.insert(out.end(), right.begin(), right.end());
    return out;
}
const std::vector<Quadruple> &QuadrupleGenerator::getQuadraples() const
{
    return quads;
}
std::string QuadrupleGenerator::formatTable() const
{
    std::ostringstream oss;
    oss << "INDEX  " << std::left << std::setw(12) << "OP" << std::setw(10) << "ARG1" << std::setw(10)
        << "ARG2" << std::setw(10) << "RESULT" << "\n";
    oss << "------+-------------------------------------------\n";

    for (size_t i = 0; i < quads.size(); ++i)
    {
        const auto &q = quads[i];
        oss << std::right << std::setw(5) << i << "  " << std::left << std::setw(12) << q.oper
            << std::setw(10) << q.arg1 << std::setw(10) << q.arg2 << std::setw(10) << q.result
            << "\n";
    }
    return oss.str();
}