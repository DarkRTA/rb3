/*
    Compile unit: C:\rockband2\system\src\synth\MicNull.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8057EB80 -> 0x8057ECC8
*/
class MicNull : public Mic {
    // total size: 0x4E60
    signed short mBuf[10000]; // offset 0x4, size 0x4E20
    class Timer mTimer; // offset 0x4E28, size 0x38
};
// Range: 0x8057EB80 -> 0x8057EBD0
void * MicNull::MicNull(class MicNull * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__7MicNull;
}

// Range: 0x8057EBD0 -> 0x8057ECC8
signed short * MicNull::GetBuf(class MicNull * const this /* r29 */, int & samples /* r30 */) {
    // Local variables
    int i; // r31
}

struct {
    // total size: 0x7C
} __vt__7MicNull; // size: 0x7C, address: 0x8091D8A0
struct {
    // total size: 0x8
} __RTTI__7MicNull; // size: 0x8, address: 0x8091D938

