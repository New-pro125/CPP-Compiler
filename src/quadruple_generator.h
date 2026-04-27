#ifndef QUADRAPLE_GENERATOR_H
#define QUADRAPLE_GENERATOR_H

#include <vector>
#include "quadruple.h"
using namespace std;
class QuadrupleGenerator
{
private:
    vector<Quadruple> quads;
    int tempCounter = 0;
    int labelCounter = 0;
    int suppressionDepth = 0;

public:
    void emit(const string &op, const string &arg1, const string &arg2, const string result);

    int nextQuad() const;

    string newTemp();
    string newLabel();

    void rollbackTo(int index);
    void beginSuppression();
    void endSuppression();
    void replaceNames(const vector<pair<string, string>> &renameEvents);
    void print() const;
};

#endif
