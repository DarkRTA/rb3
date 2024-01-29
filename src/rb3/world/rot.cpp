#include "rot.hpp"

#include "common.hpp"
#include "math.h"
#include "hmx/matrix3.hpp"
#include "vector3.hpp"
#include "vector_ops.hpp"
#include "trigtable.hpp"
#include "hmx/quat.hpp"
#include "textstream.hpp"
#include "vector2.hpp"
#include "transform.hpp"
#include "binstream.hpp"
#include "shortquat.hpp"
#include "shorttransform.hpp"


// fn_802DE5B4
float ASinFloat(double d) {
    return asin(d);
}


// fn_802DEEF8
float ACosFloat(double d) {
    return acos(d);
}

// fn_802DE7D8
float GetXAngle(const Hmx::Matrix3 &mtx) {
    return my_atan2f(mtx.row2.z, mtx.row2.y);
}

// fn_802DE7E4
float GetYAngle(const Hmx::Matrix3 &mtx) {
    return my_atan2f(-mtx.row1.z, mtx.row3.z);
}

// fn_802DE7F4
float GetZAngle(const Hmx::Matrix3 &mtx) {
    return -my_atan2f(mtx.row2.x, mtx.row2.y);
}

void MakeVertical(Hmx::Matrix3 &mtx) {
    mtx.row3.Set(0.0f, 0.0f, 1.0f);
    mtx.row2.z = 0.0f;
    Normalize(mtx.row2, mtx.row2);
    Cross(mtx.row2, mtx.row3, mtx.row1);
}

void MakeEuler(const Hmx::Matrix3 &mtx, Vector3 &vec) {
    if (AbsThunk(mtx.row2.z) > 0.99999988f) {
        if (mtx.row2.z > 0.0f)
            vec.x = 1.5707964f;
        else
            vec.x = -1.5707964f;
        vec.z = ATan2Thunk(mtx.row1.y, mtx.row1.x);
        vec.y = 0.0f;
    } else {
        vec.z = ATan2Thunk(-mtx.row2.x, mtx.row2.y);
        vec.x = ASinFloat(mtx.row2.z);
        vec.y = ATan2Thunk(-mtx.row1.z, mtx.row3.z);
    }
}

void MakeScale(const Hmx::Matrix3 &mtx, Vector3 &vec) {
    Vector3 bruh;
    float f1 = Length(mtx.row3);
    Cross(mtx.row1, mtx.row2, bruh);
    float f2 = Dot(bruh, mtx.row3);
    f1 = (f2 > 0.0f) ? f1 : -f1;
    f2 = Length(mtx.row2);
    float f3 = Length(mtx.row1);
    vec.Set(f3, f2, f1);
}

void MakeRotMatrix(const Hmx::Quat &q, Hmx::Matrix3 &mtx) {
    float f9 = 1.0f;
    float f1 = q.y;
    float f2 = q.z;
    float f3 = q.w;
    float f4 = q.x * 2.0f;
    float f5 = 2.0f * f1;
    float f6 = 2.0f * f2 * f2;
    float f7 = 2.0f * f2 * f3;
    float f8 = q.x * f4;

    mtx.row1.x = (1.0f - f5 * f1) - f6;
    mtx.row1.y = f4 * f1 + f7;
    mtx.row1.z = f4 * f2 - f5 * f3;
    mtx.row2.x = f4 * f1 - f7;
    mtx.row2.y = f9 - f6 - f8;
    mtx.row2.z = f5 * f2 + f4 * f3;
    mtx.row3.x = f4 * f2 + f5 * f3;
    mtx.row3.y = f5 * f2 - f4 * f3;
    mtx.row3.z = f9 - f8 - (f5 * f1);
}

extern void NOP(Hmx::Matrix3 *);

void MakeEulerScale(const Hmx::Matrix3 &mtx, Vector3 &v1, Vector3 &v2) {
    Hmx::Matrix3 lol;
    MakeScale(mtx, v2);
    NOP(&lol);
    if (v2.x != 0.0f) {
        Scale(mtx.row1, 1.0f / v2.x, lol.row1);
    }
    if (v2.y != 0.0f) {
        Scale(mtx.row2, 1.0f / v2.y, lol.row2);
    }
    if (v2.z != 0.0f) {
        Scale(mtx.row3, 1.0f / v2.z, lol.row3);
    }
    MakeEuler(lol, v1);
}

void MakeEuler(const Hmx::Quat &q, Vector3 &vec) {
    Hmx::Matrix3 lmao;
    NOP(&lmao);
    MakeRotMatrix(q, lmao);
    MakeEuler(lmao, vec);
}


// fn_802DE4D4
float Cosine(float f) {
    return Sine(f + 1.5707964f);
}


void MakeRotMatrix(const Vector3 &v1, const Vector3 &v2, Hmx::Matrix3 &mtx) {
    mtx.row2 = v1;
    Normalize(mtx.row2, mtx.row2);
    Cross(mtx.row2, v2, mtx.row1);
    Normalize(mtx.row1, mtx.row1);
    Cross(mtx.row1, mtx.row2, mtx.row3);
}

TextStream &operator<<(TextStream &ts, const Hmx::Quat &q) {
    ts << "(x:" << q.x << " y:" << q.y << " z:" << q.z << " w:" << q.w << ")";
    return ts;
}

TextStream &operator<<(TextStream &ts, const Vector3 &vec) {
    ts << "(x:" << vec.x << " y:" << vec.y << " z:" << vec.z << ")";
    return ts;
}

TextStream &operator<<(TextStream &ts, const Vector2 &vec) {
    ts << "(x:" << vec.x << " y:" << vec.y << ")";
    return ts;
}

TextStream &operator<<(TextStream &ts, const Hmx::Matrix3 &mtx) {
    ts << "\n\t" << mtx.row1 << "\n\t" << mtx.row2 << "\n\t" << mtx.row3;
    return ts;
}

TextStream &operator<<(TextStream &ts, const Transform &tf) {
    ts << tf.rot << "\n\t" << tf.trans;
    return ts;
}

void FastInvert(const Hmx::Matrix3 &mtx, Hmx::Matrix3 &dst) {
    float d1 = 1.0f / Dot(mtx.row1, mtx.row1);
    float d2 = 1.0f / Dot(mtx.row2, mtx.row2);
    float d3 = 1.0f / Dot(mtx.row3, mtx.row3);
    dst.Set(
        mtx.row1.x * d1,
        mtx.row2.x * d2,
        mtx.row3.x * d3,
        mtx.row1.y * d1,
        mtx.row2.y * d2,
        mtx.row3.y * d3,
        mtx.row1.z * d1,
        mtx.row2.z * d2,
        mtx.row3.z * d3
    );
}

BinStream &operator<<(BinStream &bs, const Vector3 &vec) {
    bs << vec.x << vec.y << vec.z;
    return bs;
}

void ShortQuat::Set(const Hmx::Quat &q) {
    x = FloorThunk(Clamp(-32767.0f, 32767.0f, 32767.0f * q.x + 0.5f));
    y = FloorThunk(Clamp(-32767.0f, 32767.0f, 32767.0f * q.y + 0.5f));
    z = FloorThunk(Clamp(-32767.0f, 32767.0f, 32767.0f * q.z + 0.5f));
    w = FloorThunk(Clamp(-32767.0f, 32767.0f, 32767.0f * q.w + 0.5f));
}

void ShortQuat::operator=(const ShortQuat &q) {
    x = q.x;
    y = q.y;
    z = q.z;
    w = q.w;
}

bool Vector3::operator==(const Vector3 &vec) const {
    bool b = false;
    if (x == vec.x && y == vec.y && z == vec.z)
        b = true;
    return b;
}

bool Vector3::operator!=(const Vector3 &vec) const {
    bool b = false;
    if (x != vec.x || y != vec.y || z != vec.z)
        b = true;
    return b;
}

void ShortQuat::ToQuat(Hmx::Quat &q) const {
    q.Set(
        (float)(x * 0.000030518509f),
        (float)(y * 0.000030518509f),
        (float)(z * 0.000030518509f),
        (float)(w * 0.000030518509f)
    );
}

void Normalize(const register Hmx::Quat &quat, register Hmx::Quat &dst) {
    using Hmx::Quat;

    register float quatXY;
    register float quatZW;

    register float quatXYsq;
    register float quatZWsq;

    register float magnitude;
    register float magHalf;
    register float magSquare;
    register float magNewton;

    register float squares;
    register float cutoff = 0.00001f;
    register float zero;
    register float half = 0.5f;
    register float three = 3.0f;

    register float factor;

    ASM_BLOCK(
        // quat.x * quat.x + quat.y * quat.y + quat.z * quat.z + quat.w * quat.w;
        psq_l    quatXY, 0(r3), 0, 0
        psq_l    quatZW, 8(r3), 0, 0
        ps_mul   quatXYsq, quatXY, quatXY
        ps_mul   quatZWsq, quatZW, quatZW
        ps_sum0  squares, quatXYsq, quatZWsq, quatXYsq
        ps_sum1  quatZWsq, quatZWsq, quatXYsq, quatZWsq
        ps_sum0  squares, squares, quatXYsq, quatZWsq

        // 1 / sqrt(squares)
        frsqrte  magnitude, squares

        // Newton's method
        // -(magnitude * magnitude * squares - 3.0f) * magnitude * 0.5f;
        // Tried to make this match as C code, couldn't get it to work correctly
        fmul     magSquare, magnitude, magnitude
        fmul     magHalf, magnitude, half
        fnmsub   magNewton, magSquare, squares, three
        fmul     magnitude, magNewton, magHalf

        // if (squares - 0.00001f <= 0.0f) magnitude = 0.0f;
        ps_sub   zero, cutoff, cutoff
        ps_sub   cutoff, squares, cutoff
        ps_sel   magnitude, cutoff, magnitude, zero

        // dst.x = quat.x * magnitude;
        // dst.y = quat.y * magnitude;
        // dst.z = quat.z * magnitude;
        // dst.w = quat.w * magnitude;
        ps_muls0 quatXY, quatXY, magnitude
        ps_muls0 quatZW, quatZW, magnitude
        psq_st   quatXY, Quat.x(dst), 0, 0
        psq_st   quatZW, Quat.z(dst), 0, 0
    )
}

void IdentityInterp(const Hmx::Quat &q, float f, Hmx::Quat &dst) {
    if (f == 0.0f) {
        dst = q;
    } else if (f == 1.0f) {
        dst.Set(0.0f, 0.0f, 0.0f, 1.0f);
    } else {
        float f2 = 1.0f - f;
        dst.x = q.x * f2;
        dst.y = q.y * f2;
        dst.z = q.z * f2;
        float f1 = q.w;
        if (f1 < 0.0f) {
            dst.w = f1 * f2 - f;
        } else
            dst.w = f1 * f2 + f;
        Normalize(dst, dst);
    }
}


BinStream &operator>>(BinStream &bs, Vector3 &vec) {
    bs >> vec.x >> vec.y >> vec.z;
    return bs;
}


BinStream &operator>>(BinStream &bs, Hmx::Matrix3 &mtx) {
    bs >> mtx.row1 >> mtx.row2 >> mtx.row3;
    return bs;
}

void Hmx::Quat::Set(const Vector3 &vec, float f) {
    float mult = 0.5f * f;
    float f1 = Sine(mult);
    float f2 = Cosine(mult);
    w = f2;
    x = vec.x * f1;
    y = vec.y * f1;
    z = vec.z * f1;
}

void Hmx::Quat::Set(const Vector3 &vec) {
    Vector3 stack;
    Scale(vec, 0.5f, stack);
    float f1 = Sine(stack.x);
    float f2 = Cosine(stack.x);
    float f3 = Sine(stack.y);
    float f4 = Cosine(stack.y);
    Set(f1 * f4, f2 * f3, f1 * f3, f2 * f4);
    f1 = Sine(stack.z);
    f2 = Cosine(stack.z);
    Set(f2 * x - f1 * y, f2 * y + f1 * x, f2 * z + f1 * w, f2 * w - f1 * z);
}

void Multiply(
    const register Transform &t1, const register Transform &t2, register Transform &dst
) {
    register float row1XY;
    register float row1Z;
    register float row2XY;
    register float row2Z;
    register float row3XY;
    register float row3Z;
    register float transXY;
    register float transZ;

    ASM_BLOCK(
        // Load t1
        psq_l       row1XY,  Transform.rot.row1.x(t1), 0, 0
        psq_l       row1Z,   Transform.rot.row1.z(t1), 1, 0
        psq_l       row2XY,  Transform.rot.row2.x(t1), 0, 0
        psq_l       row2Z,   Transform.rot.row2.z(t1), 1, 0
        psq_l       row3XY,  Transform.rot.row3.x(t1), 0, 0
        psq_l       row3Z,   Transform.rot.row3.z(t1), 1, 0
        psq_l       transXY, Transform.trans.x(t1), 0, 0
        psq_l       transZ,  Transform.trans.z(t1), 1, 0

        // Merge X components together
        ps_merge00  f0, row1XY, row2XY
        ps_merge00  f1, row3XY, transXY

        // Merge Y components together
        ps_merge11  f2, row1XY, row2XY
        ps_merge11  f3, row3XY, transXY

        // Merge Z components together
        ps_merge00  f4, row1Z,  row2Z
        ps_merge00  f5, row3Z,  transZ

        ps_sub      f10, f10, f10
        ps_merge01  f26, f10, transZ

        // Load t2
        psq_l       row1XY,  Transform.rot.row1.x(t2), 0, 0
        psq_l       row1Z,   Transform.rot.row1.z(t2), 1, 0
        psq_l       row2XY,  Transform.rot.row2.x(t2), 0, 0
        psq_l       row2Z,   Transform.rot.row2.z(t2), 1, 0
        psq_l       row3XY,  Transform.rot.row3.x(t2), 0, 0
        psq_l       transXY, Transform.trans.x(t2), 0, 0 // Must be swapped in order to match
        psq_l       row3Z,   Transform.rot.row3.z(t2), 1, 0
        psq_l       transZ,  Transform.trans.z(t2), 1, 0

        // After this point it becomes pretty entangled, done my best to comment what I can

        ps_merge00  f6, row1XY, row2XY // f6 = (t2.row1.x, t2.row2.x)
        ps_muls0    f10, f1, f6        // f10 = (t1.row3.x * t2.row)
        ps_madds1   f10, f3, f6, f10

        // row1XY = (t2.row1.y, t2.row2.y)
        ps_merge11  row1XY, row1XY, row2XY
        ps_muls0    f12, f1, row1XY
        ps_madds1   f12, f3, row1XY, f12

        // row1XY = (t2.row1.z, t2.row2.z)
        ps_merge00  row1Z, row1Z, row2Z

        ps_muls0    row2Z, f0, row1XY

        ps_muls0    f31, f1, row1Z
        ps_muls0    f13, f0, row1Z

        ps_muls0    row2XY,  f0, f6

        // f0 = (row3.x, trans.x)
        ps_merge00  f0, row3XY, transXY
        ps_madds1   row2XY, f2, f6, row2XY
        ps_madds0   row2XY, f4, f0, row2XY

        ps_madds0   f10, f5, f0, f10
        ps_madd     f10, f26, f0, f10

        // f1 = (row3.y, trans.y)
        ps_merge11  f1, row3XY, transXY
        ps_madds1   row2Z, f2, row1XY, row2Z
        ps_madds0   row2Z, f4, f1, row2Z

        ps_madds0   f12, f5, f1, f12
        ps_madd     f12, f26, f1, f12

        // f6 = (row3.z, trans.z)
        ps_merge00  f6, row3Z, transZ
        ps_madds1   f31, f3, row1Z, f31
        ps_madds0   f31, f5, f6, f31
        ps_madd     f31, f26, f6, f31

        ps_madds1   f13, f2, row1Z, f13
        ps_madds0   f13, f4, f6, f13

        ps_merge00  row1XY, row2XY, row2Z
        ps_merge11  row2XY, row2XY, row2Z
        ps_merge11  row2Z, f13, f13
        ps_merge11  transZ, f31, f31
        ps_merge00  row3XY, f10, f12
        ps_merge11  transXY, f10, f12

        // Store result
        psq_st      row1XY, Transform.rot.row1.x(dst), 0, 0
        psq_st      f13, Transform.rot.row1.z(dst), 1, 0
        psq_st      row2XY, Transform.rot.row2.x(dst), 0, 0
        psq_st      row2Z, Transform.rot.row2.z(dst), 1, 0
        psq_st      row3XY, Transform.rot.row3.x(dst), 0, 0
        psq_st      f31, Transform.rot.row3.z(dst), 1, 0
        psq_st      transXY, Transform.trans.x(dst), 0, 0
        psq_st      transZ, Transform.trans.z(dst), 1, 0
    )
}


Hmx::Quat::Quat(const Hmx::Matrix3 &mtx) {
    Set(mtx);
}


void Hmx::Quat::Set(const Hmx::Matrix3 &mtx) {
    float f1 = mtx.row1.x;
    float f2 = mtx.row2.y;
    float f3 = mtx.row3.z;
    float diag = f1 + f2 + f3;
    if (diag > 0.0f) {
        w = diag + 1.0f;
        x = mtx.row2.z - mtx.row3.y;
        y = mtx.row3.x - mtx.row1.z;
        z = mtx.row1.y - mtx.row2.x;
    } else if ((f3 > f1) && (f3 > f2)) {
        z = f3 - f1 - f2 + 1.0f;
        w = mtx.row1.y - mtx.row2.x;
        x = mtx.row3.x + mtx.row1.z;
        y = mtx.row3.y + mtx.row2.z;
    } else if (f2 > f1) {
        y = f2 - f3 - f1 + 1.0f;
        w = mtx.row3.x - mtx.row1.z;
        z = mtx.row2.z + mtx.row3.y;
        x = mtx.row2.x + mtx.row1.y;
    } else {
        x = f1 - f2 - f3 + 1.0f;
        w = mtx.row2.z - mtx.row3.y;
        y = mtx.row1.y + mtx.row2.x;
        z = mtx.row1.z + mtx.row3.x;
    }
    Normalize(*this, *this);
}


void ShortQuat::Set(const Hmx::Matrix3 &mtx) {
    Set(Hmx::Quat(mtx));
}


void Invert(const Hmx::Matrix3 &mtx, Hmx::Matrix3 &dst) {
    float big_num = mtx.row1.z * mtx.row2.x * mtx.row3.y - mtx.row3.x * mtx.row2.y
        + mtx.row1.x * mtx.row2.y * mtx.row3.z - mtx.row3.y * mtx.row2.z
        - mtx.row1.y * mtx.row2.x * mtx.row3.z - mtx.row3.x * mtx.row2.z;
    float f10 = 0.0f;
    if (big_num != 0.0f)
        f10 = 1.0f / big_num;

    float f1 = mtx.row1.x;
    float f2 = mtx.row1.y;
    float f3 = mtx.row1.z;
    float f4 = mtx.row2.x;
    float f5 = mtx.row2.y;
    float f6 = mtx.row2.z;
    float f7 = mtx.row3.x;
    float f8 = mtx.row3.y;
    float f9 = mtx.row3.z;
    dst.Set(
        f10 * (f5 * f9 - f6 * f8),
        f10 * -(f2 * f9 - f8 * f3),
        f10 * (f2 * f6 - f5 * f3),
        f10 * -(f4 * f9 - f6 * f7),
        f10 * (f1 * f9 - f7 * f3),
        f10 * -(f1 * f6 - f4 * f3),
        f10 * (f4 * f8 - f7 * f5),
        f10 * -(f1 * f8 - f7 * f2),
        dst.row1.x
    );
}

void MakeRotQuat(const Vector3 &v1, const Vector3 &v2, Hmx::Quat &dst) {
    Vector3 vec;
    Cross(v1, v2, vec);
    float len2 = LengthSquared(v2);
    float len1 = LengthSquared(v1);
    float sq = SqrtThunk(len1 * len2);
    float dot = Dot(v1, v2);
    float sq2 = SqrtThunk(0.5f + ((0.5f * dot) / sq));
    if (sq2 > 1.0E-7f) {
        float f1 = 0.5f / (sq * sq2);
        dst.x = vec.x * f1;
        dst.y = vec.y * f1;
        dst.z = vec.z * f1;
        dst.w = sq2;
    } else {
        dst.Set(0.0f, 0.0f, 1.0f, 0.0f);
    }
}

void MakeRotQuatUnitX(const Vector3 &vec, Hmx::Quat &dst) {
    float sq = SqrtThunk(0.5f * vec.x + 0.5f);
    if (sq > 1.0E-7f) {
        dst.Set(0.0f, vec.z * (0.5f / sq), -vec.y * (0.5f / sq), sq);
    } else {
        dst.Set(0.0f, 0.0f, 1.0f, 0.0f);
    }
}

float operator*(const Hmx::Quat &q1, const Hmx::Quat &q2) {
    return q1.x * q2.x + q1.y * q2.y + q1.z * q2.z + q1.w * q2.w;
}

void Interp(const Hmx::Quat &q1, const Hmx::Quat &q2, float f, Hmx::Quat &dst) {
    if (f == 0.0f)
        dst = q1;
    else if (f == 1.0f)
        dst = q2;
    else {
        if ((q1 * q2) < 0.0f) {
            dst.x = -(f * (q1.x + q2.x) - q1.x);
            dst.y = -(f * (q1.y + q2.y) - q1.y);
            dst.z = -(f * (q1.z + q2.z) - q1.z);
            dst.w = -(f * (q1.w + q2.w) - q1.w);
        } else {
            dst.x = -(f * (q1.x - q2.x) - q1.x);
            dst.y = -(f * (q1.y - q2.y) - q1.y);
            dst.z = -(f * (q1.z - q2.z) - q1.z);
            dst.w = -(f * (q1.w - q2.w) - q1.w);
        }
        Normalize(dst, dst);
    }
}


void InterpThunk(const Hmx::Quat &q1, const Hmx::Quat &q2, float f, Hmx::Quat &dst) {
    Interp(q1, q2, f, dst);
}


void Interp(const Hmx::Matrix3 &m1, const Hmx::Matrix3 &m2, float f, Hmx::Matrix3 &dst) {
    Hmx::Quat q1(m1);
    Hmx::Quat q2(m2);
    Hmx::Quat q;
    InterpThunk(q1, q2, f, q);
    MakeRotMatrix(q, dst);
}

void FastInterp(const Hmx::Quat &q1, const Hmx::Quat &q2, float f, Hmx::Quat &dst) {
    if (f == 0.0f)
        dst = q1;
    else if (f == 1.0f)
        dst = q2;
    else {
        if ((q1 * q2) < 0.0f) {
            float q1x = q1.x;
            dst.x = -(f * (q2.x + q1x) - q1x);
            float q1y = q1.y;
            dst.y = -(f * (q2.y + q1y) - q1y);
            float q1z = q1.z;
            dst.z = -(f * (q2.z + q1z) - q1z);
            float q1w = q1.w;
            dst.w = -(f * (q2.w + q1w) - q1w);
        } else {
            float q1x = q1.x;
            dst.x = (f * (q2.x - q1x) + q1x);
            float q1y = q1.y;
            dst.y = (f * (q2.y - q1y) + q1y);
            float q1z = q1.z;
            dst.z = (f * (q2.z - q1z) + q1z);
            float q1w = q1.w;
            dst.w = (f * (q2.w - q1w) + q1w);
        }
        Normalize(dst, dst);
    }
}

// fn_802DE1D8
ShortTransform::ShortTransform() {
    rot.z = 0;
    rot.y = 0;
    rot.x = 0;
    rot.w = 0x7FFF;
    trans.z = 0.0f;
    trans.y = 0.0f;
    trans.x = 0.0f;
}

// fn_802DE0D0
void ShortTransform::operator=(const ShortTransform &st) {
    rot = st.rot;
    trans = st.trans;
}

// fn_802DDF9C
void ShortTransform::operator=(const Transform &tf) {
    rot.Set(tf.rot);
    trans = tf.trans;
}


Hmx::Quat::Quat(const Vector3 &vec, float f) {
    Set(vec, f);
}

void ShortQuat::SetThunk(const Hmx::Quat &q) {
    Set(q);
}
