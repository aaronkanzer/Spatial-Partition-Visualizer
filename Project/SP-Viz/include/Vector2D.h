#ifndef Vector2D_h
#define Vector2D_h

#include <cmath>

// Forward references of each of the structs
struct Vector2D;

// Vector2D performs vector operations with 2-dimensions
//!  This class represents any vector within the game, usually a location or velocity
struct Vector2D
{
    // Note: x,y are a convention
    //! The first value of the pair.
    float x;
    //! The second value of the pair.
    float y;

    // Default conostrutcor
    // 'why default?' https://stackoverflow.com/questions/20828907/the-new-keyword-default-in-c11
    Vector2D() = default;

    // The "Real" constructor we want to use.
    //! This initializes the pair: a to x, b to y
    Vector2D(float a, float b)
    {
        x = a;
        y = b;
    }

    // Multiplication Operator
    //! Multiply the vector by a uniform-scalar.
    Vector2D &operator*=(float s)
    {
        x *= s;
        y *= s;
        return (*this);
    }

    //! Divide the vector by a uniform-scalar.
    Vector2D &operator/=(float s)
    {
        x /= s;
        y /= s;
        return (*this);
    }

    //! Add another vector to this vector.
    Vector2D &operator+=(const Vector2D &v)
    {
        x += v.x;
        y += v.y;
        return (*this);
    }

    //! Subtract another vector from this vector.
    Vector2D &operator-=(const Vector2D &v)
    {
        x -= v.x;
        y -= v.y;
        return (*this);
    }
};

//! Multiply the vector by a uniform-scalar and return a new Vector2D.
inline Vector2D operator*(const Vector2D &v, float s)
{
    return Vector2D(v.x * s, v.y * s);
}

//! Divide the vector by a uniform-scalar and return a new Vector2D.
inline Vector2D operator/(const Vector2D &v, float s)
{
    return Vector2D(v.x / s, v.y / s);
}

//! Negate the vector and return a new Vector2D.
inline Vector2D operator-(const Vector2D &v)
{
    return Vector2D(-v.x, -v.y);
}

//! Return the magnitude of the vector.
inline float Magnitude(const Vector2D &v)
{
    return sqrt(pow(v.x, 2) + pow(v.y, 2));
}

//! Add two vectors together and return a new Vector2D.
inline Vector2D operator+(const Vector2D &a, const Vector2D &b)
{
    return Vector2D(a.x + b.x, a.y + b.y);
}

//! Subtract two vectors and return a new Vector2D.
inline Vector2D operator-(const Vector2D &a, const Vector2D &b)
{
    return Vector2D(a.x - b.x, a.y - b.y);
}

//! Set a vectors magnitude to 1
inline Vector2D Normalize(const Vector2D &v)
{
    float mag = Magnitude(v);
    return Vector2D(v.x / mag, v.y / mag);
}

#endif