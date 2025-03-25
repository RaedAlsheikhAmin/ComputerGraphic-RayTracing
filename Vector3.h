#ifndef INC_477HW1_VECTOR3_H
#define INC_477HW1_VECTOR3_H

#include <cmath>
#include <iostream>

class Vector3 {
public:
    float x, y, z;

    // Constructors
    Vector3() : x(0), y(0), z(0) {}
    Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

    // Basic Arithmetic Operations
    inline Vector3 operator+(const Vector3& v) const { return Vector3(x + v.x, y + v.y, z + v.z); }
    inline Vector3 operator-(const Vector3& v) const { return Vector3(x - v.x, y - v.y, z - v.z); }
    inline Vector3 operator*(float scalar) const { return Vector3(x * scalar, y * scalar, z * scalar); }
    inline Vector3 operator/(float scalar) const { return Vector3(x / scalar, y / scalar, z / scalar); }

    // Dot Product
    inline float dot(const Vector3& v) const { return x * v.x + y * v.y + z * v.z; }

    // Cross Product
    inline Vector3 cross(const Vector3& v) const {
        return Vector3(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
    }
    inline Vector3 operator*(const Vector3& v) const { return Vector3(x * v.x, y * v.y, z * v.z); }

    // Normalize Vector
    inline Vector3 normalize() const {
        float mag = std::sqrt(x*x + y*y + z*z);
        return (*this) / (mag > 0 ? mag : 1); // Avoid division by zero
    }
    inline Vector3 operator-() const { return Vector3(-x, -y, -z); }
    friend inline Vector3 operator*(float scalar, const Vector3& v) { return Vector3(scalar * v.x, scalar * v.y, scalar * v.z); }

    inline Vector3& operator+=(const Vector3& v) {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }


    // Print (For Debugging)
    inline void print() const { std::cout << "(" << x << ", " << y << ", " << z << ")\n"; }
    inline float length() const { return std::sqrt(x * x + y * y + z * z); }
};

#endif
