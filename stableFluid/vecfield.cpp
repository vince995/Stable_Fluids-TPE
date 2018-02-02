#include "vecfield.h"

VecField::VecField(int size) : m_size(size)
{
    m_VecField = new vector[size*size];
}

VecField::~VecField(){
    delete m_VecField;
}

float VecField::getPas(){
    return 1.f/(m_size-2);
}

void VecField::reset(){
    for(int i = 0; i < m_size*m_size; i++){
             m_VecField[i] = vector(0, 0);
    }
}

vector& VecField::operator ()(int x, int y){
    return m_VecField[x + y*m_size];
}


