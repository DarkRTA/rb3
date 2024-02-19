#ifndef MATH_VEC_H
#define MATH_VEC_H

class Vector2 {
public:
    float x;
    float y;
};

class Vector3 {
public:
    static Vector3 sX;
    static Vector3 sY;
    static Vector3 sZ;
    static Vector3 sZero;

    float x;
    float y;
    float z;

    Vector3(float f1, float f2, float f3) : x(f1), y(f2), z(f3) {}

    // Vector3() {};
    // Vector3(float, float, float);
    // Vector3(const Vector3 &);
    // void Set(float, float, float); // fn_800CB1A4 - same as as __ct__7Vector3Ffff?
    // Vector3 *operator=(const Vector3 &); // fn_800D8AC8
    // void operator*=(float);
    // Vector3 *operator-=(const Vector3 &);
    // Vector3 *operator+=(const Vector3 &);
    // void Zero();
    // bool operator==(const Vector3 &) const;
    // bool operator!=(const Vector3 &) const;
};

class Vector4 {
public:
    static Vector4 sX;
    static Vector4 sY;
    static Vector4 sZ;
    static Vector4 sW;
    static Vector4 sZero;
    float x;
    float y;
    float z;
    float w;

    Vector4(float f1, float f2, float f3, float f4) : x(f1), y(f2), z(f3), w(f4) {}

    // Vector4(const Vector4 &);
};

#endif
