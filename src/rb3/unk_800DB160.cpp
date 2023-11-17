#include "data.hpp"
#include "common.hpp"
#include "std/math.h"
#include "vector3.hpp"
#include "triangle.hpp"
#include "hmx/matrix3.hpp"

// fn_800E25EC
float Ceil(double d)
{
	return ceil(d);
}

#pragma dont_inline on
// fn_800E25E8
float CeilThunk(double d)
{
	return Ceil(d);
}
#pragma dont_inline reset

// fn_800DC764
float Floor(double d)
{
	return floor(d);
}

#pragma dont_inline on
// fn_800DC760
float FloorThunk(double d)
{
	return Floor(d);
}
#pragma dont_inline reset

// fn_800DC1B0
int Round(float f)
{
	if (f > (float)0.0) {
		return (int)((float)0.5 + f);
	} else {
		return (int)(f - (float)0.5);
	}
}

// fn_800E2610
float Clamp(float f1, float f2, float f3){
	if(f3 > f2) return f2;
    if(!(f3 < f1)) return f3;
    return f1;
}

// fn_800E6BE4
float FMod(float f1, float f2){
	return fmod(f1, f2);
}

// fn_800DED98
float Interp(float f1, float f2, float f3){
	return (f3 * (f2 - f1)) + f1;
}

// fn_800E1E08
float SinFloat(double d){
	return sin(d);
}

#pragma dont_inline on
// fn_800E1E04
float SinThunk(double d){
	return SinFloat(d);
}
#pragma dont_inline reset

void Interp(const Vector3& v1, const Vector3& v2, float f, Vector3& dst){
	if(f == 0.0f){
		dst = v1;
	}
	else if(f == 1.0f){
		dst = v2;
	}
    else {
        dst.Set(Interp(v1.x, v2.x, f), Interp(v1.y, v2.y, f), Interp(v1.z, v2.z, f));
    }
}

void Subtract(const Vector3& v1, const Vector3& v2, Vector3& dst){
	dst.Set(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

void Negate(const Vector3& v1, Vector3& dst){
	dst.Set(-v1.x, -v1.y, -v1.z);
}

float Dot(const Vector3& v1, const Vector3& v2){
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

void Cross(const Vector3& v1, const Vector3& v2, Vector3& dst){
	dst.Set(v1.y * v2.z - v1.z * v2.y,
			v1.z * v2.x - v1.x * v2.z,
			v1.x * v2.y - v1.y * v2.x);
}

// fn_800DEDA4
void Triangle::Set(const Vector3& v1, const Vector3& v2, const Vector3& v3) {
    vec1 = v1;
    Subtract(v2, v1, vec2);
    Subtract(v3, v1, vec3);
    Cross(vec2, vec3, vec4);
}

// fn_800DEBE0
void Scale(const Vector3& v1, float f, Vector3& dst){
	dst.Set(v1.x * f, v1.y * f, v1.z * f);
}

void Scale(const Vector3& v, const Hmx::Matrix3& mtx, Hmx::Matrix3& dst){
	Scale(mtx.row1, v.x, dst.row1);
	Scale(mtx.row2, v.y, dst.row2);
	Scale(mtx.row3, v.z, dst.row3);
}