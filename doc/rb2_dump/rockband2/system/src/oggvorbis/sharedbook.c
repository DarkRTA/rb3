/*
    Compile unit: C:\rockband2\system\src\oggvorbis\sharedbook.c
    Producer: MW EABI PPC C-Compiler
    Language: C89
    Code range: 0x8054A940 -> 0x8054B660
*/
// Range: 0x8054A940 -> 0x8054A960
int _ilog() {
    // Local variables
    int ret; // r4
}

// Range: 0x8054A960 -> 0x8054A9BC
float _float32_unpack() {
    // Local variables
    double mant; // f1
    long exp; // r4
}

// Range: 0x8054A9BC -> 0x8054ABB0
unsigned int * _make_words(long * l /* r27 */, long n /* r28 */, long sparsecount /* r29 */) {
    // Local variables
    long i; // r3
    long j; // r8
    long count; // r31
    unsigned int marker[33]; // r1+0x8
    unsigned int * r; // r30
    long length; // r9
    unsigned int entry; // r0
    unsigned int temp; // r4
}

// Range: 0x8054ABB0 -> 0x8054AC88
long _book_maptype1_quantvals() {
    // Local variables
    long vals; // r3
    long acc; // r4
    long acc1; // r5
    int i; // r6
}

// Range: 0x8054AC88 -> 0x8054AF40
float * _book_unquantize(const struct static_codebook * b /* r28 */, int n /* r30 */, int * sparsemap /* r29 */) {
    // Local variables
    long j; // r4
    long k; // r5
    long count; // r31
    int quantvals; // r0
    float mindel; // f0
    float delta; // f0
    float * r; // r30
    float last; // f2
    int indexdiv; // r9
    float val; // f0
    float last; // f2
    float val; // f0
}

// Range: 0x8054AF40 -> 0x8054B02C
void vorbis_staticbook_clear(struct static_codebook * b /* r31 */) {}

// Range: 0x8054B02C -> 0x8054B06C
void vorbis_staticbook_destroy(struct static_codebook * b /* r31 */) {}

// Range: 0x8054B06C -> 0x8054B0F4
void vorbis_book_clear(struct codebook * b /* r31 */) {}

// Range: 0x8054B0F4 -> 0x8054B174
int vorbis_book_init_encode(struct codebook * c /* r30 */, const struct static_codebook * s /* r31 */) {}

// Range: 0x8054B174 -> 0x8054B1F8
static unsigned int bitreverse(unsigned int x /* r6 */) {}

// Range: 0x8054B1F8 -> 0x8054B228
static int sort32a() {}

// Range: 0x8054B228 -> 0x8054B660
int vorbis_book_init_decode(struct codebook * c /* r23 */, const struct static_codebook * s /* r24 */) {
    // Local variables
    int i; // r29
    int j; // r7
    int n; // r28
    int tabn; // r30
    int * sortindex; // r27
    unsigned int * codes; // r26
    unsigned int * * codep; // r25
    unsigned int orig; // r0
    unsigned int mask; // r25
    long lo; // r26
    long hi; // r27
    unsigned int word; // r24
    unsigned long loval; // r0
    unsigned long hival; // r3
}


