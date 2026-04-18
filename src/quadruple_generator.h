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
    int suppressionDepth = 0;

public:
    void emit(const std::string &op, const std::string &arg1, const std::string &arg2, const std::string result);

    int nextQuad() const;

    std::string newTemp();
    std::string newLabel();

    void rollbackTo(int index);
    void beginSuppression();
    void endSuppression();
    void replaceNames(const std::vector<std::pair<std::string, std::string>> &renameEvents);
    void print() const;
};

#endif
