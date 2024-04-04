#ifndef MATH_ROT_H
#define MATH_ROT_H

#include "utl/TextStream.h"
#include "math/Vec.h"
#include "math/Mtx.h"

void Multiply(const Transform&, const Transform&, Transform&);
void MakeRotMatrix(const Vector3&, Hmx::Matrix3&, bool);
void MakeEulerScale(const Hmx::Matrix3&, Vector3&, Vector3&);

TextStream& operator<<(TextStream& ts, const Hmx::Quat& v);
TextStream& operator<<(TextStream& ts, const Vector3& v);
TextStream& operator<<(TextStream& ts, const Vector2& v);
TextStream& operator<<(TextStream& ts, const Hmx::Matrix3& m);
TextStream& operator<<(TextStream& ts, const Transform& t);

#endif
