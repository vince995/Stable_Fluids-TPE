#include "scalarfield.h"

scalarField::scalarField(int size) : m_size(size)
{
    m_ScalarField = new float[size*size];
    for(int j = 0; j < m_size*m_size; ++j){
            m_ScalarField[j] = 0;
    }
}


scalarField::~scalarField(){
    delete m_ScalarField;
}

float scalarField::getPas(){
    return 1/(m_size-2);
}

void scalarField::reset(int x){
    for(int j = 0; j < m_size*m_size; ++j){
            m_ScalarField[j] = x;
    }
}

float& scalarField::operator ()(int x, int y){
    return m_ScalarField[x + y*m_size];
}
