/**
* This file is part of
* 
* 8888888b.                    888    888      888      d8b                  
* 888  "Y88b                   888    888      888      Y8P                  
* 888    888                   888    888      888                           
* 888    888  .d88b.   8888b.  888888 88888b.  888      888  8888b.  888d888 
* 888    888 d8P  Y8b     "88b 888    888 "88b 888      888     "88b 888P"   
* 888    888 88888888 .d888888 888    888  888 888      888 .d888888 888     
* 888  .d88P Y8b.     888  888 Y88b.  888  888 888      888 888  888 888     
* 8888888P"   "Y8888  "Y888888  "Y888 888  888 88888888 888 "Y888888 888   
* 
* Copyright © 2012 Emil Sandstø, Sebastian Reinhard
* 
*/

#ifndef VEC2D_H
#define VEC2D_H

#include "MathUtil.h"
#include <iostream>
#include <SFML/Graphics.hpp>

/**
 * A 2D vector class.
 */
class Vec2D
{
public:
    Real x; ///< The x position of the vector.
    Real y; ///< The y position of the vector.

    /**
     * Initalize the vector with x and y positions = 0.
     */
    Vec2D() : x(0), y(0) {}

    /**
     * Initalize the vector with x and y positions.
     * @param x The new x position.
     * @param y The new y position.
     */
    Vec2D(Real x, Real y) : x(x), y(y) {}

    void Set(Real x, Real y) 
    {
        this->x = x;
        this->y = y;
    }

    /**
     * Copies the vector from another vector.
     * @param c The vector to copy.
     */
    Vec2D(const Vec2D &c) 
    {
        x = c.x;
        y = c.y;
    }

    void Zero()
    {
        x = 0.0;
        y = 0.0;
    }

    /**
     * Adds two vectors together and returns the result.
     * @param a The vector to add.
     * @return The result of the two vectors.
     */
    Vec2D operator +(const Vec2D &a) const
    {
        return Vec2D(x + a.x, y + a.y);
    }

    /**
     * Adds a vector to the vector.
     * @param a The vector to add.
     */
    void operator +=(const Vec2D &a)
    {
        x += a.x;
        y += a.y;
    }

    /**
     * Subtracts one vector from another and returns the result.
     * @param a The vector to subtract
     * @return The result of the subtraction.
     */
    Vec2D operator -(const Vec2D &a) const
    {
        return Vec2D(x - a.x, y - a.y);
    }

    /**
     * Subtracts a vector from the vector.
     * @param a The vector to subtract.
     */
    void operator -=(const Vec2D &a)
    {
        x -= a.x;
        y -= a.y;
    }

    /**
     * Multiplies the vector with a scalar and returns the result.
     * @param scalar The scalar to multiply by.
     * @return The result of the multiplication.
     */
    Vec2D operator *(Real scalar) const
    {
        return Vec2D(x * scalar, y * scalar);
    }

    /**
     * Divides the vector by a scalar and returns the result.
     * @param scalar The scalar to divide by.
     * @return The result of the division.
     */
    Vec2D operator /(Real scalar) const
    {
        return Vec2D(x / scalar, y / scalar);
    }

    /**
     * Multiplies the vector by a scalar.
     * @param scalar The scalar to multiply by.
     */
    void operator *=(Real scalar)
    {
        x *= scalar;
        y *= scalar;
    }

    /**
     * Divides the vector by a scalar.
     * @param scalar The scalar to divide by.
     */
    void operator /=(Real scalar)
    {
        x /= scalar;
        y /= scalar;
    }

    /**
     * Multiplies a scalar with the vector and returns the result.
     * @param a The vector to multiply by.
     * @return The result of the multiplication.
     */
    Real operator *(const Vec2D &a)
    {
        return x * a.x + y * a.y;
    }

    /**
     * Returns the magnitude of the vector.
     * @return The magnitude of the vector.
     */
    Real Magnitude()
    {
        return sqrt(x * x + y * y);
    }

    /**
     * Normalizes the vector.
     */
    void Normalize()
    {
        Real mag = sqrt(x * x + y * y);
        if(mag > 0)
        {
            Real oneOverMag = (Real)1.0 / mag;
            x *= oneOverMag;
            y *= oneOverMag;
        }
    }

    /**
     * Returns the perpendicular vector.
     * @return The perpendicular vector.
     */
    Vec2D Perp() const
    {
        return Vec2D(-y, x);
    }

    /**
     * Truncates the vector to a given value.
     * @param max The maximum length of the vector.
     */
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

    /**
     * Copy data from a SFML vector.
     */
    void operator =(sf::Vector2f &a)
    {
        x = a.x;
        y = a.y;
    }

    /**
     * Returns the opposite vector.
     */
    Vec2D Opposite()
    {
        return Vec2D(-x, -y);
    }
};

/**
 * Returns the distance between two vectors.
 * @param from The first vector.
 * @param target The target vector.
 * @return The distance between two vectors.
 */
inline Real Distance(const Vec2D &from, const Vec2D &target)
{
    Vec2D bet = target - from;
    return bet.Magnitude();
}

/**
 * Returns the distance between two vectors in square space.
 * @param from The first vector.
 * @param target The target vector.
 * @return The distance between two vectors in square space.
 */
inline Real DistanceSqr(const Vec2D &from, const Vec2D &target)
{
    Vec2D bet = target - from;
    return bet.x * bet.x + bet.y * bet.y;
}

/**
 * Normalizes a vector and returns the result.
 * @param a The vector to normalize.
 * @return The normalized vector.
 */
inline Vec2D Normalize(const Vec2D &a)
{
    Vec2D tmp = a;
    Real mag = sqrt(tmp.x * tmp.x + tmp.y * tmp.y);
    if(mag > 0)
    {
        Real oneOverMag = (Real)1.0 / mag;
        tmp.x *= oneOverMag;
        tmp.y *= oneOverMag;
    }

    return tmp;
}

inline void PrintVec2D(const char *vectorName, const Vec2D &vec)
{
    std::cout << vectorName << "(" << vec.x << ", " << vec.y << ")\n";
}

/**
 * Returns a SFML vector of a vector.
 * @param vec The vector to create a SFML vector of.
 * @return The SFML vector of the vector.
 *//*
template <typename T>
void operator =(sf::Vector2<T> &a, const Vec2D& b)
{
    //a.x = b.x;
    //a.y = b.y;
}
*/

#endif
