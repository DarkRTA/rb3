/*
    Compile unit: C:\rockband2\system\src\oggvorbis\res0.c
    Producer: MW EABI PPC C-Compiler
    Language: C89
    Code range: 0x80549394 -> 0x8054A940
*/
struct vorbis_info_residue0 {
    // total size: 0x714
    long begin; // offset 0x0, size 0x4
    long end; // offset 0x4, size 0x4
    int grouping; // offset 0x8, size 0x4
    int partitions; // offset 0xC, size 0x4
    int groupbook; // offset 0x10, size 0x4
    int secondstages[64]; // offset 0x14, size 0x100
    int booklist[256]; // offset 0x114, size 0x400
    float classmetric1[64]; // offset 0x514, size 0x100
    float classmetric2[64]; // offset 0x614, size 0x100
};
// Range: 0x80549394 -> 0x805493D8
void res0_free_info() {
    // Local variables
    struct vorbis_info_residue0 * info; // r31
}

// Range: 0x805493D8 -> 0x80549490
void res0_free_look(void * i /* r30 */) {
    // Local variables
    int j; // r31
    struct {
        // total size: 0x2C
        struct vorbis_info_residue0 * info; // offset 0x0, size 0x4
        int parts; // offset 0x4, size 0x4
        int stages; // offset 0x8, size 0x4
        struct codebook * fullbooks; // offset 0xC, size 0x4
        struct codebook * phrasebook; // offset 0x10, size 0x4
        struct codebook * * * partbooks; // offset 0x14, size 0x4
        int partvals; // offset 0x18, size 0x4
        int * * decodemap; // offset 0x1C, size 0x4
        long postbits; // offset 0x20, size 0x4
        long phrasebits; // offset 0x24, size 0x4
        long frames; // offset 0x28, size 0x4
    } * look; // [invalid]
}

// Range: 0x80549490 -> 0x805494B0
static int ilog() {
    // Local variables
    int ret; // r4
}

// Range: 0x805494B0 -> 0x805494D4
static int icount() {
    // Local variables
    int ret; // r4
}

// Range: 0x805494D4 -> 0x8054961C
void res0_pack(void * vr /* r26 */, struct {
    // total size: 0x14
    long endbyte; // offset 0x0, size 0x4
    int endbit; // offset 0x4, size 0x4
    unsigned char * buffer; // offset 0x8, size 0x4
    unsigned char * ptr; // offset 0xC, size 0x4
    long storage; // offset 0x10, size 0x4
} * opb /* r27 */) {
    // Local variables
    struct vorbis_info_residue0 * info; // r0
    int j; // r29
    int acc; // r28
}

// Range: 0x8054961C -> 0x805497A0
void * res0_unpack(struct vorbis_info * vi /* r27 */, struct {
    // total size: 0x14
    long endbyte; // offset 0x0, size 0x4
    int endbit; // offset 0x4, size 0x4
    unsigned char * buffer; // offset 0x8, size 0x4
    unsigned char * ptr; // offset 0xC, size 0x4
    long storage; // offset 0x10, size 0x4
} * opb /* r26 */) {
    // Local variables
    int j; // r31
    int acc; // r30
    struct vorbis_info_residue0 * info; // r29
    struct codec_setup_info * ci; // r28
    int cascade; // r27
}

// Range: 0x805497A0 -> 0x805499A8
void * res0_look(struct vorbis_dsp_state * vd /* r23 */, void * vr /* r22 */) {
    // Local variables
    struct vorbis_info_residue0 * info; // r0
    struct {
        // total size: 0x2C
        struct vorbis_info_residue0 * info; // offset 0x0, size 0x4
        int parts; // offset 0x4, size 0x4
        int stages; // offset 0x8, size 0x4
        struct codebook * fullbooks; // offset 0xC, size 0x4
        struct codebook * phrasebook; // offset 0x10, size 0x4
        struct codebook * * * partbooks; // offset 0x14, size 0x4
        int partvals; // offset 0x18, size 0x4
        int * * decodemap; // offset 0x1C, size 0x4
        long postbits; // offset 0x20, size 0x4
        long phrasebits; // offset 0x24, size 0x4
        long frames; // offset 0x28, size 0x4
    } * look; // r29
    struct codec_setup_info * ci; // r28
    int j; // r27
    int k; // r3
    int acc; // r26
    int dim; // r25
    int maxstage; // r24
    int stages; // r23
    long val; // r23
    long mult; // r24
    long deco; // r5
}

// Range: 0x805499A8 -> 0x80549B68
static int local_book_besterror() {
    // Local variables
    int dim; // r0
    int i; // r10
    int k; // r11
    int o; // r12
    int best; // r6
    struct encode_aux_threshmatch * tt; // r31
    float val; // f1
    const struct static_codebook * c; // r0
    int i; // r9
    int j; // r8
    float bestf; // f2
    float * e; // r10
    float this; // f3
    float val; // f0
    float * ptr; // r3
}

// Range: 0x80549B68 -> 0x80549BEC
static int _encodepart(struct {
    // total size: 0x14
    long endbyte; // offset 0x0, size 0x4
    int endbit; // offset 0x4, size 0x4
    unsigned char * buffer; // offset 0x8, size 0x4
    unsigned char * ptr; // offset 0xC, size 0x4
    long storage; // offset 0x10, size 0x4
} * opb /* r25 */, float * vec /* r26 */, struct codebook * book /* r27 */) {
    // Local variables
    int i; // r31
    int bits; // r30
    int dim; // r29
    int step; // r28
    int entry; // r0
}

// Range: 0x80549BEC -> 0x80549E0C
static long * * _01class(struct vorbis_block * vb /* r23 */, void * vl /* r20 */, float * * in /* r21 */, int ch /* r22 */) {
    // Local variables
    long i; // r30
    long j; // r29
    long k; // r28
    struct {
        // total size: 0x2C
        struct vorbis_info_residue0 * info; // offset 0x0, size 0x4
        int parts; // offset 0x4, size 0x4
        int stages; // offset 0x8, size 0x4
        struct codebook * fullbooks; // offset 0xC, size 0x4
        struct codebook * phrasebook; // offset 0x10, size 0x4
        struct codebook * * * partbooks; // offset 0x14, size 0x4
        int partvals; // offset 0x18, size 0x4
        int * * decodemap; // offset 0x1C, size 0x4
        long postbits; // offset 0x20, size 0x4
        long phrasebits; // offset 0x24, size 0x4
        long frames; // offset 0x28, size 0x4
    } * look; // r0
    struct vorbis_info_residue0 * info; // r27
    int samples_per_partition; // r26
    int possible_partitions; // r25
    int n; // r28
    int partvals; // r0
    long * * partword; // r24
    float scale; // f31
    int offset; // r23
    float max; // f30
    float ent; // f29
}

// Range: 0x80549E0C -> 0x80549F7C
static long * * _2class(struct vorbis_block * vb /* r22 */, void * vl /* r24 */, float * * in /* r25 */, int ch /* r26 */) {
    // Local variables
    long i; // r4
    long j; // r5
    long k; // r6
    long l; // r7
    struct {
        // total size: 0x2C
        struct vorbis_info_residue0 * info; // offset 0x0, size 0x4
        int parts; // offset 0x4, size 0x4
        int stages; // offset 0x8, size 0x4
        struct codebook * fullbooks; // offset 0xC, size 0x4
        struct codebook * phrasebook; // offset 0x10, size 0x4
        struct codebook * * * partbooks; // offset 0x14, size 0x4
        int partvals; // offset 0x18, size 0x4
        int * * decodemap; // offset 0x1C, size 0x4
        long postbits; // offset 0x20, size 0x4
        long phrasebits; // offset 0x24, size 0x4
        long frames; // offset 0x28, size 0x4
    } * look; // r0
    struct vorbis_info_residue0 * info; // r31
    int samples_per_partition; // r30
    int possible_partitions; // r29
    int n; // r23
    int partvals; // r28
    long * * partword; // r27
    float magmax; // f1
    float angmax; // f2
}

// Range: 0x80549F7C -> 0x8054A1AC
static int _01forward(struct vorbis_block * vb /* r15 */, void * vl /* r16 */, float * * in /* r17 */, int ch /* r18 */, long * * partword /* r19 */, int (* encode)(struct {
    // total size: 0x14
    long endbyte; // offset 0x0, size 0x4
    int endbit; // offset 0x4, size 0x4
    unsigned char * buffer; // offset 0x8, size 0x4
    unsigned char * ptr; // offset 0xC, size 0x4
    long storage; // offset 0x10, size 0x4
} *, float *, int, struct codebook *, long *) /* r20 */) {
    // Local variables
    long i; // r29
    long j; // r28
    long k; // r27
    long s; // r26
    struct {
        // total size: 0x2C
        struct vorbis_info_residue0 * info; // offset 0x0, size 0x4
        int parts; // offset 0x4, size 0x4
        int stages; // offset 0x8, size 0x4
        struct codebook * fullbooks; // offset 0xC, size 0x4
        struct codebook * phrasebook; // offset 0x10, size 0x4
        struct codebook * * * partbooks; // offset 0x14, size 0x4
        int partvals; // offset 0x18, size 0x4
        int * * decodemap; // offset 0x1C, size 0x4
        long postbits; // offset 0x20, size 0x4
        long phrasebits; // offset 0x24, size 0x4
        long frames; // offset 0x28, size 0x4
    } * look; // r0
    struct vorbis_info_residue0 * info; // r25
    int samples_per_partition; // r24
    int possible_partitions; // r14
    int partitions_per_word; // r23
    int partvals; // r22
    long resbits[128]; // r1+0x208
    long resvals[128]; // r1+0x8
    long val; // r4
    long offset; // r21
    struct codebook * statebook; // r6
    int ret; // r0
}

// Range: 0x8054A1AC -> 0x8054A3A8
static int _01inverse(struct vorbis_block * vb /* r16 */, void * vl /* r17 */, float * * in /* r18 */, int ch /* r19 */, long (* decodepart)(struct codebook *, float *, struct {
    // total size: 0x14
    long endbyte; // offset 0x0, size 0x4
    int endbit; // offset 0x4, size 0x4
    unsigned char * buffer; // offset 0x8, size 0x4
    unsigned char * ptr; // offset 0xC, size 0x4
    long storage; // offset 0x10, size 0x4
} *, int) /* r20 */) {
    // Local variables
    long i; // r30
    long j; // r29
    long k; // r28
    long l; // r27
    long s; // r26
    struct {
        // total size: 0x2C
        struct vorbis_info_residue0 * info; // offset 0x0, size 0x4
        int parts; // offset 0x4, size 0x4
        int stages; // offset 0x8, size 0x4
        struct codebook * fullbooks; // offset 0xC, size 0x4
        struct codebook * phrasebook; // offset 0x10, size 0x4
        struct codebook * * * partbooks; // offset 0x14, size 0x4
        int partvals; // offset 0x18, size 0x4
        int * * decodemap; // offset 0x1C, size 0x4
        long postbits; // offset 0x20, size 0x4
        long phrasebits; // offset 0x24, size 0x4
        long frames; // offset 0x28, size 0x4
    } * look; // r0
    struct vorbis_info_residue0 * info; // r25
    int samples_per_partition; // r24
    int partitions_per_word; // r23
    int partvals; // r22
    int partwords; // r26
    int * * * partword; // r21
    int temp; // r0
    long offset; // r0
    struct codebook * stagebook; // r3
}

// Range: 0x8054A3A8 -> 0x8054A400
int res0_inverse() {
    // Local variables
    int i; // r9
    int used; // r10
}

// Range: 0x8054A400 -> 0x8054A550
int res1_forward(float * * in /* r27 */, float * * out /* r28 */, int * nonzero /* r29 */, int ch /* r30 */) {
    // Local variables
    int i; // r10
    int j; // r24
    int used; // r11
    int n; // r31
    int ret; // r3
}

// Range: 0x8054A550 -> 0x8054A5A0
long * * res1_class() {
    // Local variables
    int i; // r9
    int used; // r10
}

// Range: 0x8054A5A0 -> 0x8054A5F8
int res1_inverse() {
    // Local variables
    int i; // r9
    int used; // r10
}

// Range: 0x8054A5F8 -> 0x8054A63C
long * * res2_class() {
    // Local variables
    int i; // r8
    int used; // r9
}

// Range: 0x8054A63C -> 0x8054A79C
int res2_forward(struct vorbis_block * vb /* r23 */, void * vl /* r24 */, float * * in /* r25 */, float * * out /* r26 */, int * nonzero /* r27 */, int ch /* r28 */, long * * partword /* r29 */) {
    // Local variables
    long i; // r6
    long j; // r7
    long k; // r8
    long n; // r31
    long used; // r30
    float * work; // r1+0x8
    float * pcm; // r4
    int ret; // r3
    float * pcm; // r9
    float * sofar; // r10
}

// Range: 0x8054A79C -> 0x8054A940
int res2_inverse(struct vorbis_block * vb /* r19 */, void * vl /* r20 */, float * * in /* r21 */, int * nonzero /* r27 */, int ch /* r22 */) {
    // Local variables
    long i; // r30
    long k; // r29
    long l; // r28
    long s; // r27
    struct {
        // total size: 0x2C
        struct vorbis_info_residue0 * info; // offset 0x0, size 0x4
        int parts; // offset 0x4, size 0x4
        int stages; // offset 0x8, size 0x4
        struct codebook * fullbooks; // offset 0xC, size 0x4
        struct codebook * phrasebook; // offset 0x10, size 0x4
        struct codebook * * * partbooks; // offset 0x14, size 0x4
        int partvals; // offset 0x18, size 0x4
        int * * decodemap; // offset 0x1C, size 0x4
        long postbits; // offset 0x20, size 0x4
        long phrasebits; // offset 0x24, size 0x4
        long frames; // offset 0x28, size 0x4
    } * look; // r0
    struct vorbis_info_residue0 * info; // r26
    int samples_per_partition; // r25
    int partitions_per_word; // r24
    int partvals; // r23
    int * * partword; // r0
    int temp; // r0
    struct codebook * stagebook; // r3
}

struct {
    // total size: 0x20
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
    long * * (* class)(struct vorbis_block *, void *, float * *, int *, int); // offset 0x14, size 0x4
    int (* forward)(struct vorbis_block *, void *, float * *, float * *, int *, int, long * *); // offset 0x18, size 0x4
    int (* inverse)(struct vorbis_block *, void *, float * *, int *, int); // offset 0x1C, size 0x4
} residue0_exportbundle; // size: 0x20, address: 0x8090F3F0
struct {
    // total size: 0x20
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
    long * * (* class)(struct vorbis_block *, void *, float * *, int *, int); // offset 0x14, size 0x4
    int (* forward)(struct vorbis_block *, void *, float * *, float * *, int *, int, long * *); // offset 0x18, size 0x4
    int (* inverse)(struct vorbis_block *, void *, float * *, int *, int); // offset 0x1C, size 0x4
} residue1_exportbundle; // size: 0x20, address: 0x8090F410
struct {
    // total size: 0x20
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
    long * * (* class)(struct vorbis_block *, void *, float * *, int *, int); // offset 0x14, size 0x4
    int (* forward)(struct vorbis_block *, void *, float * *, float * *, int *, int, long * *); // offset 0x18, size 0x4
    int (* inverse)(struct vorbis_block *, void *, float * *, int *, int); // offset 0x1C, size 0x4
} residue2_exportbundle; // size: 0x20, address: 0x8090F430

