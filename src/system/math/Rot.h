#ifndef MATH_ROT_H
#define MATH_ROT_H
#include "math/Vec.h"
#include "math/Mtx.h"

void Multiply(const Transform&, const Transform&, Transform&);
void MakeRotMatrix(const Vector3&, Hmx::Matrix3&, bool);
void MakeEulerScale(const Hmx::Matrix3&, Vector3&, Vector3&);

#endif
