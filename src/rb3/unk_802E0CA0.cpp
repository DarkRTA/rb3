#include "hmx/matrix3.hpp"
#include "vector3.hpp"
#include "vector_ops.hpp"

Vector3* Vector3::operator+=(const Vector3& v){
    x += v.x;
    y += v.y;
    z += v.z;
}

Vector3* Vector3::operator-=(const Vector3& v){
    x -= v.x;
    y -= v.y;
    z -= v.z;
}

// fn_802E2D8C
void Normalize(const Hmx::Matrix3& src, Hmx::Matrix3& dst){
    Normalize(src.row2, dst.row2);
    Cross(dst.row2, src.row3, dst.row1);
    Normalize(dst.row1, dst.row1);
    Cross(dst.row1, dst.row2, dst.row3);
}

// fn_802E2E28 - initializes sine table - https://decomp.me/scratch/Se53p - 

extern float gBigSinTable[];

// fn_802E2FE8
float FastSin(float f){
    if(f < 0.0f){
        return -gBigSinTable[((int)(-40.743664f * f + 0.49998999f) & 0xFF) * 2];
    }
    else return gBigSinTable[((int)(40.743664f * f + 0.49998999f) & 0xFF) * 2];
}