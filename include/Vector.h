#include <include.h>
#include <gl_inc_hs.h>

#ifndef VECTOR_H
#define VECTOR_H
#include <iostream>

class Vector
{
    public:
        Vector(float, float, float);
        Vector();
        float x, y, z;

        float r();
        float theta();
        float phi();

        float rho();

        void r(float);
        void theta(float);
        void phi(float);

        void rho(float);

        Vector& operator+=(const Vector&);
        Vector& operator-=(const Vector&);

        Vector& operator*=(const float&);
        Vector& operator/=(const float&);

        float& operator*=(const Vector&);
        Vector& operator|=(const Vector&);

        Vector& operator+(const Vector&);
        Vector& operator-(const Vector&);

        Vector& operator*(const float&);
        Vector& operator/(const float&);

        float& operator*(const Vector&);
        Vector& operator|(const Vector&);

        Vector& operator~();

        std::vector<GLfloat> homogenousCoord(GLfloat);
        friend std::ostream& operator<< (std::ostream &out, Vector &v);
     protected:
    private:
};



#endif // VECTOR_H
