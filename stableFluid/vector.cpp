#include "vector.h"
#include <iostream>

vector::vector(float _x, float _y) : x(_x), y(_y)
{

}

vector& vector::operator += (const vector &b){
    x += b.x;
    y += b.y;

    return *this;
}

vector& vector::operator -= (const vector &b){
    x -= b.x;
    y -= b.y;

    return *this;
}

vector& vector::operator *= (const float &scale){
    x *= scale;
    y *= scale;

    return *this;
}

vector& vector::operator /= (const float &div){
    x /= div;
    y /= div;

    return *this;
}

vector operator +(vector const& a, vector const& b){
    vector sum(a);
    sum += b;
    return sum;
}

vector operator -(vector const& a, vector const& b){
    vector difference(a);
    difference -= b;
    return difference;
}

vector operator *(vector const& a, float const& scale){
    vector product(a);
    product *= scale;
    return product;
}

vector operator *(float const& scale,vector const& a){
    vector product(a);
    product *= scale;
    return product;
}

vector operator /(vector const& a, float const& div){
    vector quotient(a);
    quotient /= div;
    return quotient;
}

vector operator /(float const& div,vector const& a){
    vector quotient(a);
    quotient /= div;
    return quotient;
}


