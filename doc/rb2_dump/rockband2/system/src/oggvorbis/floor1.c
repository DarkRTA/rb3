/*
    Compile unit: C:\rockband2\system\src\oggvorbis\floor1.c
    Producer: MW EABI PPC C-Compiler
    Language: C89
    Code range: 0x80540844 -> 0x805426A8
*/
// Range: 0x80540844 -> 0x80540888
static void floor1_free_info() {
    // Local variables
    struct {
        // total size: 0x460
        int partitions; // offset 0x0, size 0x4
        int partitionclass[31]; // offset 0x4, size 0x7C
        int class_dim[16]; // offset 0x80, size 0x40
        int class_subs[16]; // offset 0xC0, size 0x40
        int class_book[16]; // offset 0x100, size 0x40
        int class_subbook[16][8]; // offset 0x140, size 0x200
        int mult; // offset 0x340, size 0x4
        int postlist[65]; // offset 0x344, size 0x104
        float maxover; // offset 0x448, size 0x4
        float maxunder; // offset 0x44C, size 0x4
        float maxerr; // offset 0x450, size 0x4
        float twofitweight; // offset 0x454, size 0x4
        float twofitatten; // offset 0x458, size 0x4
        int n; // offset 0x45C, size 0x4
    } * info; // r31
}

// Range: 0x80540888 -> 0x805408CC
static void floor1_free_look() {
    // Local variables
    struct {
        // total size: 0x520
        int sorted_index[65]; // offset 0x0, size 0x104
        int forward_index[65]; // offset 0x104, size 0x104
        int reverse_index[65]; // offset 0x208, size 0x104
        int hineighbor[63]; // offset 0x30C, size 0xFC
        int loneighbor[63]; // offset 0x408, size 0xFC
        int posts; // offset 0x504, size 0x4
        int n; // offset 0x508, size 0x4
        int quant_q; // offset 0x50C, size 0x4
        struct {
            // total size: 0x460
            int partitions; // offset 0x0, size 0x4
            int partitionclass[31]; // offset 0x4, size 0x7C
            int class_dim[16]; // offset 0x80, size 0x40
            int class_subs[16]; // offset 0xC0, size 0x40
            int class_book[16]; // offset 0x100, size 0x40
            int class_subbook[16][8]; // offset 0x140, size 0x200
            int mult; // offset 0x340, size 0x4
            int postlist[65]; // offset 0x344, size 0x104
            float maxover; // offset 0x448, size 0x4
            float maxunder; // offset 0x44C, size 0x4
            float maxerr; // offset 0x450, size 0x4
            float twofitweight; // offset 0x454, size 0x4
            float twofitatten; // offset 0x458, size 0x4
            int n; // offset 0x45C, size 0x4
        } * vi; // offset 0x510, size 0x4
        long phrasebits; // offset 0x514, size 0x4
        long postbits; // offset 0x518, size 0x4
        long frames; // offset 0x51C, size 0x4
    } * look; // r31
}

// Range: 0x805408CC -> 0x805408EC
static int ilog() {
    // Local variables
    int ret; // r4
}

// Range: 0x805408EC -> 0x80540918
static int ilog2() {
    // Local variables
    int ret; // r4
}

// Range: 0x80540918 -> 0x80540AEC
static void floor1_pack(void * i /* r24 */, struct {
    // total size: 0x14
    long endbyte; // offset 0x0, size 0x4
    int endbit; // offset 0x4, size 0x4
    unsigned char * buffer; // offset 0x8, size 0x4
    unsigned char * ptr; // offset 0xC, size 0x4
    long storage; // offset 0x10, size 0x4
} * opb /* r25 */) {
    // Local variables
    struct {
        // total size: 0x460
        int partitions; // offset 0x0, size 0x4
        int partitionclass[31]; // offset 0x4, size 0x7C
        int class_dim[16]; // offset 0x80, size 0x40
        int class_subs[16]; // offset 0xC0, size 0x40
        int class_book[16]; // offset 0x100, size 0x40
        int class_subbook[16][8]; // offset 0x140, size 0x200
        int mult; // offset 0x340, size 0x4
        int postlist[65]; // offset 0x344, size 0x104
        float maxover; // offset 0x448, size 0x4
        float maxunder; // offset 0x44C, size 0x4
        float maxerr; // offset 0x450, size 0x4
        float twofitweight; // offset 0x454, size 0x4
        float twofitatten; // offset 0x458, size 0x4
        int n; // offset 0x45C, size 0x4
    } * info; // r0
    int j; // r30
    int k; // r29
    int count; // r28
    int rangebits; // r26
    int maxposit; // r27
    int maxclass; // r26
}

// Range: 0x80540AEC -> 0x80540D20
static void * floor1_unpack(struct {
    // total size: 0x14
    long endbyte; // offset 0x0, size 0x4
    int endbit; // offset 0x4, size 0x4
    unsigned char * buffer; // offset 0x8, size 0x4
    unsigned char * ptr; // offset 0xC, size 0x4
    long storage; // offset 0x10, size 0x4
} * opb /* r25 */) {
    // Local variables
    struct codec_setup_info * ci; // r31
    int j; // r30
    int k; // r29
    int count; // r28
    int maxclass; // r27
    int rangebits; // r27
    struct {
        // total size: 0x460
        int partitions; // offset 0x0, size 0x4
        int partitionclass[31]; // offset 0x4, size 0x7C
        int class_dim[16]; // offset 0x80, size 0x40
        int class_subs[16]; // offset 0xC0, size 0x40
        int class_book[16]; // offset 0x100, size 0x40
        int class_subbook[16][8]; // offset 0x140, size 0x200
        int mult; // offset 0x340, size 0x4
        int postlist[65]; // offset 0x344, size 0x104
        float maxover; // offset 0x448, size 0x4
        float maxunder; // offset 0x44C, size 0x4
        float maxerr; // offset 0x450, size 0x4
        float twofitweight; // offset 0x454, size 0x4
        float twofitatten; // offset 0x458, size 0x4
        int n; // offset 0x45C, size 0x4
    } * info; // r26
    int t; // r0
}

// Range: 0x80540D20 -> 0x80540D38
static int icomp() {}

// Range: 0x80540D38 -> 0x80540FA0
static void * floor1_look(void * in /* r29 */) {
    // Local variables
    int * sortpointer[65]; // r1+0x8
    struct {
        // total size: 0x460
        int partitions; // offset 0x0, size 0x4
        int partitionclass[31]; // offset 0x4, size 0x7C
        int class_dim[16]; // offset 0x80, size 0x40
        int class_subs[16]; // offset 0xC0, size 0x40
        int class_book[16]; // offset 0x100, size 0x40
        int class_subbook[16][8]; // offset 0x140, size 0x200
        int mult; // offset 0x340, size 0x4
        int postlist[65]; // offset 0x344, size 0x104
        float maxover; // offset 0x448, size 0x4
        float maxunder; // offset 0x44C, size 0x4
        float maxerr; // offset 0x450, size 0x4
        float twofitweight; // offset 0x454, size 0x4
        float twofitatten; // offset 0x458, size 0x4
        int n; // offset 0x45C, size 0x4
    } * info; // r0
    struct {
        // total size: 0x520
        int sorted_index[65]; // offset 0x0, size 0x104
        int forward_index[65]; // offset 0x104, size 0x104
        int reverse_index[65]; // offset 0x208, size 0x104
        int hineighbor[63]; // offset 0x30C, size 0xFC
        int loneighbor[63]; // offset 0x408, size 0xFC
        int posts; // offset 0x504, size 0x4
        int n; // offset 0x508, size 0x4
        int quant_q; // offset 0x50C, size 0x4
        struct {
            // total size: 0x460
            int partitions; // offset 0x0, size 0x4
            int partitionclass[31]; // offset 0x4, size 0x7C
            int class_dim[16]; // offset 0x80, size 0x40
            int class_subs[16]; // offset 0xC0, size 0x40
            int class_book[16]; // offset 0x100, size 0x40
            int class_subbook[16][8]; // offset 0x140, size 0x200
            int mult; // offset 0x340, size 0x4
            int postlist[65]; // offset 0x344, size 0x104
            float maxover; // offset 0x448, size 0x4
            float maxunder; // offset 0x44C, size 0x4
            float maxerr; // offset 0x450, size 0x4
            float twofitweight; // offset 0x454, size 0x4
            float twofitatten; // offset 0x458, size 0x4
            int n; // offset 0x45C, size 0x4
        } * vi; // offset 0x510, size 0x4
        long phrasebits; // offset 0x514, size 0x4
        long postbits; // offset 0x518, size 0x4
        long frames; // offset 0x51C, size 0x4
    } * look; // r31
    int i; // r5
    int j; // r4
    int n; // r30
    int lo; // r6
    int hi; // r7
    int lx; // r8
    int hx; // r9
    int currentx; // r10
    int x; // r0
}

// Range: 0x80540FA0 -> 0x80540FD8
static int render_point(int y0 /* r8 */) {
    // Local variables
    int dy; // r6
    int ady; // r5
    int off; // r0
}

// Range: 0x80540FD8 -> 0x80541018
static int vorbis_dBquant() {
    // Local variables
    int i; // r3
}

static float FLOOR1_fromdB_LOOKUP[256]; // size: 0x400, address: 0x80908790
// Range: 0x80541018 -> 0x805410D4
static void render_line() {
    // Local variables
    int dy; // r6
    int adx; // r10
    int ady; // r11
    int base; // r12
    int sy; // r0
    int x; // r3
    int y; // r5
    int err; // r31

    // References
    // -> static float FLOOR1_fromdB_LOOKUP[256];
}

// Range: 0x805410D4 -> 0x80541150
static void render_line0() {
    // Local variables
    int dy; // r6
    int adx; // r9
    int ady; // r10
    int base; // r11
    int sy; // r0
    int x; // r3
    int y; // r5
    int err; // r12
}

struct lsfit_acc {
    // total size: 0x20
    long x0; // offset 0x0, size 0x4
    long x1; // offset 0x4, size 0x4
    long xa; // offset 0x8, size 0x4
    long ya; // offset 0xC, size 0x4
    long x2a; // offset 0x10, size 0x4
    long y2a; // offset 0x14, size 0x4
    long xya; // offset 0x18, size 0x4
    long an; // offset 0x1C, size 0x4
};
// Range: 0x80541150 -> 0x80541344
static int accumulate_fit(const float * flr /* r14 */, const float * mdct /* f1 */, int x0 /* r15 */, int x1 /* r16 */, struct lsfit_acc * a /* r17 */, int n /* r31 */, struct {
    // total size: 0x460
    int partitions; // offset 0x0, size 0x4
    int partitionclass[31]; // offset 0x4, size 0x7C
    int class_dim[16]; // offset 0x80, size 0x40
    int class_subs[16]; // offset 0xC0, size 0x40
    int class_book[16]; // offset 0x100, size 0x40
    int class_subbook[16][8]; // offset 0x140, size 0x200
    int mult; // offset 0x340, size 0x4
    int postlist[65]; // offset 0x344, size 0x104
    float maxover; // offset 0x448, size 0x4
    float maxunder; // offset 0x44C, size 0x4
    float maxerr; // offset 0x450, size 0x4
    float twofitweight; // offset 0x454, size 0x4
    float twofitatten; // offset 0x458, size 0x4
    int n; // offset 0x45C, size 0x4
} * info /* r18 */) {
    // Local variables
    long i; // r0
    long xa; // r30
    long ya; // r29
    long x2a; // r28
    long y2a; // r27
    long xya; // r26
    long na; // r25
    long xb; // r24
    long yb; // r23
    long x2b; // r22
    long y2b; // r21
    long xyb; // r20
    long nb; // r19
    int quantized; // r0
    int weight; // r3
}

// Range: 0x80541344 -> 0x8054159C
static void fit_line(int * y0 /* r28 */, int * y1 /* r29 */) {
    // Local variables
    long x; // r0
    long y; // r7
    long x2; // r8
    long xy; // r9
    long an; // r10
    long i; // r27
    long x0; // r11
    long x1; // r30
    double fx; // f3
    double fy; // f4
    double fx2; // f5
    double fxy; // f6
    double denom; // f7
    double a; // f31
    double b; // f30
}

// Range: 0x8054159C -> 0x80541830
static int inspect_error(int x1 /* r17 */, int y0 /* r18 */, const float * mask /* r19 */, const float * mdct /* r20 */, struct {
    // total size: 0x460
    int partitions; // offset 0x0, size 0x4
    int partitionclass[31]; // offset 0x4, size 0x7C
    int class_dim[16]; // offset 0x80, size 0x40
    int class_subs[16]; // offset 0xC0, size 0x40
    int class_book[16]; // offset 0x100, size 0x40
    int class_subbook[16][8]; // offset 0x140, size 0x200
    int mult; // offset 0x340, size 0x4
    int postlist[65]; // offset 0x344, size 0x104
    float maxover; // offset 0x448, size 0x4
    float maxunder; // offset 0x44C, size 0x4
    float maxerr; // offset 0x450, size 0x4
    float twofitweight; // offset 0x454, size 0x4
    float twofitatten; // offset 0x458, size 0x4
    int n; // offset 0x45C, size 0x4
} * info /* r21 */) {
    // Local variables
    int dy; // r5
    int adx; // r28
    int ady; // r27
    int base; // r26
    int sy; // r0
    int x; // r25
    int y; // [invalid]
    int err; // r24
    int val; // r0
    int mse; // r23
    int n; // r22
}

// Range: 0x80541830 -> 0x80541864
static int post_Y() {}

// Range: 0x80541864 -> 0x80541CD8
int * floor1_fit(struct vorbis_block * vb /* r14 */, struct {
    // total size: 0x520
    int sorted_index[65]; // offset 0x0, size 0x104
    int forward_index[65]; // offset 0x104, size 0x104
    int reverse_index[65]; // offset 0x208, size 0x104
    int hineighbor[63]; // offset 0x30C, size 0xFC
    int loneighbor[63]; // offset 0x408, size 0xFC
    int posts; // offset 0x504, size 0x4
    int n; // offset 0x508, size 0x4
    int quant_q; // offset 0x50C, size 0x4
    struct {
        // total size: 0x460
        int partitions; // offset 0x0, size 0x4
        int partitionclass[31]; // offset 0x4, size 0x7C
        int class_dim[16]; // offset 0x80, size 0x40
        int class_subs[16]; // offset 0xC0, size 0x40
        int class_book[16]; // offset 0x100, size 0x40
        int class_subbook[16][8]; // offset 0x140, size 0x200
        int mult; // offset 0x340, size 0x4
        int postlist[65]; // offset 0x344, size 0x104
        float maxover; // offset 0x448, size 0x4
        float maxunder; // offset 0x44C, size 0x4
        float maxerr; // offset 0x450, size 0x4
        float twofitweight; // offset 0x454, size 0x4
        float twofitatten; // offset 0x458, size 0x4
        int n; // offset 0x45C, size 0x4
    } * vi; // offset 0x510, size 0x4
    long phrasebits; // offset 0x514, size 0x4
    long postbits; // offset 0x518, size 0x4
    long frames; // offset 0x51C, size 0x4
} * look /* r15 */, const float * logmdct /* r16 */, const float * logmask /* r17 */) {
    // Local variables
    long i; // r29
    long j; // r5
    struct {
        // total size: 0x460
        int partitions; // offset 0x0, size 0x4
        int partitionclass[31]; // offset 0x4, size 0x7C
        int class_dim[16]; // offset 0x80, size 0x40
        int class_subs[16]; // offset 0xC0, size 0x40
        int class_book[16]; // offset 0x100, size 0x40
        int class_subbook[16][8]; // offset 0x140, size 0x200
        int mult; // offset 0x340, size 0x4
        int postlist[65]; // offset 0x344, size 0x104
        float maxover; // offset 0x448, size 0x4
        float maxunder; // offset 0x44C, size 0x4
        float maxerr; // offset 0x450, size 0x4
        float twofitweight; // offset 0x454, size 0x4
        float twofitatten; // offset 0x458, size 0x4
        int n; // offset 0x45C, size 0x4
    } * info; // r28
    long n; // r18
    long posts; // r27
    long nonzero; // r19
    struct lsfit_acc fits[64]; // r1+0x538
    int fit_valueA[65]; // r1+0x430
    int fit_valueB[65]; // r1+0x32C
    int loneighbor[65]; // r1+0x228
    int hineighbor[65]; // r1+0x124
    int * output; // r20
    int memo[65]; // r1+0x20
    int y0; // r1+0x1C
    int y1; // r1+0x18
    int sortpos; // r26
    int ln; // r25
    int hn; // r24
    int lsortpos; // r23
    int hsortpos; // r22
    int lx; // r21
    int hx; // r20
    int ly; // r19
    int hy; // r18
    int ly0; // r1+0x14
    int ly1; // r1+0x10
    int hy0; // r1+0xC
    int hy1; // r1+0x8
    int ln; // r4
    int hn; // r0
    int predicted; // r0
    int vx; // r0
}

// Range: 0x80541CD8 -> 0x80541DB8
int * floor1_interpolate_fit(int * A /* r28 */, int * B /* r29 */, int del /* r30 */) {
    // Local variables
    long i; // r7
    long posts; // r31
    int * output; // r8
}

static long seq; // size: 0x4, address: 0x80A53E20
// Range: 0x80541DB8 -> 0x805422E4
int floor1_encode(struct vorbis_block * vb /* r28 */, struct {
    // total size: 0x520
    int sorted_index[65]; // offset 0x0, size 0x104
    int forward_index[65]; // offset 0x104, size 0x104
    int reverse_index[65]; // offset 0x208, size 0x104
    int hineighbor[63]; // offset 0x30C, size 0xFC
    int loneighbor[63]; // offset 0x408, size 0xFC
    int posts; // offset 0x504, size 0x4
    int n; // offset 0x508, size 0x4
    int quant_q; // offset 0x50C, size 0x4
    struct {
        // total size: 0x460
        int partitions; // offset 0x0, size 0x4
        int partitionclass[31]; // offset 0x4, size 0x7C
        int class_dim[16]; // offset 0x80, size 0x40
        int class_subs[16]; // offset 0xC0, size 0x40
        int class_book[16]; // offset 0x100, size 0x40
        int class_subbook[16][8]; // offset 0x140, size 0x200
        int mult; // offset 0x340, size 0x4
        int postlist[65]; // offset 0x344, size 0x104
        float maxover; // offset 0x448, size 0x4
        float maxunder; // offset 0x44C, size 0x4
        float maxerr; // offset 0x450, size 0x4
        float twofitweight; // offset 0x454, size 0x4
        float twofitatten; // offset 0x458, size 0x4
        int n; // offset 0x45C, size 0x4
    } * vi; // offset 0x510, size 0x4
    long phrasebits; // offset 0x514, size 0x4
    long postbits; // offset 0x518, size 0x4
    long frames; // offset 0x51C, size 0x4
} * look /* r29 */, int * post /* r30 */, int * ilogmask /* r31 */) {
    // Local variables
    long i; // r24
    long j; // r25
    struct {
        // total size: 0x460
        int partitions; // offset 0x0, size 0x4
        int partitionclass[31]; // offset 0x4, size 0x7C
        int class_dim[16]; // offset 0x80, size 0x40
        int class_subs[16]; // offset 0xC0, size 0x40
        int class_book[16]; // offset 0x100, size 0x40
        int class_subbook[16][8]; // offset 0x140, size 0x200
        int mult; // offset 0x340, size 0x4
        int postlist[65]; // offset 0x344, size 0x104
        float maxover; // offset 0x448, size 0x4
        float maxunder; // offset 0x44C, size 0x4
        float maxerr; // offset 0x450, size 0x4
        float twofitweight; // offset 0x454, size 0x4
        float twofitatten; // offset 0x458, size 0x4
        int n; // offset 0x45C, size 0x4
    } * info; // r23
    long posts; // r22
    struct codec_setup_info * ci; // r4
    int out[65]; // r1+0x48
    struct static_codebook * * sbooks; // r21
    struct codebook * books; // r20
    int val; // r6
    int ln; // r0
    int hn; // r3
    int predicted; // r3
    int val; // r5
    int class; // r22
    int cdim; // r26
    int csubbits; // r3
    int csub; // r5
    int bookas[8]; // r1+0x28
    int cval; // r4
    int cshift; // r6
    int k; // r27
    int l; // r10
    int maxval[8]; // r1+0x8
    int book; // r5
    int hx; // r20
    int lx; // r3
    int ly; // r5
    int current; // r0
    int hy; // r21

    // References
    // -> static long seq;
}

// Range: 0x805422E4 -> 0x8054257C
static void * floor1_inverse1(struct vorbis_block * vb /* r19 */, void * in /* r20 */) {
    // Local variables
    struct {
        // total size: 0x520
        int sorted_index[65]; // offset 0x0, size 0x104
        int forward_index[65]; // offset 0x104, size 0x104
        int reverse_index[65]; // offset 0x208, size 0x104
        int hineighbor[63]; // offset 0x30C, size 0xFC
        int loneighbor[63]; // offset 0x408, size 0xFC
        int posts; // offset 0x504, size 0x4
        int n; // offset 0x508, size 0x4
        int quant_q; // offset 0x50C, size 0x4
        struct {
            // total size: 0x460
            int partitions; // offset 0x0, size 0x4
            int partitionclass[31]; // offset 0x4, size 0x7C
            int class_dim[16]; // offset 0x80, size 0x40
            int class_subs[16]; // offset 0xC0, size 0x40
            int class_book[16]; // offset 0x100, size 0x40
            int class_subbook[16][8]; // offset 0x140, size 0x200
            int mult; // offset 0x340, size 0x4
            int postlist[65]; // offset 0x344, size 0x104
            float maxover; // offset 0x448, size 0x4
            float maxunder; // offset 0x44C, size 0x4
            float maxerr; // offset 0x450, size 0x4
            float twofitweight; // offset 0x454, size 0x4
            float twofitatten; // offset 0x458, size 0x4
            int n; // offset 0x45C, size 0x4
        } * vi; // offset 0x510, size 0x4
        long phrasebits; // offset 0x514, size 0x4
        long postbits; // offset 0x518, size 0x4
        long frames; // offset 0x51C, size 0x4
    } * look; // r0
    struct {
        // total size: 0x460
        int partitions; // offset 0x0, size 0x4
        int partitionclass[31]; // offset 0x4, size 0x7C
        int class_dim[16]; // offset 0x80, size 0x40
        int class_subs[16]; // offset 0xC0, size 0x40
        int class_book[16]; // offset 0x100, size 0x40
        int class_subbook[16][8]; // offset 0x140, size 0x200
        int mult; // offset 0x340, size 0x4
        int postlist[65]; // offset 0x344, size 0x104
        float maxover; // offset 0x448, size 0x4
        float maxunder; // offset 0x44C, size 0x4
        float maxerr; // offset 0x450, size 0x4
        float twofitweight; // offset 0x454, size 0x4
        float twofitatten; // offset 0x458, size 0x4
        int n; // offset 0x45C, size 0x4
    } * info; // r29
    int i; // r28
    int j; // r30
    int k; // r31
    struct codebook * books; // r27
    int * fit_value; // r26
    int class; // r25
    int cdim; // r24
    int csubbits; // r23
    int csub; // r22
    int cval; // r21
    int book; // r0
    int predicted; // r0
    int hiroom; // r4
    int room; // r0
    int val; // r5
}

// Range: 0x8054257C -> 0x805426A8
static int floor1_inverse2(void * in /* r28 */, void * memo /* r29 */, float * out /* r30 */) {
    // Local variables
    struct {
        // total size: 0x520
        int sorted_index[65]; // offset 0x0, size 0x104
        int forward_index[65]; // offset 0x104, size 0x104
        int reverse_index[65]; // offset 0x208, size 0x104
        int hineighbor[63]; // offset 0x30C, size 0xFC
        int loneighbor[63]; // offset 0x408, size 0xFC
        int posts; // offset 0x504, size 0x4
        int n; // offset 0x508, size 0x4
        int quant_q; // offset 0x50C, size 0x4
        struct {
            // total size: 0x460
            int partitions; // offset 0x0, size 0x4
            int partitionclass[31]; // offset 0x4, size 0x7C
            int class_dim[16]; // offset 0x80, size 0x40
            int class_subs[16]; // offset 0xC0, size 0x40
            int class_book[16]; // offset 0x100, size 0x40
            int class_subbook[16][8]; // offset 0x140, size 0x200
            int mult; // offset 0x340, size 0x4
            int postlist[65]; // offset 0x344, size 0x104
            float maxover; // offset 0x448, size 0x4
            float maxunder; // offset 0x44C, size 0x4
            float maxerr; // offset 0x450, size 0x4
            float twofitweight; // offset 0x454, size 0x4
            float twofitatten; // offset 0x458, size 0x4
            int n; // offset 0x45C, size 0x4
        } * vi; // offset 0x510, size 0x4
        long phrasebits; // offset 0x514, size 0x4
        long postbits; // offset 0x518, size 0x4
        long frames; // offset 0x51C, size 0x4
    } * look; // r0
    struct {
        // total size: 0x460
        int partitions; // offset 0x0, size 0x4
        int partitionclass[31]; // offset 0x4, size 0x7C
        int class_dim[16]; // offset 0x80, size 0x40
        int class_subs[16]; // offset 0xC0, size 0x40
        int class_book[16]; // offset 0x100, size 0x40
        int class_subbook[16][8]; // offset 0x140, size 0x200
        int mult; // offset 0x340, size 0x4
        int postlist[65]; // offset 0x344, size 0x104
        float maxover; // offset 0x448, size 0x4
        float maxunder; // offset 0x44C, size 0x4
        float maxerr; // offset 0x450, size 0x4
        float twofitweight; // offset 0x454, size 0x4
        float twofitatten; // offset 0x458, size 0x4
        int n; // offset 0x45C, size 0x4
    } * info; // r31
    int n; // r27
    int j; // r26
    int * fit_value; // r0
    int hx; // r25
    int lx; // r3
    int ly; // r5
    int current; // r0
    int hy; // r24

    // References
    // -> static float FLOOR1_fromdB_LOOKUP[256];
}

struct {
    // total size: 0x1C
    void (* pack)(void *, struct {
        // total size: 0x14
        long endbyte; // offset 0x0, size 0x4
        int endbit; // offset 0x4, size 0x4
        unsigned char * buffer; // offset 0x8, size 0x4
        unsigned char * ptr; // offset 0xC, size 0x4
        long storage; // offset 0x10, size 0x4
    } *); // offset 0x0, size 0x4
    void * (* unpack)(struct vorbis_info *, struct {
        // total size: 0x14
        long endbyte; // offset 0x0, size 0x4
        int endbit; // offset 0x4, size 0x4
        unsigned char * buffer; // offset 0x8, size 0x4
        unsigned char * ptr; // offset 0xC, size 0x4
        long storage; // offset 0x10, size 0x4
    } *); // offset 0x4, size 0x4
    void * (* look)(struct vorbis_dsp_state *, void *); // offset 0x8, size 0x4
    void (* free_info)(void *); // offset 0xC, size 0x4
    void (* free_look)(void *); // offset 0x10, size 0x4
    void * (* inverse1)(struct vorbis_block *, void *); // offset 0x14, size 0x4
    int (* inverse2)(struct vorbis_block *, void *, void *, float *); // offset 0x18, size 0x4
} floor1_exportbundle; // size: 0x1C, address: 0x80908B90

