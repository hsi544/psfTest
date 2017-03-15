/* $Revision: VERSION PLACEHOLDER $
******************************************************************************
*       COPYRIGHT  PGS, Inc.  2015  -  All Rights Reserved
* This software is the property of PGS, Inc.  No part of this code
* may be copied in any form or by any means without the expressed written
* consent of PGS, Inc.  Copying, use or modification of this software
* by any person other than a PGS employee is illegal unless that
* person has a software license agreement with PGS, Inc. to do so.
* NOTICE: This is confidential information not to be discussed or used
* outside of PGS.
******************************************************************************/
#ifndef _PM_GPU_COMPLEX
#define _PM_GPU_COMPLEX

#include "cuComplex.h"

#ifndef I
    #define I ( make_cuFloatComplex( 0.0f, 1.0f ) )
#endif

__forceinline__ __device__
const cuFloatComplex operator+( const cuFloatComplex &lhs, const cuFloatComplex &rhs )
{
    return cuCaddf( lhs, rhs );
}

__forceinline__ __device__
const cuFloatComplex operator+( const float &lhs, const cuFloatComplex &rhs )
{
    return make_cuFloatComplex( lhs + rhs.x, rhs.y );
}

__forceinline__ __device__
const cuFloatComplex operator+( const cuFloatComplex &lhs, const float &rhs )
{
    return make_cuFloatComplex( lhs.x + rhs, lhs.y + rhs );
}

__forceinline__ __device__
const cuFloatComplex operator-( const cuFloatComplex &lhs, const cuFloatComplex &rhs )
{
    return cuCsubf( lhs, rhs );
}

__forceinline__ __device__
const cuFloatComplex operator-( const float &lhs, const cuFloatComplex &rhs )
{
    return make_cuFloatComplex( lhs - rhs.x, -rhs.y );
}

__forceinline__ __device__
const cuFloatComplex operator*( const cuFloatComplex &lhs, const cuFloatComplex &rhs )
{
    return cuCmulf( lhs, rhs );
}

__forceinline__ __device__
const cuFloatComplex operator*( const float &lhs, const cuFloatComplex &rhs )
{
    return make_cuFloatComplex( lhs * rhs.x, lhs * rhs.y );
}

__forceinline__ __device__
const cuFloatComplex operator*( const cuFloatComplex &lhs, const float &rhs )
{
    return make_cuFloatComplex( lhs.x * rhs, lhs.y * rhs );
}

__forceinline__ __device__
const cuFloatComplex operator/( const cuFloatComplex &lhs, const cuFloatComplex &rhs )
{
    return cuCdivf( lhs, rhs );
}

__forceinline__ __device__
const cuFloatComplex operator/( const float &lhs, const cuFloatComplex &rhs )
{
    return cuCdivf( make_cuFloatComplex( lhs, 0 ), rhs );
}

__forceinline__ __device__
const cuFloatComplex operator/( const cuFloatComplex &lhs, const float &rhs )
{
    return make_cuFloatComplex( lhs.x/rhs, lhs.y/rhs );
}

__forceinline__ __device__
cuFloatComplex operator-( const cuFloatComplex &rhs )
{
    return make_cuFloatComplex( -rhs.x, -rhs.y );
}

__forceinline__ __device__
cuFloatComplex cexpf( const cuFloatComplex &z )
{
    double rho = exp ( z.x );
    return make_cuFloatComplex( rho * cosf( z.y ), rho * sinf( z.y ) );
}

__forceinline__ __device__
cuFloatComplex conjf( const cuFloatComplex &z )
{
    return make_cuFloatComplex( z.x, -z.y );
}

__forceinline__ __device__
float cabsf( const cuFloatComplex &z )
{
    return cuCabsf( z );
}

__forceinline__ __device__
float crealf( const cuFloatComplex &z )
{
    return z.x;
}

__forceinline__ __device__
float cimagf( const cuFloatComplex &z )
{
    return z.y;
}

__forceinline__ __device__
cuFloatComplex csqrtf( const cuFloatComplex &z)
{
    cuFloatComplex retval;
    float r;
    float x = z.x;
    float y = z.y;

    if( y == 0.0f )
    {
        if (x < 0.0f)
            retval = make_cuFloatComplex( 0.0f, sqrtf(-x) );
        else
            retval = make_cuFloatComplex( sqrtf(x), 0.0f );
    }
    else
    {
        if( x == 0.0f)
        {
            r = sqrtf( 0.5f * fabsf (y) );
            retval = make_cuFloatComplex( r, y > 0.0f ? r : -r );
        }
        else
        {
            float t = sqrtf( 2.f * ( cabsf( z ) + fabsf (x)));
            float u = t / 2.0f;

            if( x > 0.0f)
            {
                retval = make_cuFloatComplex( u, y/t );
            }
            else
            {
                retval = make_cuFloatComplex( fabsf(y/t), y < 0 ? -u : u );
            }
        }
    }

    return retval;
}


#endif
