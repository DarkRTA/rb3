#ifndef RB3_VECTOR_OPS_HPP
#define RB3_VECTOR_OPS_HPP
#include "vector3.hpp"
#include "hmx/matrix3.hpp"

void Add(const Vector3&, const Vector3&, Vector3&);
void Subtract(const Vector3&, const Vector3&, Vector3&);

void Negate(const Vector3&, Vector3&);

float Dot(const Vector3&, const Vector3&);
void Cross(const Vector3&, const Vector3&, Vector3&);
void Normalize(const Vector3&, Vector3&);

void Scale(const Vector3&, float, Vector3&);
void Scale(const Vector3&, const Vector3&, Vector3&);
void Scale(const Vector3&, const Hmx::Matrix3&, Hmx::Matrix3&);

#endif
