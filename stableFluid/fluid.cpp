#include "fluid.h"
#include <iostream>
#include <unistd.h>

Fluid::Fluid(int size, float _dt) : m_size(size), dt(_dt)//, u0(size), u1(size)
{
    u0 = new VecField(size+2);
    u1 = new VecField(size+2);

    s0 = new scalarField(size+2);
    s1 = new scalarField(size+2);

    t0 = new scalarField(size+2);
    t1 = new scalarField(size+2);
    t0->reset(22);
    t1->reset(22);

    phi = new scalarField(size+2);
    divPas = new scalarField(size+2);
}

Fluid::~Fluid(){
    delete u0;
    delete u1;
    delete s0;
    delete s1;
    delete t0;
    delete t1;
    delete phi;
    delete divPas;
}

void Fluid::setBound(VecField &u){
    int n = m_size;
    for(int j = 1; j <= n; ++j){
        u(0, j) = vector(0, u(1, j).y);
        u(n+1, j) = vector(0, u(n+1, j).y);
        u(j,0) = vector(u(j,1).x, 0);
        u(j,n+1) = vector(u(j,n+1).x,0);
    }

    u(0,0)     = 0.5 * (u(0,1)+u(1,0));
    u(n+1,n+1) = 0.5 * (u(n+1,n)+ u(n,n+1));
    u(0,n+1)   = 0.5 * (u(0,n)+ u(1,n+1));
    u(n+1,0)   = 0.5 * (u(n,0)+ u(n+1,1));
}

void Fluid::setScalarBound(scalarField &s){
    int n = m_size;
    for(int j = 1; j <= n; ++j){
        s(0, j) = s(1, j);
        s(n+1, j) = s(n+1, j);
        s(j,0) = s(j,1);
        s(j,n+1) = s(j,n+1);
    }

    s(0,0)     = 0.5 * (s(0,1)+s(1,0));
    s(n+1,n+1) = 0.5 * (s(n+1,n)+ s(n,n+1));
    s(0,n+1)   = 0.5 * (s(0,n)+ s(1,n+1));
    s(n+1,0)   = 0.5 * (s(n,0)+ s(n+1,1));
}

void Fluid::diffuse(VecField &in, VecField &out, float nu){
    int i, j, k;

    float tempo = dt * nu * m_size * m_size;

    for(k = 1; k < 50; ++k){
        for(j = 1; j < m_size; ++j){
            for(i = 1; i < m_size; ++i){
                out(i,j) = (in(i,j) + tempo * (out(i-1,j) + out(i+1,j) + out(i,j-1)+ out(i,j+1) ))/(1+4 * tempo);
            }
        }
        setBound(out);
    }
}


void Fluid::advect(VecField &in, VecField &out){
    float xd, yd;
    int id, jd;
    float Asw, Ase, Ane, Anw;
    float dtspas = dt / in.getPas();
    int n = m_size;


    for(int j = 1; j < n; ++j){
        for(int i = 1; i < n; ++i){
            xd = (float)i - dtspas * in(i, j).x;
            yd = (float)j - dtspas * in(i, j).y;

            if(xd < 0.5f) xd = 0.5f;
            if(xd > n+0.5f) xd = 0.5f +n;
            if(yd < 0.5f) yd = 0.5f;
            if(yd > n+0.5f) yd = 0.5f +n;

            id = (int) xd;
            jd = (int) yd;


            Asw = (1.f+id-xd) * (1.f+jd-yd);
            Ase = (xd - id) * (1.f+jd-yd);
            Anw = (1.f+id-xd) * (yd - jd);
            Ane = (xd - id) * (yd - jd);

            out(i,j) =
            Asw * in(id, jd) +
            Ase * in(id+1,jd) +
            Anw * in(id, jd+1) +
            Ane * in(id+1, jd+1);

        }
    }
    setBound(out);
}

void Fluid::advectS(scalarField &in, scalarField &out, VecField &u){
    float xd, yd;
    int id, jd;
    float Asw, Ase, Ane, Anw;
    float dtspas = dt / u.getPas();
    int n = m_size;

    //std::cout << dt << std::endl;


    for(int j = 1; j < n; ++j){
        for(int i = 1; i < n; ++i){
            xd = (float)i - dtspas * u(i, j).x;
            yd = (float)j - dtspas * u(i, j).y;

            if(xd < 0.5f) xd = 0.5f;
            if(xd > n+0.5f) xd = 0.5f +n;
            if(yd < 0.5f) yd = 0.5f;
            if(yd > n+0.5f) yd = 0.5f +n;

            id = (int) xd;
            jd = (int) yd;

            Asw = (1.f+id-xd) * (1.f+jd-yd);
            Ase = (xd - id) * (1.f+jd-yd);
            Anw = (1.f+id-xd) * (yd - jd);
            Ane = (xd - id) * (yd - jd);

            out(i,j) =
            Asw * in(id, jd) +
            Ase * in(id+1,jd) +
            Anw * in(id, jd+1) +
            Ane * in(id+1, jd+1);

        }
    }
    setScalarBound(out);
}

void Fluid::forces(VecField &u, vector force){
    for(int j = 1; j < m_size; ++j){
        for(int i = 1; i < m_size; ++i){
            u(i,j) = u(i,j) + force * dt;
        }
    }
}

void Fluid::divPasCarreField(VecField &u, scalarField &divpout){
    for(int j = 1; j < m_size; ++j){
        for(int i = 1; i < m_size; ++i){
            divpout(i, j) = 0.5 * (u(i+1, j).x - u(i-1, j).x + u(i, j+1).y - u(i, j-1).y) * u.getPas();
        }
    }
    setScalarBound(divpout);
}

void Fluid::project(VecField &u, scalarField &phi, scalarField &divPas){
    divPasCarreField(u, divPas);
    phi.reset();

    for(int k = 1; k < 50; ++k){
        for(int j = 1; j < m_size; ++j){
            for(int i = 1; i < m_size; ++i){
                phi(i,j) = (-divPas(i,j) + (phi(i-1,j) + phi(i+1,j) +  phi(i,j-1)+ phi(i,j+1))) / 4.0f;
            }
        }
        setScalarBound(phi);
    }

    for(int j = 1; j < m_size; ++j){
        for(int i = 1; i < m_size; ++i){
            u(i,j).x = u(i,j).x - 0.5*(phi(i+1,j) - phi(i-1,j)) / u.getPas();
            u(i,j).y = u(i,j).y - 0.5*(phi(i,j+1) - phi(i,j-1)) / u.getPas();
            u(i,j).y = u(i, j).y -0.0001*((*t0)(i, j)-22);
        }
    }
}

vector Fluid::getVec(int i, int j){
    return (*u0)(i, j);
}

float Fluid::getDens(int i, int j){
    return(*s0)(i, j);
}

float Fluid::getT(int i, int j){
    return(*t0)(i, j);
}

void Fluid::addForces(int i, int j, float x, float y){
    (*u0)(i,j) = (*u0)(i,j) + vector(x, y) * dt;
}

void Fluid::addDensity(int i, int j, float quantity){
    (*s0)(i,j) = (*s0)(i,j) + quantity;
}

void Fluid::addT(int i, int j, float T){
    (*t0)(i,j) = T;
}

void Fluid::reset(){
    u0->reset();
    u1->reset();
    s0->reset();
    s1->reset();
    t0->reset(22);
    t1->reset(22);
}

void Fluid::update(){
    //diffuse((*u1), (*u0), 1000);
    //project((*u0), (*phi), (*divPas));
    advect((*u0), (*u1));
    //forces((*u1), g);
    project((*u1), (*phi), (*divPas));
    advectS((*s0), (*phi), (*u1));
    advectS((*t0), (*t1), (*u1));

    scalarField *tmpT = t0;
    t0 = t1;
    t1 = tmpT;

    scalarField *tmpS = s0;
    s0 = phi;
    phi = tmpS;

    VecField *tmp = u0;
    u0 = u1;
    u1 = tmp;

}
