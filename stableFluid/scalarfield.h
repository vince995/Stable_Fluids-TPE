#ifndef SCALARFIELD_H
#define SCALARFIELD_H


class scalarField
{
public:
    scalarField(int size);
    ~scalarField();
    float getPas();
    float& operator()(int x, int y);
    void reset(int x = 0);

private:
    int m_size;
    float *m_ScalarField;
};

#endif // SCALARFIELD_H
