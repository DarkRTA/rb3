/*
    Compile unit: C:\rockband2\system\src\math\Key.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x806324C4 -> 0x8063318C
*/
// Range: 0x806324C4 -> 0x8063263C
void InterpTangent() {
    // Local variables
    class Vector3 v; // r1+0x10
    float r2; // f0
}

// Range: 0x8063263C -> 0x80632C5C
void InterpVector(const class Keys & vectorKeys /* r21 */, unsigned char spline /* r22 */, float frame /* f29 */, class Vector3 & r /* r23 */, class Vector3 * tangent /* r24 */) {
    // Local variables
    float t; // f31
    float t2; // f30
    float t3; // f29
    class Vector3 ta; // r1+0x30
    class Vector3 tb; // r1+0x20
    const class Vector3 * a; // r26
    const class Vector3 * b; // r25
    int i; // r27
    class Vector3 v; // r1+0x10
}

// Range: 0x80632C5C -> 0x8063318C
void QuatSpline(const class Keys & quatKeys /* r26 */, float frame /* f29 */, class Quat & ret /* r27 */) {
    // Local variables
    int before; // r29
    int after; // r28
    float f; // f0
    int between; // r25
    float t; // f31
    float t2; // f30
    float t3; // f29
    class Quat q[4]; // r1+0x10
    int i; // r7
}


