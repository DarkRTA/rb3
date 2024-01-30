#ifndef RB3_ROT_HPP
#define RB3_ROT_HPP
#include "hmx/quat.hpp"
#include "hmx/matrix3.hpp"
#include "vector3.hpp"

// TODO: add function prototypes
void Normalize(const register Hmx::Quat&, register Hmx::Quat&);
void MakeEuler(const Hmx::Matrix3&, Vector3&);
void MakeVertical(Hmx::Matrix3&);
void MakeScale(const Hmx::Matrix3&, Vector3&);
void MakeEulerScale(const Hmx::Matrix3&, Vector3&, Vector3&);
float GetXAngle(const Hmx::Matrix3&);
float GetYAngle(const Hmx::Matrix3&);
float GetZAngle(const Hmx::Matrix3&);

#endif
