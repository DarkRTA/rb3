/*
    Compile unit: C:\rockband2\system\src\synth\ByteGrinder.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8056A170 -> 0x8056C75C
*/
struct Symmetric_CTR {
    // total size: 0x310
    int cipher; // offset 0x0, size 0x4
    int blocklen; // offset 0x4, size 0x4
    int padlen; // offset 0x8, size 0x4
    unsigned char ctr[128]; // offset 0xC, size 0x80
    unsigned char pad[128]; // offset 0x8C, size 0x80
    union Symmetric_key key; // offset 0x10C, size 0x204
};
static unsigned long hashMapping[256]; // size: 0x400, address: 0x80982FB0
// Range: 0x8056A170 -> 0x8056A240
class DataNode hashTo5Bits(class DataArray * msg /* r31 */) {
    // Local variables
    unsigned long ret; // r3
    unsigned long seed; // r3
    int i; // r6

    // References
    // -> static unsigned long hashMapping[256];
}

static unsigned long s_seed; // size: 0x4, address: 0x80A47630
static unsigned char usedUp[32]; // size: 0x20, address: 0x809833B0
// Range: 0x8056A240 -> 0x8056A330
class DataNode getRandomSequence32A(class DataArray * msg /* r31 */) {
    // Local variables
    unsigned long seed; // r0
    unsigned char taken; // r6
    unsigned long which; // r5

    // References
    // -> static unsigned long s_seed;
    // -> static unsigned char usedUp[32];
}

static unsigned long s_seed; // size: 0x4, address: 0x80A47634
static unsigned char usedUp[32]; // size: 0x20, address: 0x809833D0
// Range: 0x8056A330 -> 0x8056A420
class DataNode getRandomSequence32B(class DataArray * msg /* r31 */) {
    // Local variables
    unsigned long seed; // r0
    unsigned char taken; // r6
    unsigned long which; // r5

    // References
    // -> static unsigned long s_seed;
    // -> static unsigned char usedUp[32];
}

// Range: 0x8056A420 -> 0x8056A49C
class DataNode op0(class DataArray * msg /* r30 */) {
    // Local variables
    unsigned long operand; // r0
    unsigned long w; // r0
}

// Range: 0x8056A49C -> 0x8056A520
class DataNode op1(class DataArray * msg /* r30 */) {
    // Local variables
    unsigned long operand; // r0
    unsigned long w; // r0
}

// Range: 0x8056A520 -> 0x8056A5A8
class DataNode op2(class DataArray * msg /* r30 */) {
    // Local variables
    unsigned long operand; // r0
    unsigned long w; // r4
}

// Range: 0x8056A5A8 -> 0x8056A634
class DataNode op3(class DataArray * msg /* r30 */) {
    // Local variables
    unsigned long operand; // r0
    unsigned long w; // r4
}

// Range: 0x8056A634 -> 0x8056A6C8
class DataNode op4(class DataArray * msg /* r30 */) {
    // Local variables
    unsigned long operand; // r4
    unsigned long w; // r3
}

// Range: 0x8056A6C8 -> 0x8056A758
class DataNode op5(class DataArray * msg /* r30 */) {
    // Local variables
    unsigned long operand; // r0
    unsigned long w; // r3
}

// Range: 0x8056A758 -> 0x8056A7DC
class DataNode op6(class DataArray * msg /* r30 */) {
    // Local variables
    unsigned long operand; // r0
    unsigned long w; // r0
}

// Range: 0x8056A7DC -> 0x8056A864
class DataNode op7(class DataArray * msg /* r30 */) {
    // Local variables
    unsigned long operand; // r0
    unsigned long w; // r3
}

// Range: 0x8056A864 -> 0x8056A8EC
class DataNode op8(class DataArray * msg /* r30 */) {
    // Local variables
    unsigned long operand; // r4
    unsigned long w; // r3
}

// Range: 0x8056A8EC -> 0x8056A974
class DataNode op9(class DataArray * msg /* r30 */) {
    // Local variables
    unsigned long operand; // r4
    unsigned long w; // r3
}

// Range: 0x8056A974 -> 0x8056AA08
class DataNode op10(class DataArray * msg /* r30 */) {
    // Local variables
    unsigned long operand; // r31
    unsigned long w; // r4
    unsigned long originalOperand; // r5
}

// Range: 0x8056AA08 -> 0x8056AA94
class DataNode op11(class DataArray * msg /* r30 */) {
    // Local variables
    unsigned long operand; // r0
    unsigned long w; // r4
}

// Range: 0x8056AA94 -> 0x8056AB20
class DataNode op12(class DataArray * msg /* r30 */) {
    // Local variables
    unsigned long operand; // r0
    unsigned long w; // r4
}

// Range: 0x8056AB20 -> 0x8056ABB4
class DataNode op13(class DataArray * msg /* r30 */) {
    // Local variables
    unsigned long operand; // r31
    unsigned long w; // r4
    unsigned long originalOperand; // r5
}

// Range: 0x8056ABB4 -> 0x8056AC3C
class DataNode op14(class DataArray * msg /* r30 */) {
    // Local variables
    unsigned long w; // r4
}

// Range: 0x8056AC3C -> 0x8056ACC4
class DataNode op15(class DataArray * msg /* r30 */) {
    // Local variables
    unsigned long w; // r4
}

// Range: 0x8056ACC4 -> 0x8056AD4C
class DataNode op16(class DataArray * msg /* r30 */) {
    // Local variables
    unsigned long w; // r4
}

// Range: 0x8056AD4C -> 0x8056ADD4
class DataNode op17(class DataArray * msg /* r30 */) {
    // Local variables
    unsigned long w; // r4
}

// Range: 0x8056ADD4 -> 0x8056AE5C
class DataNode op18(class DataArray * msg /* r30 */) {
    // Local variables
    unsigned long w; // r4
}

// Range: 0x8056AE5C -> 0x8056AEE4
class DataNode op19(class DataArray * msg /* r30 */) {
    // Local variables
    unsigned long w; // r4
}

// Range: 0x8056AEE4 -> 0x8056AF6C
class DataNode op20(class DataArray * msg /* r30 */) {
    // Local variables
    unsigned long w; // r4
}

// Range: 0x8056AF6C -> 0x8056AFF4
class DataNode op21(class DataArray * msg /* r30 */) {
    // Local variables
    unsigned long w; // r4
}

// Range: 0x8056AFF4 -> 0x8056B07C
class DataNode op22(class DataArray * msg /* r30 */) {
    // Local variables
    unsigned long w; // r4
}

// Range: 0x8056B07C -> 0x8056B104
class DataNode op23(class DataArray * msg /* r30 */) {
    // Local variables
    unsigned long w; // r4
}

// Range: 0x8056B104 -> 0x8056B18C
class DataNode op24(class DataArray * msg /* r30 */) {
    // Local variables
    unsigned long w; // r4
}

// Range: 0x8056B18C -> 0x8056B214
class DataNode op25(class DataArray * msg /* r30 */) {
    // Local variables
    unsigned long w; // r4
}

// Range: 0x8056B214 -> 0x8056B29C
class DataNode op26(class DataArray * msg /* r30 */) {
    // Local variables
    unsigned long w; // r4
}

// Range: 0x8056B29C -> 0x8056B324
class DataNode op27(class DataArray * msg /* r30 */) {
    // Local variables
    unsigned long w; // r4
}

// Range: 0x8056B324 -> 0x8056B3B0
class DataNode op28(class DataArray * msg /* r30 */) {
    // Local variables
    unsigned long operand; // r0
    unsigned long w; // r4
}

// Range: 0x8056B3B0 -> 0x8056B43C
class DataNode op29(class DataArray * msg /* r30 */) {
    // Local variables
    unsigned long operand; // r0
    unsigned long w; // r4
}

// Range: 0x8056B43C -> 0x8056B4C8
class DataNode op30(class DataArray * msg /* r30 */) {
    // Local variables
    unsigned long operand; // r0
    unsigned long w; // r4
}

// Range: 0x8056B4C8 -> 0x8056B554
class DataNode op31(class DataArray * msg /* r30 */) {
    // Local variables
    unsigned long operand; // r0
    unsigned long w; // r4
}

// Range: 0x8056B554 -> 0x8056B5FC
unsigned long ByteGrinder::pickOneOf32A() {
    // Local variables
    class DataArray * a; // r31
    char script[256]; // r1+0x8
    unsigned long result; // r30
}

// Range: 0x8056B5FC -> 0x8056B6A4
unsigned long ByteGrinder::pickOneOf32B() {
    // Local variables
    class DataArray * a; // r31
    char script[256]; // r1+0x8
    unsigned long result; // r30
}

static unsigned long s_seed; // size: 0x4, address: 0x80A47640
// Range: 0x8056B6A4 -> 0x8056B6E0
class DataNode getRandomLong() {
    // References
    // -> static unsigned long s_seed;
}

// Range: 0x8056B6E0 -> 0x8056B7B4
class DataNode magicNumberGenerator(class DataArray * msg /* r29 */) {
    // Local variables
    long hash; // r30
    long mask; // r30
}

class vector : protected _Vector_base {
    // total size: 0xC
};
// Range: 0x8056B7B4 -> 0x8056C434
void ByteGrinder::Init(class ByteGrinder * const this /* r31 */) {
    // Local variables
    char functionName[256]; // r1+0x130
    class vector funPtrs; // r1+0x124
    int i; // r30
}

class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class DataNode (* * _M_data)(class DataArray *); // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class DataNode (* * _M_start)(class DataArray *); // offset 0x0, size 0x4
    class DataNode (* * _M_finish)(class DataArray *); // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
// Range: 0x8056C434 -> 0x8056C6E4
void ByteGrinder::GrindArray(class ByteGrinder * const this /* r26 */, long seedA /* r0 */, long seedB /* r27 */, unsigned char * arrayToGrind /* r30 */, int arrayLen /* r31 */) {
    // Local variables
    char script[256]; // r1+0x160
    class DataArray * a; // r28
    class String mainScript; // r1+0x30
    int i; // r28
    char block[256]; // r1+0x60
    char callName[16]; // r1+0x20
    class DataArray * mainScriptArray; // r28
    int i; // r29
    char itoaBuffer[32]; // r1+0x40
    unsigned char w; // r27
    class String stringArgs; // r1+0x10
    int j; // r27
    class DataArray * args; // r27
}

static unsigned char gHvKeyGreen[16]; // size: 0x10, address: 0x8091ADB0
static unsigned char gHvKeyRed[16]; // size: 0x10, address: 0x8091ADC0
struct symmetric_ECB {
    // total size: 0x20C
    int cipher; // offset 0x0, size 0x4
    int blocklen; // offset 0x4, size 0x4
    union Symmetric_key key; // offset 0x8, size 0x204
};
struct rijndael_key {
    // total size: 0x204
    unsigned long eK[64]; // offset 0x0, size 0x100
    unsigned long dK[64]; // offset 0x100, size 0x100
    unsigned long k_len; // offset 0x200, size 0x4
};
union Symmetric_key {
    struct rijndael_key rijndael; // offset 0x0, size 0x204
};
// Range: 0x8056C6E4 -> 0x8056C75C
void ByteGrinder::HvDecrypt(unsigned char * inBlock /* r29 */, unsigned char * outBlock /* r30 */) {
    // Local variables
    struct symmetric_ECB * ecbState; // r31
    union Symmetric_key symKey; // r1+0x8

    // References
    // -> static unsigned char gHvKeyGreen[16];
}

struct {
    // total size: 0x8
} __RTTI__PPFP9DataArray_8DataNode; // size: 0x8, address: 0x8091ADF0

