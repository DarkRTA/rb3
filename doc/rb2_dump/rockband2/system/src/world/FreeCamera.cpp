/*
    Compile unit: C:\rockband2\system\src\world\FreeCamera.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x804295BC -> 0x80429FF8
*/
// Range: 0x804295BC -> 0x804295FC
void * FreeCamera::FreeCamera() {
    // References
    // -> struct [anonymous] __vt__10FreeCamera;
}

// Range: 0x804295FC -> 0x8042963C
void * FreeCamera::~FreeCamera(class FreeCamera * const this /* r31 */) {}

// Range: 0x8042963C -> 0x8042973C
void FreeCamera::UpdateFromCamera(class FreeCamera * const this /* r30 */) {
    // References
    // -> class WorldDir * TheWorld;
}

// Range: 0x8042973C -> 0x8042978C
void FreeCamera::SetActive(class FreeCamera * const this /* r30 */, unsigned char active /* r31 */) {}

// Range: 0x8042978C -> 0x80429794
unsigned char FreeCamera::IsActive() {}

// Range: 0x80429794 -> 0x80429800
void FreeCamera::AdvanceState(class FreeCamera * const this /* r31 */) {}

// Range: 0x80429800 -> 0x80429820
void FreeCamera::NextState() {}

// Range: 0x80429820 -> 0x80429864
void FreeCamera::SetFrozen(class FreeCamera * const this /* r30 */, unsigned char frozen /* r31 */) {}

// Range: 0x80429864 -> 0x80429874
void FreeCamera::SetParentDof() {}

// Range: 0x80429874 -> 0x80429FF8
void FreeCamera::Poll(class FreeCamera * const this /* r30 */) {
    // Local variables
    class JoypadData * data; // r0
    float dt; // f31
    float left0; // f2
    float left1; // f3
    float rotateRate; // f4
    float left0rate; // f2
    float left1rate; // f28
    float slewRate; // f2
    float r0; // f3
    float r1; // f4
    float r0rate; // f5
    float r1rate; // f6
    class Transform t; // r1+0x110
    class Matrix3 rotMatrix; // r1+0xE0
    class Vector3 angles; // r1+0x20
    class Matrix3 multMatrix; // r1+0xB0
    class Transform tempT; // r1+0x70
    class Transform worldToParent; // r1+0x30

    // References
    // -> class WorldDir * TheWorld;
    // -> class TaskMgr TheTaskMgr;
}

struct {
    // total size: 0xC
} __vt__10FreeCamera; // size: 0xC, address: 0x808EC7A0
struct {
    // total size: 0x8
} __RTTI__10FreeCamera; // size: 0x8, address: 0x808EC7B8

