#ifndef QUADRAPLE_GENERATOR_H
#define QUADRAPLE_GENERATOR_H

#include <list>
#include <vector>
#include "quadruple.h"
class QuadrupleGenerator
{
private:
    std::vector<Quadruple> quads;
    int tempCounter = 0;
    int labelCounter = 0;

public:
    void emit(const std::string &op, const std::string &arg1, const std::string &arg2, const std::string result);

    int nextQuad() const;

    std::string newTemp();
    std::string newLabel();

    void backpatch(std::list<int> &indices, const std::string &label);
    std::list<int> merge(const std::list<int> &left, const std::list<int> &right) const;
    const std::vector<Quadruple> &getQuadraples() const;
    std::string formatTable() const;
};

#endif