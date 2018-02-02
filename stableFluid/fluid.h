#ifndef FLUID_H
#define FLUID_H

#include "scalarfield.h"
#include "vecfield.h"

class Fluid
{
public:
    Fluid(int size, float _dt);
    ~Fluid();
    void diffuse(VecField &in, VecField &out, float nu);
    void advect(VecField &in, VecField &out);
    void advectS(scalarField &in, scalarField &out, VecField &u);
    void forces(VecField &u, vector force);
    void divPasCarreField(VecField &u, scalarField &divpout);
    void project(VecField &u, scalarField &phi, scalarField &divPas);
    void update();
    void reset();
    void addForces(int i, int j, float x, float y);
    void addDensity(int i, int j, float quantity);
    void addT(int i, int j, float T);
    vector getVec(int i, int j);
    float getDens(int i, int j);
    float getT(int i, int j);

private:
    VecField *u0;
    VecField *u1;

    scalarField *s0;
    scalarField *s1;

    scalarField *t0;
    scalarField *t1;

    scalarField *phi;
    scalarField *divPas;
    int m_size;
    float dt;

    void setBound(VecField &u);
    void setScalarBound(scalarField &s);

};

#endif // FLUID_H
