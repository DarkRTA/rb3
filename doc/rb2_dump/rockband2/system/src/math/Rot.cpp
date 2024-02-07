/*
    Compile unit: C:\rockband2\system\src\math\Rot.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8062DDEC -> 0x8062F730
*/
// Range: 0x8062DDEC -> 0x8062DE48
void Normalize() {
    // Local variables
    float xy; // f0
    float zw; // f1
    float xy_sqr; // f2
    float zw_sqr; // f3
    float sum_0; // f4
    float sum_1; // f3
    float rsqrt; // f2
    float nwork0; // f3
    float nwork1; // f2
    float diff; // f5
    float c_zero; // f3
    float epsilon; // f6
    float c_half; // f7
    float c_three; // f8
}

// Range: 0x8062DE48 -> 0x8062DEE4
void Quat::Set(class Quat * const this /* r30 */, const class Vector3 & axis /* r31 */) {
    // Local variables
    float h; // f30
    float s; // f0
}

// Range: 0x8062DEE4 -> 0x8062DFB0
void MakeEuler(const class Matrix3 & m /* r30 */, class Vector3 & r /* r31 */) {}

// Range: 0x8062DFB0 -> 0x8062E07C
void MakeVertical() {}

// Range: 0x8062E07C -> 0x8062E1D8
void MakeScale() {
    // Local variables
    float z; // f0
    class Vector3 v; // r1+0x10
}

// Range: 0x8062E1D8 -> 0x8062E2F0
void MakeEulerScale(const class Matrix3 & m /* r29 */, class Vector3 & r /* r30 */, class Vector3 & s /* r31 */) {
    // Local variables
    class Matrix3 m2; // r1+0x10
}

// Range: 0x8062E2F0 -> 0x8062E31C
float GetXAngle() {}

// Range: 0x8062E31C -> 0x8062E34C
float GetYAngle() {}

// Range: 0x8062E34C -> 0x8062E37C
float GetZAngle() {}

// Range: 0x8062E37C -> 0x8062E4D0
void Quat::Set(class Quat * const this /* r31 */) {
    // Local variables
    class Vector3 e; // r1+0x10
    float x1; // f0
    float w1; // f0
    float y2; // f0
    float w2; // f0
    float z1; // f0
}

// Range: 0x8062E4D0 -> 0x8062E6BC
void Quat::Set() {
    // Local variables
    float tr; // f3
    float s; // f2
    int nxt[3]; // r1+0x8
    int i; // r10
    int j; // r11
    int k; // r12
    float s; // f6
}

// Range: 0x8062E6BC -> 0x8062E7C8
void FastInterp() {
    // Local variables
    float cosom; // f0
}

// Range: 0x8062E7C8 -> 0x8062E86C
void IdentityInterp() {
    // Local variables
    float t1; // f3
}

// Range: 0x8062E86C -> 0x8062E978
void Interp() {}

// Range: 0x8062E978 -> 0x8062EA04
void Interp(const class Matrix3 & from /* r0 */, const class Matrix3 & to /* r30 */, float t /* f31 */, class Matrix3 & res /* r31 */) {
    // Local variables
    class Quat a; // r1+0x30
    class Quat b; // r1+0x20
    class Quat c; // r1+0x10
}

// Range: 0x8062EA04 -> 0x8062EB94
void MakeRotMatrix(const class Vector3 & v /* r30 */, class Matrix3 & m /* r31 */) {
    // Local variables
    float cz; // f31
    float sz; // f30
    float cy; // f29
    float sy; // f28
    float cx; // f1
    float sx; // f27
    float syz; // f2
    float cyz; // f3
    float csyz; // f4
    float cszy; // f5
}

// Range: 0x8062EB94 -> 0x8062ED18
void MakeRotMatrix() {}

// Range: 0x8062ED18 -> 0x8062EDB8
void MakeRotMatrix() {
    // Local variables
    float p00; // f5
    float p01; // f6
    float p02; // f7
    float p03; // f8
    float p11; // f3
    float p12; // f9
    float p13; // f10
    float p22; // f2
    float p23; // f4
}

// Range: 0x8062EDB8 -> 0x8062EEA0
void RotateAboutX(const class Matrix3 & in /* r30 */, float rad /* f30 */, class Matrix3 & out /* r31 */) {
    // Local variables
    float cs; // f0
    float sn; // f0
}

// Range: 0x8062EEA0 -> 0x8062EF88
void RotateAboutZ(const class Matrix3 & in /* r30 */, float rad /* f30 */, class Matrix3 & out /* r31 */) {
    // Local variables
    float cs; // f0
    float sn; // f0
}

// Range: 0x8062EF88 -> 0x8062EFD4
void MakeEuler(class Vector3 & euler /* r31 */) {
    // Local variables
    class Matrix3 mat; // r1+0x10
}

// Range: 0x8062EFD4 -> 0x8062F140
void MakeRotQuat() {
    // Local variables
    class Vector3 axis; // r1+0x10
    float l; // f0
    float cosHalfTheta; // f0
    float scale; // f2
}

// Range: 0x8062F140 -> 0x8062F1C8
void MakeRotQuatUnitX() {
    // Local variables
    float cosHalfTheta; // f0
    float scale; // f4
}

// Range: 0x8062F1C8 -> 0x8062F258
void Multiply(const class Vector3 & a /* r30 */, class Vector3 & b /* r31 */) {
    // Local variables
    class Matrix3 mat; // r1+0x10
}

// Range: 0x8062F258 -> 0x8062F2D8
class TextStream & __ls(class TextStream & d /* r30 */, const class Quat & a /* r31 */) {}

// Range: 0x8062F2D8 -> 0x8062F348
class TextStream & __ls(class TextStream & d /* r30 */, const class Vector3 & a /* r31 */) {}

// Range: 0x8062F348 -> 0x8062F3A8
class TextStream & __ls(class TextStream & d /* r30 */, const class Vector2 & a /* r31 */) {}

// Range: 0x8062F3A8 -> 0x8062F410
class TextStream & __ls(class TextStream & d /* r30 */, const class Matrix3 & a /* r31 */) {}

// Range: 0x8062F410 -> 0x8062F45C
class TextStream & __ls(class TextStream & d /* r30 */, const class Transform & a /* r31 */) {}

// Range: 0x8062F45C -> 0x8062F530
void Multiply() {
    // Local variables
    float b_m__xy; // f0
    float b_m__zw; // f1
    float a_m__; // f2
    float a_v__; // f2
    float c_m_x_xy; // f3
    float c_m_x_zw; // f4
    float c_m_y_xy; // f5
    float c_m_y_zw; // f6
    float c_m_z_xy; // f7
    float c_m_z_zw; // f8
    float c_v_xy; // f9
    float c_v_zw; // f10
}

// Range: 0x8062F530 -> 0x8062F5EC
void FastInvert() {
    // Local variables
    float x; // f13
    float y; // f31
    float z; // f1
}

// Range: 0x8062F5EC -> 0x8062F730
void Invert() {
    // Local variables
    float det; // f2
}


