#include "jsonobject.hpp"
#include "common.hpp"
#include "data.hpp"
#include "std/math.h"
#include "vector3.hpp"
#include "matrix3.hpp"

// fn_800CF370
int Minimum(int x, int y)
{
	return (y < x) ? y : x;
}

// fn_800D7964
float DataArray::GetFloatAtIndex(int i) const
{
	DataNode *dn = GetNodeAtIndex(i);
	return dn->Float(this);
}

// fn_800D81D4
double FAbs(double d)
{
	return __fabs(d);
}

#pragma dont_inline on
// fn_800D81B0
float FAbsFloat(double d)
{
	return FAbs(d);
}

// fn_800D81AC
float AbsThunk(double d)
{
	return FAbsFloat(d);
}

#pragma dont_inline reset

// fn_800D4728
int Clamp(int i1, int i2, int i3){
	if(i3 > i2) return i2;
    if(!(i3 < i1)) return i3;
    return i1;
}

#pragma dont_inline on
// fn_800CB1A4
void Vector3::Set(float f1, float f2, float f3){
	x = f1;
	y = f2;
	z = f3;
}
#pragma dont_inline reset

// fn_800D8AC8
Vector3* Vector3::operator=(const Vector3& vec){
	x = vec.x;
	y = vec.y;
	z = vec.z;
	return this;
}

void Scale(const Vector3& v1, const Vector3& v2, Vector3& dst){
	dst.Set(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
}

void Vector3::Zero(){
	z = 0.0f; y = 0.0f; x = 0.0f;
}

// fn_800CBBA0
void Hmx::Matrix3::Identity(){
	row1.Set(1.0f, 0.0f, 0.0f);
    row2.Set(0.0f, 1.0f, 0.0f);
    row3.Set(0.0f, 0.0f, 1.0f);
}