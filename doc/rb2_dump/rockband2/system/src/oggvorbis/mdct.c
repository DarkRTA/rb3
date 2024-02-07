/*
    Compile unit: C:\rockband2\system\src\oggvorbis\mdct.c
    Producer: MW EABI PPC C-Compiler
    Language: C89
    Code range: 0x80545444 -> 0x805466F4
*/
// Range: 0x80545444 -> 0x805457F0
void mdct_init(struct {
    // total size: 0x18
    int n; // offset 0x0, size 0x4
    int log2n; // offset 0x4, size 0x4
    float * trig; // offset 0x8, size 0x4
    float * trig2; // offset 0xC, size 0x4
    int * bitrev; // offset 0x10, size 0x4
    float scale; // offset 0x14, size 0x4
} * lookup /* r18 */, int n /* r19 */) {
    // Local variables
    int * bitrev; // r0
    float * T; // r0
    float * T2; // r0
    int i; // r21
    int n2; // r20
    int log2n; // r0
    int mask; // r6
    int i; // r7
    int j; // r3
    int msb; // r8
    int acc; // r9
}

// Range: 0x805457F0 -> 0x80545874
static void mdct_butterfly_8() {
    // Local variables
    float r0; // f5
    float r1; // f6
    float r2; // f7
    float r3; // f8
}

// Range: 0x80545874 -> 0x8054598C
static void mdct_butterfly_16(float * x /* r31 */) {
    // Local variables
    float r0; // f5
    float r1; // f6
}

// Range: 0x8054598C -> 0x80545BAC
static void mdct_butterfly_32(float * x /* r31 */) {
    // Local variables
    float r0; // f3
    float r1; // f4
}

// Range: 0x80545BAC -> 0x80545D40
static void mdct_butterfly_first() {
    // Local variables
    float * x1; // r7
    float * x2; // r6
    float r0; // f0
    float r1; // f1
}

// Range: 0x80545D40 -> 0x80545ED8
static void mdct_butterfly_generic() {
    // Local variables
    float * x1; // r8
    float * x2; // r6
    float r0; // f0
    float r1; // f1
}

// Range: 0x80545ED8 -> 0x80545FA8
static void mdct_butterflies(float * x /* r25 */, int points /* r26 */) {
    // Local variables
    float * T; // r31
    float * T2; // r30
    int stages; // r29
    int i; // r28
    int j; // r27
}

// Range: 0x80545FA8 -> 0x80546018
void mdct_clear(struct {
    // total size: 0x18
    int n; // offset 0x0, size 0x4
    int log2n; // offset 0x4, size 0x4
    float * trig; // offset 0x8, size 0x4
    float * trig2; // offset 0xC, size 0x4
    int * bitrev; // offset 0x10, size 0x4
    float scale; // offset 0x14, size 0x4
} * l /* r31 */) {}

// Range: 0x80546018 -> 0x80546148
static void mdct_bitreverse(float * x /* r9 */) {
    // Local variables
    int n; // r5
    int * bit; // r6
    float * w0; // r4
    float * w1; // r7
    float * T; // r3
    float * x0; // r5
    float * x1; // r8
    float r0; // f8
    float r1; // f9
    float r2; // f1
    float r3; // f2
}

// Range: 0x80546148 -> 0x805464A0
void mdct_backward(struct {
    // total size: 0x18
    int n; // offset 0x0, size 0x4
    int log2n; // offset 0x4, size 0x4
    float * trig; // offset 0x8, size 0x4
    float * trig2; // offset 0xC, size 0x4
    int * bitrev; // offset 0x10, size 0x4
    float scale; // offset 0x14, size 0x4
} * init /* r28 */, float * out /* r29 */) {
    // Local variables
    int n; // r6
    int n2; // r31
    int n4; // r30
    float * iX; // r8
    float * oX; // r9
    float * T; // r6
    float * oX1; // r4
    float * oX2; // r3
    float * iX; // r5
}

// Range: 0x805464A0 -> 0x805466F4
void mdct_forward(struct {
    // total size: 0x18
    int n; // offset 0x0, size 0x4
    int log2n; // offset 0x4, size 0x4
    float * trig; // offset 0x8, size 0x4
    float * trig2; // offset 0xC, size 0x4
    int * bitrev; // offset 0x10, size 0x4
    float scale; // offset 0x14, size 0x4
} * init /* r27 */, float * out /* r28 */) {
    // Local variables
    int n; // r9
    int n2; // r5
    int n4; // r30
    int n8; // r10
    float * w; // r29
    float * w2; // r0
    float r0; // f2
    float r1; // f3
    float * x0; // r6
    float * x1; // r11
    float * T; // r3
    int i; // r7
}


