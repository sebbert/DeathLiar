/**
* Part of AI Fun
* Copyright (c) Emil Sandstø 2012
*/
#ifndef VEC2D_H
#define VEC2D_H

#include "MathUtil.h"

class Vec2D
{
public:
    Real x;
    Real y;

    Vec2D() : x(0), y(0) {}
    Vec2D(Real x, Real y) : x(x), y(y) {}
    Vec2D(const Vec2D &c) 
    {
        x = c.x;
        y = c.y;
    }

    Vec2D operator +(const Vec2D &a) const
    {
        return Vec2D(x + a.x, y + a.y);
    }

    void operator +=(const Vec2D &a)
    {
        x += a.x;
        y += a.y;
    }

    Vec2D operator -(const Vec2D &a) const
    {
        return Vec2D(x - a.x, y - a.y);
    }

    void operator -=(const Vec2D &a)
    {
        x -= a.x;
        y -= a.y;
    }

    Vec2D operator *(Real scalar) const
    {
        return Vec2D(x * scalar, y * scalar);
    }

    Vec2D operator /(Real scalar) const
    {
        return Vec2D(x / scalar, y / scalar);
    }

    void operator *=(Real scalar)
    {
        x *= scalar;
        y *= scalar;
    }

    void operator /=(Real scalar)
    {
        x /= scalar;
        y /= scalar;
    }

    Real operator *(const Vec2D &a)
    {
        return x * a.x + y * a.y;
    }

    Real Magnitude()
    {
        return sqrt(x * x + y * y);
    }

    void Normalize()
    {
        Real mag = sqrt(x * x + y * y);
        if(mag > 0)
        {
            Real oneOverMag = 1.0 / mag;
            x *= oneOverMag;
            y *= oneOverMag;
        }
    }

    Vec2D Perp() const
    {
        return Vec2D(-y, x);
    }

    void Truncate(Real max)
    {
        Real mag = sqrt(x * x + y * y);
        if(mag > max)
        {
            Normalize();
            x *= max;
            y *= max;
        }
    }

    Vec2D Negate()
    {
        return Vec2D(-x, -y);
    }
};

inline Real Distance(const Vec2D &from, const Vec2D &target)
{
    Vec2D bet = target - from;
    return bet.Magnitude();
}

inline Real DistanceSqr(const Vec2D &from, const Vec2D &target)
{
    Vec2D bet = target - from;
    return bet.x * bet.x + bet.y * bet.y;
}

inline Vec2D Normalize(const Vec2D &a)
{
    Vec2D tmp = a;
    Real mag = sqrt(tmp.x * tmp.x + tmp.y * tmp.y);
    if(mag > 0)
    {
        Real oneOverMag = 1.0 / mag;
        tmp.x *= oneOverMag;
        tmp.y *= oneOverMag;
    }

    return tmp;
}

#endif