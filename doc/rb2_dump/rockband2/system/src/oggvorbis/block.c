/*
    Compile unit: C:\rockband2\system\src\oggvorbis\block.c
    Producer: MW EABI PPC C-Compiler
    Language: C89
    Code range: 0x8053E40C -> 0x8053F514
*/
// Range: 0x8053E40C -> 0x8053E438
static int ilog2() {
    // Local variables
    int ret; // r4
}

// Range: 0x8053E438 -> 0x8053E4C8
int vorbis_block_init(struct vorbis_dsp_state * v /* r31 */, struct vorbis_block * vb /* r30 */) {
    // Local variables
    struct vorbis_block_internal * vbi; // r0
}

// Range: 0x8053E4C8 -> 0x8053E578
void * _vorbis_block_alloc(struct vorbis_block * vb /* r30 */, long bytes /* r31 */) {
    // Local variables
    struct alloc_chain * link; // r0
    void * ret; // r0
}

// Range: 0x8053E578 -> 0x8053E62C
void _vorbis_block_ripcord(struct vorbis_block * vb /* r29 */) {
    // Local variables
    struct alloc_chain * reap; // r31
    struct alloc_chain * next; // r30
}

// Range: 0x8053E62C -> 0x8053E6B0
int vorbis_block_clear(struct vorbis_block * vb /* r31 */) {}

struct private_state {
    // total size: 0xC0
    struct {
        // total size: 0xB8
        int ch; // offset 0x0, size 0x4
        int winlength; // offset 0x4, size 0x4
        int searchstep; // offset 0x8, size 0x4
        float minenergy; // offset 0xC, size 0x4
        struct {
            // total size: 0x18
            int n; // offset 0x0, size 0x4
            int log2n; // offset 0x4, size 0x4
            float * trig; // offset 0x8, size 0x4
            float * trig2; // offset 0xC, size 0x4
            int * bitrev; // offset 0x10, size 0x4
            float scale; // offset 0x14, size 0x4
        } mdct; // offset 0x10, size 0x18
        float * mdct_win; // offset 0x28, size 0x4
        struct {
            // total size: 0x10
            int begin; // offset 0x0, size 0x4
            int end; // offset 0x4, size 0x4
            float * window; // offset 0x8, size 0x4
            float total; // offset 0xC, size 0x4
        } band[7]; // offset 0x2C, size 0x70
        struct {
            // total size: 0x90
            float ampbuf[17]; // offset 0x0, size 0x44
            int ampptr; // offset 0x44, size 0x4
            float nearDC[15]; // offset 0x48, size 0x3C
            float nearDC_acc; // offset 0x84, size 0x4
            float nearDC_partialacc; // offset 0x88, size 0x4
            int nearptr; // offset 0x8C, size 0x4
        } * filter; // offset 0x9C, size 0x4
        int stretch; // offset 0xA0, size 0x4
        int * mark; // offset 0xA4, size 0x4
        long storage; // offset 0xA8, size 0x4
        long current; // offset 0xAC, size 0x4
        long curmark; // offset 0xB0, size 0x4
        long cursor; // offset 0xB4, size 0x4
    } * ve; // offset 0x0, size 0x4
    int window[2]; // offset 0x4, size 0x8
    void * transform[2]; // offset 0xC, size 0x8
    struct {
        // total size: 0xC
        int n; // offset 0x0, size 0x4
        float * trigcache; // offset 0x4, size 0x4
        int * splitcache; // offset 0x8, size 0x4
    } fft_look[2]; // offset 0x14, size 0x18
    int modebits; // offset 0x2C, size 0x4
    void * flr; // offset 0x30, size 0x4
    void * residue; // offset 0x34, size 0x4
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
    } * psy; // offset 0x38, size 0x4
    struct {
        // total size: 0x24
        float ampmax; // offset 0x0, size 0x4
        int channels; // offset 0x4, size 0x4
        struct {
            // total size: 0x1EC
            int eighth_octave_lines; // offset 0x0, size 0x4
            float preecho_thresh[7]; // offset 0x4, size 0x1C
            float postecho_thresh[7]; // offset 0x20, size 0x1C
            float stretch_penalty; // offset 0x3C, size 0x4
            float preecho_minenergy; // offset 0x40, size 0x4
            float ampmax_att_per_sec; // offset 0x44, size 0x4
            int coupling_pkHz[15]; // offset 0x48, size 0x3C
            int coupling_pointlimit[2][15]; // offset 0x84, size 0x78
            int coupling_prepointamp[15]; // offset 0xFC, size 0x3C
            int coupling_postpointamp[15]; // offset 0x138, size 0x3C
            int sliding_lowpass[2][15]; // offset 0x174, size 0x78
        } * gi; // offset 0x8, size 0x4
        int coupling_pointlimit[2][3]; // offset 0xC, size 0x18
    } * psy_g_look; // offset 0x3C, size 0x4
    unsigned char * header; // offset 0x40, size 0x4
    unsigned char * header1; // offset 0x44, size 0x4
    unsigned char * header2; // offset 0x48, size 0x4
    struct bitrate_manager_state bms; // offset 0x50, size 0x68
    long long sample_count; // offset 0xB8, size 0x8
};
// Range: 0x8053E6B0 -> 0x8053EA40
static int _vds_shared_init(struct vorbis_dsp_state * v /* r27 */, struct vorbis_info * vi /* r28 */, int encp /* r30 */) {
    // Local variables
    int i; // r30
    struct codec_setup_info * ci; // r29
    struct private_state * b; // r0
    int hs; // r26
    int i; // r26

    // References
    // -> struct [anonymous] * _residue_P[3];
    // -> struct [anonymous] * _floor_P[2];
}

// Range: 0x8053EA40 -> 0x8053ECC4
void vorbis_dsp_clear(struct vorbis_dsp_state * v /* r27 */) {
    // Local variables
    int i; // r31
    struct vorbis_info * vi; // r30
    struct codec_setup_info * ci; // r29
    struct private_state * b; // r28

    // References
    // -> struct [anonymous] * _residue_P[3];
    // -> struct [anonymous] * _floor_P[2];
}

// Range: 0x8053ECC4 -> 0x8053ED4C
int vorbis_synthesis_restart() {
    // Local variables
    struct vorbis_info * vi; // r4
    struct codec_setup_info * ci; // r4
    int hs; // r6
}

// Range: 0x8053ED4C -> 0x8053ED98
int vorbis_synthesis_init(struct vorbis_dsp_state * v /* r31 */) {}

// Range: 0x8053ED98 -> 0x8053F460
int vorbis_synthesis_blockin(struct vorbis_dsp_state * v /* r20 */, struct vorbis_block * vb /* r21 */) {
    // Local variables
    struct vorbis_info * vi; // r31
    struct codec_setup_info * ci; // r30
    struct private_state * b; // r29
    int hs; // r28
    int i; // r6
    int j; // r27
    int n; // r26
    int n0; // r25
    int n1; // r24
    int thisCenter; // r23
    int prevCenter; // r22
    float * w; // r0
    float * pcm; // r7
    float * p; // r8
    float * w; // r0
    float * pcm; // r7
    float * p; // r8
    float * w; // r0
    float * pcm; // r7
    float * p; // r10
    float * w; // r0
    float * pcm; // r7
    float * p; // r8
    float * pcm; // r5
    float * p; // r3
    long extra; // r0
}

// Range: 0x8053F460 -> 0x8053F4DC
int vorbis_synthesis_pcmout() {
    // Local variables
    struct vorbis_info * vi; // r7
    int i; // r8
}

// Range: 0x8053F4DC -> 0x8053F514
int vorbis_synthesis_read() {}


