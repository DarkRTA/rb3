/*
    Compile unit: C:\rockband2\system\src\oggvorbis\mapping0.c
    Producer: MW EABI PPC C-Compiler
    Language: C89
    Code range: 0x805441E0 -> 0x80545400
*/
struct vorbis_info_mapping0 {
    // total size: 0xC88
    int submaps; // offset 0x0, size 0x4
    int chmuxlist[256]; // offset 0x4, size 0x400
    int floorsubmap[16]; // offset 0x404, size 0x40
    int residuesubmap[16]; // offset 0x444, size 0x40
    int coupling_steps; // offset 0x484, size 0x4
    int coupling_mag[256]; // offset 0x488, size 0x400
    int coupling_ang[256]; // offset 0x888, size 0x400
};
// Range: 0x805441E0 -> 0x80544224
static void mapping0_free_info() {
    // Local variables
    struct vorbis_info_mapping0 * info; // r31
}

// Range: 0x80544224 -> 0x80544250
static int ilog() {
    // Local variables
    int ret; // r4
}

// Range: 0x80544250 -> 0x80544404
static void mapping0_pack(struct vorbis_info * vi /* r27 */, void * vm /* r30 */, struct {
    // total size: 0x14
    long endbyte; // offset 0x0, size 0x4
    int endbit; // offset 0x4, size 0x4
    unsigned char * buffer; // offset 0x8, size 0x4
    unsigned char * ptr; // offset 0xC, size 0x4
    long storage; // offset 0x10, size 0x4
} * opb /* r31 */) {
    // Local variables
    int i; // r28
    struct vorbis_info_mapping0 * info; // r0
}

// Range: 0x80544404 -> 0x80544614
static void * mapping0_unpack(struct vorbis_info * vi /* r27 */, struct {
    // total size: 0x14
    long endbyte; // offset 0x0, size 0x4
    int endbit; // offset 0x4, size 0x4
    unsigned char * buffer; // offset 0x8, size 0x4
    unsigned char * ptr; // offset 0xC, size 0x4
    long storage; // offset 0x10, size 0x4
} * opb /* r28 */) {
    // Local variables
    int i; // r31
    struct vorbis_info_mapping0 * info; // r30
    struct codec_setup_info * ci; // r29
    int testM; // r0
    int testA; // r0
}

// Range: 0x80544614 -> 0x80544FF4
static int mapping0_forward(struct vorbis_block * vb /* r16 */) {
    // Local variables
    struct vorbis_info * vi; // r27
    struct codec_setup_info * ci; // cr2
    struct private_state * b; // r26
    struct vorbis_block_internal * vbi; // cr0
    int n; // r25
    int i; // r24
    int j; // r14
    int k; // r23
    int * nonzero; // r22
    float * * gmdct; // f30
    int * * ilogmaskch; // f29
    int * * * floor_posts; // r0
    float global_ampmax; // f31
    float * local_ampmax; // r17
    int blocktype; // r4
    int modenumber; // f25
    struct vorbis_info_mapping0 * info; // r21
    struct {
        // total size: 0x30
        int n; // offset 0x0, size 0x4
        struct vorbis_info_psy * vi; // offset 0x4, size 0x4
        float * * * tonecurves; // offset 0x8, size 0x4
        float * * noiseoffset; // offset 0xC, size 0x4
        float * ath; // offset 0x10, size 0x4
        long * octave; // offset 0x14, size 0x4
        long * bark; // offset 0x18, size 0x4
        long firstoc; // offset 0x1C, size 0x4
        long shiftoc; // offset 0x20, size 0x4
        int eighth_octave_lines; // offset 0x24, size 0x4
        int total_octave_lines; // offset 0x28, size 0x4
        long rate; // offset 0x2C, size 0x4
    } * psy_look; // f23
    float scale; // r31+0x14
    float scale_dB; // f0
    float * pcm; // r18
    float * logfft; // r0
    float temp; // r31+0x10
    float * noise; // f20
    float * tone; // r30
    int submap; // f18
    float * mdct; // r18
    float * logfft; // r19
    float * logmdct; // r20
    float * * res_bundle; // r20
    float * * couple_bundle; // r19
    int * zerobundle; // r18
    int * * sortindex; // f11
    float * * mag_memo; // f10
    int * * mag_sort; // f9
    float * mdct; // r0
    int submap; // f7
    float * mdct; // f6
    float * res; // r17
    int * ilogmask; // r30
    int ch_in_bundle; // r17
    long * * classifications; // r0
    int resnum; // r0

    // References
    // -> struct [anonymous] * _residue_P[3];
}

// Range: 0x80544FF4 -> 0x80545400
static int mapping0_inverse(struct vorbis_block * vb /* r19 */, void * l /* r20 */) {
    // Local variables
    struct vorbis_dsp_state * vd; // r4
    struct vorbis_info * vi; // r28
    struct codec_setup_info * ci; // r27
    struct private_state * b; // r26
    struct vorbis_info_mapping0 * info; // r0
    int i; // r25
    int j; // r3
    long n; // r0
    float * * pcmbundle; // r24
    int * zerobundle; // r23
    int * nonzero; // r22
    void * floormemo; // r21
    int submap; // r0
    int ch_in_bundle; // r7
    float * pcmM; // r5
    float * pcmA; // r4
    float mag; // f1
    float ang; // f2
    int submap; // r3
    float * pcm; // r4

    // References
    // -> struct [anonymous] * _residue_P[3];
    // -> struct [anonymous] * _floor_P[2];
}

struct {
    // total size: 0x14
    void (* pack)(struct vorbis_info *, void *, struct {
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
    void (* free_info)(void *); // offset 0x8, size 0x4
    int (* forward)(struct vorbis_block *); // offset 0xC, size 0x4
    int (* inverse)(struct vorbis_block *, void *); // offset 0x10, size 0x4
} mapping0_exportbundle; // size: 0x14, address: 0x80909458

