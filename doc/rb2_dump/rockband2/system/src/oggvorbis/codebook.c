/*
    Compile unit: C:\rockband2\system\src\oggvorbis\codebook.c
    Producer: MW EABI PPC C-Compiler
    Language: C89
    Code range: 0x8053F514 -> 0x8053FF98
*/
// Range: 0x8053F514 -> 0x8053F840
int vorbis_staticbook_unpack(struct {
    // total size: 0x14
    long endbyte; // offset 0x0, size 0x4
    int endbit; // offset 0x4, size 0x4
    unsigned char * buffer; // offset 0x8, size 0x4
    unsigned char * ptr; // offset 0xC, size 0x4
    long storage; // offset 0x10, size 0x4
} * opb /* r29 */, struct static_codebook * s /* r30 */) {
    // Local variables
    long i; // r31
    long j; // r5
    long num; // r0
    long num; // r0
    long length; // r28
    long num; // r0
    int quantvals; // r28
}

// Range: 0x8053F840 -> 0x8053F89C
int vorbis_book_encode(struct codebook * book /* r30 */) {}

// Range: 0x8053F89C -> 0x8053F920
static unsigned int bitreverse(unsigned int x /* r6 */) {}

// Range: 0x8053F920 -> 0x8053FA80
static long decode_packed_entry_number(struct codebook * book /* r28 */, struct {
    // total size: 0x14
    long endbyte; // offset 0x0, size 0x4
    int endbit; // offset 0x4, size 0x4
    unsigned char * buffer; // offset 0x8, size 0x4
    unsigned char * ptr; // offset 0xC, size 0x4
    long storage; // offset 0x10, size 0x4
} * b /* r29 */) {
    // Local variables
    int read; // r31
    long lo; // r30
    long hi; // r27
    long lok; // r3
    long entry; // r27
    unsigned int testword; // r0
    long p; // r5
    long test; // r4
}

// Range: 0x8053FA80 -> 0x8053FAC0
long vorbis_book_decode(struct codebook * book /* r31 */) {
    // Local variables
    long packed_entry; // r0
}

// Range: 0x8053FAC0 -> 0x8053FBE8
long vorbis_book_decodevs_add(struct codebook * book /* r24 */, float * a /* r25 */, struct {
    // total size: 0x14
    long endbyte; // offset 0x0, size 0x4
    int endbit; // offset 0x4, size 0x4
    unsigned char * buffer; // offset 0x8, size 0x4
    unsigned char * ptr; // offset 0xC, size 0x4
    long storage; // offset 0x10, size 0x4
} * b /* r26 */) {
    // Local variables
    int step; // r30
    long * entry; // r29
    float * * t; // r28
    int i; // r27
    int j; // r5
    int o; // r6
}

// Range: 0x8053FBE8 -> 0x8053FE0C
long vorbis_book_decodev_add(struct codebook * book /* r27 */, float * a /* r28 */, struct {
    // total size: 0x14
    long endbyte; // offset 0x0, size 0x4
    int endbit; // offset 0x4, size 0x4
    unsigned char * buffer; // offset 0x8, size 0x4
    unsigned char * ptr; // offset 0xC, size 0x4
    long storage; // offset 0x10, size 0x4
} * b /* r29 */, int n /* r30 */) {
    // Local variables
    int i; // r31
    int j; // r3
    int entry; // r0
    float * t; // r4
}

// Range: 0x8053FE0C -> 0x8053FEB8
long vorbis_book_decodev_set(struct codebook * book /* r27 */, float * a /* r28 */, struct {
    // total size: 0x14
    long endbyte; // offset 0x0, size 0x4
    int endbit; // offset 0x4, size 0x4
    unsigned char * buffer; // offset 0x8, size 0x4
    unsigned char * ptr; // offset 0xC, size 0x4
    long storage; // offset 0x10, size 0x4
} * b /* r29 */, int n /* r30 */) {
    // Local variables
    int i; // r31
    int j; // r3
    int entry; // r0
    float * t; // r4
}

// Range: 0x8053FEB8 -> 0x8053FF98
long vorbis_book_decodevv_add(struct codebook * book /* r24 */, float * * a /* r25 */, long offset /* r26 */, int ch /* r27 */, struct {
    // total size: 0x14
    long endbyte; // offset 0x0, size 0x4
    int endbit; // offset 0x4, size 0x4
    unsigned char * buffer; // offset 0x8, size 0x4
    unsigned char * ptr; // offset 0xC, size 0x4
    long storage; // offset 0x10, size 0x4
} * b /* r28 */, int n /* r29 */) {
    // Local variables
    long i; // r31
    long j; // r5
    long entry; // r0
    int chptr; // r30
    const float * t; // r6
}


