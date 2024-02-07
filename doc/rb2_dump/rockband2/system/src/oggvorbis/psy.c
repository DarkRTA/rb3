/*
    Compile unit: C:\rockband2\system\src\oggvorbis\psy.c
    Producer: MW EABI PPC C-Compiler
    Language: C89
    Code range: 0x805466F4 -> 0x80549370
*/
static float ATH[88]; // size: 0x160, address: 0x80909470
static float tonemasks[17][6][56]; // size: 0x5940, address: 0x809095D0
static double stereo_threshholds[9]; // size: 0x48, address: 0x8090EF10
// Range: 0x805466F4 -> 0x80546738
void _vp_global_free(struct {
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
} * look /* r31 */) {}

// Range: 0x80546738 -> 0x8054677C
void _vi_psy_free(struct vorbis_info_psy * i /* r31 */) {}

// Range: 0x8054677C -> 0x805467AC
static void min_curve() {
    // Local variables
    int i; // r5
}

// Range: 0x805467AC -> 0x805467DC
static void max_curve() {
    // Local variables
    int i; // r5
}

// Range: 0x805467DC -> 0x80546804
static void attenuate_curve() {
    // Local variables
    int i; // r4
}

// Range: 0x80546804 -> 0x8054721C
static float * * * setup_tone_curves(float * curveatt_dB /* r17 */, float binHz /* f29 */, int n /* r30 */, float center_boost /* f30 */, float center_decay_rate /* f31 */) {
    // Local variables
    int i; // r25
    int j; // r24
    int k; // r23
    int m; // r22
    float ath[56]; // r31+0x8
    float workc[17][8][56]; // r31+0x810
    float athc[8][56]; // r31+0xE8
    float * brute_buffer; // r21
    float * * * ret; // r20
    int ath_offset; // r4
    float min; // f1
    float adj; // f1
    int hi_curve; // r19
    int lo_curve; // r18
    int bin; // r17
    int l; // r29
    int lo_bin; // r17
    int hi_bin; // r7
    int l; // r17
    int lo_bin; // r23
    int hi_bin; // r7
    int bin; // r0

    // References
    // -> static float tonemasks[17][6][56];
    // -> static float ATH[88];
}

// Range: 0x8054721C -> 0x805479C8
void _vp_psy_init(struct {
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
} * p /* r22 */, struct vorbis_info_psy * vi /* r23 */, struct {
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
} * gi /* r28 */, int n /* r24 */, long rate /* r25 */) {
    // Local variables
    long i; // r29
    long j; // r28
    long lo; // r27
    long hi; // r26
    long maxoc; // r3
    int endpos; // r4
    float base; // f3
    float delta; // f1
    float bark; // f31
    float halfoc; // f2
    int inthalfoc; // r4
    float del; // f3

    // References
    // -> static float ATH[88];
}

// Range: 0x805479C8 -> 0x80547AE4
void _vp_psy_clear(struct {
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
} * p /* r29 */) {
    // Local variables
    int i; // r31
    int j; // r30
}

// Range: 0x80547AE4 -> 0x80547C08
static void seed_curve() {
    // Local variables
    int i; // r4
    int post1; // r8
    int seedptr; // r5
    const float * posts; // r4
    const float * curve; // r9
    int choice; // r8
    float lin; // f2
}

// Range: 0x80547C08 -> 0x80547D20
static void seed_loop(struct {
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
} * p /* r27 */, const float * * * curves /* r28 */, const float * f /* r29 */, const float * flr /* r30 */, float * seed /* r31 */) {
    // Local variables
    long n; // r26
    long i; // r25
    float dBoffset; // f31
    float max; // f1
    long oc; // r4
}

// Range: 0x80547D20 -> 0x80547EC0
static void seed_chase() {
    // Local variables
    long * posstack; // r10
    float * ampstack; // r11
    long stack; // r12
    long pos; // r30
    long i; // r29
    long endpos; // r6
}

// Range: 0x80547EC0 -> 0x80548030
static void max_seeds(struct {
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
} * p /* r28 */, float * seed /* r29 */, float * flr /* r30 */) {
    // Local variables
    int linesper; // r27
    long linpos; // r31
    long pos; // r6
    float minV; // f2
    long end; // r7
    float minV; // f1
}

// Range: 0x80548030 -> 0x8054849C
static void bark_noise_hybridmp() {
    // Local variables
    float * N; // r8
    float * X; // r9
    float * XX; // r10
    float * Y; // r11
    float * XY; // r12
    float tN; // f0
    float tX; // f2
    float tXX; // f3
    float tY; // f9
    float tXY; // f10
    int i; // r30
    int lo; // r29
    int hi; // r28
    float R; // f2
    float A; // f4
    float B; // f5
    float D; // f6
    float w; // f11
    float x; // f7
    float y; // f12
}

static float FLOOR1_fromdB_INV_LOOKUP[256]; // size: 0x400, address: 0x8090EF58
// Range: 0x8054849C -> 0x80548504
void _vp_remove_floor() {
    // Local variables
    int i; // r9
    int n; // r10

    // References
    // -> static float FLOOR1_fromdB_INV_LOOKUP[256];
}

// Range: 0x80548504 -> 0x8054865C
void _vp_noisemask(struct {
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
} * p /* r29 */, float * logmdct /* r26 */, float * logmask /* r30 */) {
    // Local variables
    int i; // r6
    int n; // r28
    float * work; // r27
    int dB; // r0
}

// Range: 0x8054865C -> 0x80548764
void _vp_tonemask(struct {
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
} * p /* r28 */, float * logfft /* r8 */, float * logmask /* r29 */) {
    // Local variables
    int i; // r6
    int n; // r7
    float * seed; // r30
    float att; // f2
}

// Range: 0x80548764 -> 0x805487D8
void _vp_offset_and_mix() {
    // Local variables
    int i; // r9
    int n; // r10
    float toneatt; // f2
    float val; // f1
}

// Range: 0x805487D8 -> 0x805488C4
static void couple_lossless() {
    // Local variables
    int test1; // r5
    float temp; // f1
}

static float hypot_lookup[32]; // size: 0x80, address: 0x8090F358
// Range: 0x805488C4 -> 0x80548948
static void precomputed_couple_point() {
    // Local variables
    int test; // r8
    int offset; // r9
    float floormag; // f2

    // References
    // -> static float FLOOR1_fromdB_INV_LOOKUP[256];
    // -> static float hypot_lookup[32];
}

// Range: 0x80548948 -> 0x80548A1C
static float dipole_hypot() {}

// Range: 0x80548A1C -> 0x80548AF0
static float round_hypot() {}

// Range: 0x80548AF0 -> 0x80548BF8
float * * _vp_quantize_couple_memo(struct vorbis_block * vb /* r25 */, struct {
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
} * g /* r21 */, struct {
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
} * p /* r20 */, struct vorbis_info_mapping0 * vi /* r26 */, float * * mdct /* r27 */) {
    // Local variables
    int i; // r31
    int j; // r22
    int n; // r30
    float * * ret; // r29
    int limit; // r28
    float * mdctM; // r21
    float * mdctA; // r20
}

// Range: 0x80548BF8 -> 0x80548C34
static int apsort() {
    // Local variables
    float f1; // f1
    float f2; // f0
}

// Range: 0x80548C34 -> 0x80548D90
int * * _vp_quantize_couple_sort(struct vorbis_block * vb /* r21 */, struct {
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
} * p /* r24 */, struct vorbis_info_mapping0 * vi /* r22 */, float * * mags /* r23 */) {
    // Local variables
    int i; // r29
    int j; // r28
    int k; // r5
    int n; // r27
    int * * ret; // r26
    int partition; // r25
    float * * work; // r24
}

// Range: 0x80548D90 -> 0x80548E94
void _vp_noise_normalize_sort(float * magnitudes /* r24 */, int * sortedindex /* r25 */) {
    // Local variables
    int i; // r5
    int j; // r30
    int n; // r29
    struct vorbis_info_psy * vi; // r3
    int partition; // r28
    float * * work; // r27
    int start; // r26
}

// Range: 0x80548E94 -> 0x80549030
void _vp_noise_normalize(float * in /* r23 */, float * out /* r24 */, int * sortedindex /* r25 */) {
    // Local variables
    int i; // r31
    int j; // r30
    int n; // r29
    struct vorbis_info_psy * vi; // r28
    int partition; // r27
    int start; // r26
    float acc; // f31
    int k; // r0
}

// Range: 0x80549030 -> 0x80549370
void _vp_couple(int blobno /* f0 */, struct {
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
} * g /* f1 */, struct {
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
} * p /* r15 */, struct vorbis_info_mapping0 * vi /* f3 */, float * * res /* f4 */, float * * mag_memo /* r16 */, int * * mag_sort /* r17 */, int * * ifloor /* f7 */, int * nonzero /* f8 */, int sliding_lowpass /* r18 */) {
    // Local variables
    int i; // r14
    int j; // r29
    int k; // r28
    int n; // f21
    float * rM; // r27
    float * rA; // r26
    float * qM; // r25
    float * qA; // r24
    int * floorM; // r23
    int * floorA; // r22
    float prepoint; // f31
    float postpoint; // f30
    int partition; // r21
    int limit; // r20
    int pointlimit; // r0
    float acc; // f29
    int l; // r19
    int l; // r19

    // References
    // -> static double stereo_threshholds[9];
}


