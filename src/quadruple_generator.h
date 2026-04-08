#ifndef QUADRAPLE_GENERATOR_H
#define QUADRAPLE_GENERATOR_H

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

    void backpatch(std::vector<int> &indices, const std::string &label);
    std::vector<int> merge(const std::vector<int> &left, const std::vector<int> &right) const;
    const std::vector<Quadruple> &getQuadraples() const;
    void print() const;
};

#endif