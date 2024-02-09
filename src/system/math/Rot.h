#ifndef MATH_ROT_H
#define MATH_ROT_H
#include "hmx/quat.hpp"
#include "hmx/matrix3.hpp"
#include "vector3.hpp"
#include "TextStream.h"
#include "vector2.hpp"
#include "transform.hpp"

// TODO: the quat class header and weak methods go in here according to RB2

void Normalize(const register Hmx::Quat&, register Hmx::Quat&);
void MakeEuler(const Hmx::Matrix3&, Vector3&);
void MakeVertical(Hmx::Matrix3&);
void MakeScale(const Hmx::Matrix3&, Vector3&);
void MakeEulerScale(const Hmx::Matrix3&, Vector3&, Vector3&);
float GetXAngle(const Hmx::Matrix3&);
float GetYAngle(const Hmx::Matrix3&);
float GetZAngle(const Hmx::Matrix3&);
void FastInterp(const Hmx::Quat&, const Hmx::Quat&, float, Hmx::Quat&);
float operator*(const Hmx::Quat&, const Hmx::Quat&);
void IdentityInterp(const Hmx::Quat&, float, Hmx::Quat&);
void InterpThunk(const Hmx::Quat&, const Hmx::Quat&, float, Hmx::Quat&);
void Interp(const Hmx::Quat&, const Hmx::Quat&, float, Hmx::Quat&);
void Interp(const Hmx::Matrix3 &, const Hmx::Matrix3 &, float, Hmx::Matrix3 &);
void MakeRotMatrix(const Vector3&, Hmx::Matrix3&, bool);
void MakeRotMatrix(const Vector3 &, const Vector3 &, Hmx::Matrix3 &);
void MakeRotMatrix(const Hmx::Quat &, Hmx::Matrix3 &);
void MakeEuler(const Hmx::Quat &, Vector3 &);
void MakeRotQuat(const Vector3 &, const Vector3 &, Hmx::Quat &);
void MakeRotQuatUnitX(const Vector3 &, Hmx::Quat &);

TextStream &operator<<(TextStream &, const Hmx::Quat &);
TextStream &operator<<(TextStream &, const Vector3 &);
TextStream &operator<<(TextStream &, const Vector2 &);
TextStream &operator<<(TextStream &, const Hmx::Matrix3 &);
TextStream &operator<<(TextStream &, const Transform &);

void Multiply(const register Transform &, const register Transform &, register Transform &);
void FastInvert(const Hmx::Matrix3 &, Hmx::Matrix3 &);
void Invert(const Hmx::Matrix3 &, Hmx::Matrix3 &);

#endif
