#ifndef MATH_ROT_H
#define MATH_ROT_H

#include "utl/TextStream.h"
#include "math/Vec.h"
#include "math/Mtx.h"

#define PI 3.14159265358979323846
#define RAD2DEG 57.2957763671875f
#define DEG2RAD 0.01745329238474369049f

void Multiply(const Vector3&, const Transform&, Vector3&);
void Multiply(const Transform&, const Transform&, Transform&);
void Multiply(const Hmx::Matrix3&, const Hmx::Matrix3&, Hmx::Matrix3&);
void MakeRotMatrix(const Vector3&, Hmx::Matrix3&, bool);
void MakeScale(const Hmx::Matrix3&, Vector3&);
void MakeEuler(const Hmx::Matrix3&, Vector3&);
void MakeEulerScale(const Hmx::Matrix3&, Vector3&, Vector3&);
void Normalize(const Hmx::Matrix3&, Hmx::Matrix3&);
void MakeRotMatrix(const Hmx::Quat&, Hmx::Matrix3&);
void Invert(const Transform&, Transform&);
void Interp(const Hmx::Quat&, const Hmx::Quat&, float, Hmx::Quat&);

TextStream& operator<<(TextStream& ts, const Hmx::Quat& v);
TextStream& operator<<(TextStream& ts, const Vector3& v);
TextStream& operator<<(TextStream& ts, const Vector2& v);
TextStream& operator<<(TextStream& ts, const Hmx::Matrix3& m);
TextStream& operator<<(TextStream& ts, const Transform& t);

#endif
