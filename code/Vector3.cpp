/// \file Vector3.cpp
/// \brief Initialization of Vector class and any associated global functions.
/// \author Ethan Gingrich
/// \version A04

#include "Vector3.hpp"

Vector3::Vector3 ()
{
    m_x = m_y = m_z = 0;
}

Vector3::Vector3 (float xyz)
{
    m_x = m_y = m_z = xyz;
}

Vector3::Vector3 (float x, float y, float z)
{
    m_x = x;
    m_y = y;
    m_z = z;
}

void
Vector3::set (float xyz)
{
    m_x = m_y = m_z = xyz;
}

void 
Vector3::set (float x, float y, float z)
{
    m_x = x;
    m_y = y;
    m_z = z;
}

void
Vector3::negate()
{
    m_x = -m_x;
    m_y = -m_y;
    m_z = -m_z;
}

float
Vector3::dot (const Vector3& v) const
{
    return (m_x * v.m_x) + (m_y * v.m_y) + (m_z * v.m_z);
}

float
Vector3::angleBetween (const Vector3& v) const
{
    float dotP = dot (v);
    float mag1 = length ();
    float mag2 = v.length ();
    float result = acos (dotP/(mag1 * mag2));

    return result;
}

Vector3
Vector3::cross (const Vector3& v) const
{
    float newX = (m_y * v.m_z) - (m_z * v.m_y);
    float newY = (m_z * v.m_x) - (m_x * v.m_z);
    float newZ = (m_x * v.m_y) - (m_y * v.m_x);

    Vector3 newV (newX, newY, newZ);

    return newV;
}

float
Vector3::length () const 
{
    return sqrt (pow (m_x, 2) + pow (m_y, 2) + pow (m_z, 2));
}

void
Vector3::normalize ()
{
    float ogLength = length();
    m_x = m_x / ogLength;
    m_y = m_y / ogLength;
    m_z = m_z / ogLength;
}

Vector3&
Vector3::operator+= (const Vector3& v)
{
    m_x = m_x + v.m_x;
    m_y = m_y + v.m_y;
    m_z = m_z + v.m_z;
    return *this;
}

Vector3&
Vector3::operator-= (const Vector3& v)
{
    m_x = m_x - v.m_x;
    m_y = m_y - v.m_y;
    m_z = m_z - v.m_z;
    return *this;
}

Vector3&
Vector3::operator*= (float s)
{
    m_x = m_x * s;
    m_y = m_y * s;
    m_z = m_z * s;
    return *this;
}

Vector3&
Vector3::operator/= (float s)
{   
    m_x = m_x / s;
    m_y = m_y / s;
    m_z = m_z / s;
    return *this;
}

Vector3
operator+ (const Vector3& v1, const Vector3& v2)
{
    Vector3 newV (v1.m_x, v1.m_y, v1.m_z);
    return newV += v2;
}

Vector3
operator- (const Vector3& v1, const Vector3& v2)
{
    Vector3 newV (v1.m_x, v1.m_y, v1.m_z);
    return newV -= v2;
}

Vector3
operator- (const Vector3& v)
{
    Vector3 newV (-v.m_x, -v.m_y, -v.m_z);
    return newV;
}

Vector3
operator* (float s, const Vector3& v)
{
    Vector3 newV (v.m_x, v.m_y, v.m_z);
    return newV *= s;
}

Vector3
operator* (const Vector3& v, float s)
{
    Vector3 newV (v.m_x, v.m_y, v.m_z);
    return newV *= s;
}

Vector3
operator/ (const Vector3& v, float s)
{
    Vector3 newV (v.m_x, v.m_y, v.m_z);
    return newV /= s;
}

std::ostream&
operator<< (std::ostream& out, const Vector3& v)
{
    out.setf(std::ios::fixed, std::ios::floatfield);
    out.precision (2);
    out << std::setw(10);
    out << v.m_x;
    
    out.setf(std::ios::fixed, std::ios::floatfield);
    out.precision (2);
    out << std::setw(10);
    out << v.m_y;

    out.setf(std::ios::fixed, std::ios::floatfield);
    out.precision (2);
    out << std::setw(10);
    out << v.m_z;
    return out;
}

bool
operator== (const Vector3& v1, const Vector3& v2)
{
    const float episilon = 0.00001;
    bool isXEqual = std::abs(v1.m_x - v2.m_x) <= episilon * std::abs(v1.m_x);
    bool isYEqual = std::abs(v1.m_y - v2.m_y) <= episilon * std::abs (v1.m_y);
    bool isZEqual = std::abs(v1.m_z - v2.m_z) <= episilon * std::abs (v1.m_z);

    return isXEqual && isYEqual && isZEqual;
}
