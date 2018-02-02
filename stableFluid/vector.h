#ifndef VECTOR_H
#define VECTOR_H


class vector
{
public:
    vector(float _x = 0, float _y = 0);
    vector add(vector &b);
    vector substract(vector &b);
    vector multiply(vector &b);
    vector multiply(float b);
    vector multiply(int b);
    vector& operator += (const vector &b);
    vector& operator -= (const vector &b);
    vector& operator *= (const vector &b);
    vector& operator *= (const float &scale);
    vector& operator /= (const float &div);

    float x;
    float y;
};

vector operator+(vector const &a, vector const &b);
vector operator-(vector const& a, vector const& b);
vector operator*(vector const& a, float const& scale);
vector operator*(float const& scale,vector const& a);
vector operator/(vector const& a,float const& div);
vector operator/(float const& div,vector const& a);

#endif // VECTOR_H
