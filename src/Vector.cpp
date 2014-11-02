#include "Vector.h"

Vector::Vector()
{
    x = 0.0;
    y = 0.0;
    z = 0.0;
}

Vector::Vector(float xx, float yy, float zz)
{
    x = xx;
    y = yy;
    z = zz;
}

float Vector::r()
{
    return sqrt(pow(x, 2.0) + pow(y, 2.0) + pow(z, 2.0));
}

float Vector::theta()
{
    return acos(y/r());
}

float Vector::phi()
{
    return atan2(z, x);
}

float Vector::rho()
{
    return sqrt(pow(x, 2.0) + pow(z, 2.0));
}

void Vector::r(float f)
{
    float radius = r();
    x *= (f/radius)+1;
    y *= (f/radius)+1;
    z *= (f/radius)+1;
}

void Vector::theta(float f)
{
    float t = theta();
    x *= sin(f+t)/sin(t);
    z *= sin(f+t)/sin(t);
    y *= cos(f+t)/cos(t);
}

void Vector::phi(float f)
{
    float px = x * cos(f) - z * sin(f);
    z = x * sin(f) + z * cos(f);
    x = px;
}


void Vector::rho(float f)
{
    x *= f/rho();
    z *= f/rho();
}

Vector& Vector::operator+=(const Vector& v)
{
    this->x += v.x;
    this->y += v.y;
    this->z += v.z;
    return *this;
}

Vector& Vector::operator-=(const Vector& v)
{
    this->x -= v.x;
    this->y -= v.y;
    this->z -= v.z;
    return *this;
}

Vector& Vector::operator*=(const float& f)
{
    this->x *= f;
    this->y *= f;
    this->z *= f;
    return *this;
}

Vector& Vector::operator/=(const float& f)
{
    this->x /= f;
    this->y /= f;
    this->z /= f;
    return *this;
}

float& Vector::operator*=(const Vector& v)
{
    float ret (this->x*v.x + this->y*v.y + this->z*v.z);
    return ret;
}

Vector& Vector::operator|=(const Vector& v)
{
    this->x = this->y*v.z - this->z*v.y;
    this->y = this->z*v.x - this->x*v.z;
    this->z = this->x*v.y - this->y*v.x;
    return *this;
}

Vector& Vector::operator~()
{
    float invLen = 1/this->r();
    return (*this)*invLen;
}


Vector& Vector::operator+(const Vector& rhs)
{
    Vector v = {this->x + rhs.x, this->y + rhs.y, this->z + rhs.z};
    return v;
}

Vector& Vector::operator-(const Vector& rhs)
{
    Vector v = {this->x - rhs.x, this->y - rhs.y, this->z - rhs.z};
    return v;
}

Vector& Vector::operator*(const float& rhs)
{
    Vector v = {this->x * rhs, this->y * rhs, this->z * rhs};
    return v;
}

Vector& Vector::operator/(const float& rhs)
{
    Vector v = {this->x / rhs, this->y / rhs, this->z / rhs};
    return v;
}

float& Vector::operator*(const Vector& rhs)
{
    return (*this *= rhs);
}

Vector& Vector::operator|(const Vector& rhs)
{
    Vector lhsOut =
    {
        this->y*rhs.z - this->z*rhs.y,
        this->z*rhs.x - this->x*rhs.z,
        this->x*rhs.y - this->y*rhs.x
    };
    return lhsOut;
}

std::vector<GLfloat> Vector::homogenousCoord(GLfloat f)
{
    return
    {
        this->x, this->y, this->z, f
    };
}

std::ostream& operator<< (std::ostream &out, Vector &cPoint)
{
    out << "Vector: [" << cPoint.x << "\t" <<
        cPoint.y << "\t" <<
        cPoint.z << "]";
    return out;
}
