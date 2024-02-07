/*
    Compile unit: C:\rockband2\system\src\oggvorbis\bitwise.c
    Producer: MW EABI PPC C-Compiler
    Language: C89
    Code range: 0x8053DFA8 -> 0x8053E40C
*/
static unsigned long mask[33]; // size: 0x84, address: 0x809086C0
// Range: 0x8053DFA8 -> 0x8053DFFC
void oggpack_writeinit(struct {
    // total size: 0x14
    long endbyte; // offset 0x0, size 0x4
    int endbit; // offset 0x4, size 0x4
    unsigned char * buffer; // offset 0x8, size 0x4
    unsigned char * ptr; // offset 0xC, size 0x4
    long storage; // offset 0x10, size 0x4
} * b /* r31 */) {}

// Range: 0x8053DFFC -> 0x8053E158
void oggpack_write(struct {
    // total size: 0x14
    long endbyte; // offset 0x0, size 0x4
    int endbit; // offset 0x4, size 0x4
    unsigned char * buffer; // offset 0x8, size 0x4
    unsigned char * ptr; // offset 0xC, size 0x4
    long storage; // offset 0x10, size 0x4
} * b /* r29 */, unsigned long value /* r30 */, int bits /* r31 */) {
    // References
    // -> static unsigned long mask[33];
}

// Range: 0x8053E158 -> 0x8053E174
void oggpack_writealign() {
    // Local variables
    int bits; // r5
}

// Range: 0x8053E174 -> 0x8053E1B4
void oggpack_writeclear(struct {
    // total size: 0x14
    long endbyte; // offset 0x0, size 0x4
    int endbit; // offset 0x4, size 0x4
    unsigned char * buffer; // offset 0x8, size 0x4
    unsigned char * ptr; // offset 0xC, size 0x4
    long storage; // offset 0x10, size 0x4
} * b /* r31 */) {}

// Range: 0x8053E1B4 -> 0x8053E20C
void oggpack_readinit(struct {
    // total size: 0x14
    long endbyte; // offset 0x0, size 0x4
    int endbit; // offset 0x4, size 0x4
    unsigned char * buffer; // offset 0x8, size 0x4
    unsigned char * ptr; // offset 0xC, size 0x4
    long storage; // offset 0x10, size 0x4
} * b /* r29 */, unsigned char * buf /* r30 */, int bytes /* r31 */) {}

// Range: 0x8053E20C -> 0x8053E2D0
long oggpack_look(int bits /* r8 */) {
    // Local variables
    unsigned long ret; // r5
    unsigned long m; // r7

    // References
    // -> static unsigned long mask[33];
}

// Range: 0x8053E2D0 -> 0x8053E304
void oggpack_adv(int bits /* r5 */) {}

// Range: 0x8053E304 -> 0x8053E3F0
long oggpack_read(int bits /* r4 */) {
    // Local variables
    unsigned long ret; // r0
    unsigned long m; // r9

    // References
    // -> static unsigned long mask[33];
}

// Range: 0x8053E3F0 -> 0x8053E40C
long oggpack_bytes() {}


