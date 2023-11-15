#ifndef RB3_VECTOR_OPS_HPP
#define RB3_VECTOR_OPS_HPP
#include "vector3.hpp"
#include "hmx/matrix3.hpp"

// taken from RB2 and GDRB
void operator-(const Vector3&, const Vector3&);
void operator+(const Vector3&, const Vector3&); 
float operator*(const Vector3&, const Vector3&);
void operator*(const Vector3&, float);
void operator-(const Vector3&);
void operator*(float, const Vector3&);
void operator/(const Vector3&, float);

void Add(const Vector3&, const Vector3&, Vector3&);
void Subtract(const Vector3&, const Vector3&, Vector3&);

void Multiply(const Vector3&, const Hmx::Matrix3&, Vector3&);

void Negate(const Vector3&, Vector3&);

float Dot(const Vector3&, const Vector3&);
void Cross(const Vector3&, const Vector3&, Vector3&);
void Normalize(const Vector3&, Vector3&);
void NormalizeScale(const Vector3&, float, Vector3&);
void Interp(const Vector3&, const Vector3&, float, Vector3&);

float Length(const Vector3&);
float LengthSquared(const Vector3&);
float Distance(const Vector3&, const Vector3&);

void Scale(const Vector3&, float, Vector3&);
void Scale(const Vector3&, const Vector3&, Vector3&);
void Scale(const Vector3&, const Hmx::Matrix3&, Hmx::Matrix3&);
void ScaleAdd(const Vector3&, const Vector3&, float, Vector3&);

void RotateAboutZ(const Vector3&, float, Vector3&);
void MakeRotMatrix(const Vector3&, Hmx::Matrix3&, bool);
void MakeRotMatrix(const Vector3&, const Vector3&, Hmx::Matrix3&);

#endif
