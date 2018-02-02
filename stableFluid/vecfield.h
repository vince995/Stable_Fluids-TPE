#ifndef VECFIELD_H
#define VECFIELD_H

#include "vector.h"

class VecField
{
public:
    VecField(int size);
    ~VecField();
    float getPas();
    vector& operator()(int x, int y);
    void reset();

private:
    vector *m_VecField;
    int m_size;
};

#endif // VECFIELD_H
