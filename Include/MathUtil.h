/**
* Part of AI Fun
* Copyright (c) Emil Sandstø 2012
*/
#ifndef MATHUTIL_H
#define MATHUTIL_H

#include <cmath>
#include <cfloat>
#include <stdio.h>
#include <limits>
#include <cassert>

#define PI 3.1415926535
#define PI_OVER_180 0.0174532925
#define _180_OVER_PI 57.295779513
#define HALF_PI 1.570796326
#define TWO_PI  6.283185307

#ifdef DOUBLE_PRECISION
    typedef double Real;
    #define EPSILON DBL_EPSILON
#else
    typedef float Real;
    #define EPSILON FLT_EPSILON
#endif

const int MaxInt = (std::numeric_limits<int>::max)();
const double MaxReal = (std::numeric_limits<float>::max)();
const double MinReal = (std::numeric_limits<float>::min)();

inline Real RadToDeg(Real rad)
{
    return (Real)_180_OVER_PI * rad;
}

inline Real DegToRad(Real deg)
{
    return (Real)PI_OVER_180 * deg;
}

inline bool IsEqual(Real x, Real y)
{
    if(abs(x - y) < EPSILON)
    {
        return true;
    }

    return false;
}

inline bool IsZero(Real x)
{
    return ((-MinReal < x) && (MinReal < x));
}

#endif