/*
    Compile unit: C:\rockband2\system\src\oggvorbis\bitrate.c
    Producer: MW EABI PPC C-Compiler
    Language: C89
    Code range: 0x8053DE84 -> 0x8053DFA8
*/
struct bitrate_manager_state {
    // total size: 0x68
    unsigned int * queue_binned; // offset 0x0, size 0x4
    unsigned int * queue_actual; // offset 0x4, size 0x4
    int queue_size; // offset 0x8, size 0x4
    int queue_head; // offset 0xC, size 0x4
    int queue_bins; // offset 0x10, size 0x4
    long * avg_binacc; // offset 0x14, size 0x4
    int avg_center; // offset 0x18, size 0x4
    int avg_tail; // offset 0x1C, size 0x4
    unsigned int avg_centeracc; // offset 0x20, size 0x4
    unsigned int avg_sampleacc; // offset 0x24, size 0x4
    unsigned int avg_sampledesired; // offset 0x28, size 0x4
    unsigned int avg_centerdesired; // offset 0x2C, size 0x4
    long * minmax_binstack; // offset 0x30, size 0x4
    long * minmax_posstack; // offset 0x34, size 0x4
    long * minmax_limitstack; // offset 0x38, size 0x4
    long minmax_stackptr; // offset 0x3C, size 0x4
    long minmax_acctotal; // offset 0x40, size 0x4
    int minmax_tail; // offset 0x44, size 0x4
    unsigned int minmax_sampleacc; // offset 0x48, size 0x4
    unsigned int minmax_sampledesired; // offset 0x4C, size 0x4
    int next_to_flush; // offset 0x50, size 0x4
    int last_to_flush; // offset 0x54, size 0x4
    double avgfloat; // offset 0x58, size 0x8
    struct {
        // total size: 0x14
        long endbyte; // offset 0x0, size 0x4
        int endbit; // offset 0x4, size 0x4
        unsigned char * buffer; // offset 0x8, size 0x4
        unsigned char * ptr; // offset 0xC, size 0x4
        long storage; // offset 0x10, size 0x4
    } * packetbuffers; // offset 0x60, size 0x4
    struct {
        // total size: 0x20
        unsigned char * packet; // offset 0x0, size 0x4
        long bytes; // offset 0x4, size 0x4
        long b_o_s; // offset 0x8, size 0x4
        long e_o_s; // offset 0xC, size 0x4
        long long granulepos; // offset 0x10, size 0x8
        long long packetno; // offset 0x18, size 0x8
    } * packets; // offset 0x64, size 0x4
};
struct encode_aux_nearestmatch {
    // total size: 0x18
    long * ptr0; // offset 0x0, size 0x4
    long * ptr1; // offset 0x4, size 0x4
    long * p; // offset 0x8, size 0x4
    long * q; // offset 0xC, size 0x4
    long aux; // offset 0x10, size 0x4
    long alloc; // offset 0x14, size 0x4
};
struct encode_aux_threshmatch {
    // total size: 0x10
    float * quantthresh; // offset 0x0, size 0x4
    long * quantmap; // offset 0x4, size 0x4
    int quantvals; // offset 0x8, size 0x4
    int threshvals; // offset 0xC, size 0x4
};
struct encode_aux_pigeonhole {
    // total size: 0x24
    float min; // offset 0x0, size 0x4
    float del; // offset 0x4, size 0x4
    int mapentries; // offset 0x8, size 0x4
    int quantvals; // offset 0xC, size 0x4
    long * pigeonmap; // offset 0x10, size 0x4
    long fittotal; // offset 0x14, size 0x4
    long * fitlist; // offset 0x18, size 0x4
    long * fitmap; // offset 0x1C, size 0x4
    long * fitlength; // offset 0x20, size 0x4
};
struct static_codebook {
    // total size: 0x34
    long dim; // offset 0x0, size 0x4
    long entries; // offset 0x4, size 0x4
    long * lengthlist; // offset 0x8, size 0x4
    int maptype; // offset 0xC, size 0x4
    long q_min; // offset 0x10, size 0x4
    long q_delta; // offset 0x14, size 0x4
    int q_quant; // offset 0x18, size 0x4
    int q_sequencep; // offset 0x1C, size 0x4
    long * quantlist; // offset 0x20, size 0x4
    struct encode_aux_nearestmatch * nearest_tree; // offset 0x24, size 0x4
    struct encode_aux_threshmatch * thresh_tree; // offset 0x28, size 0x4
    struct encode_aux_pigeonhole * pigeon_tree; // offset 0x2C, size 0x4
    int allocedp; // offset 0x30, size 0x4
};
struct codebook {
    // total size: 0x2C
    long dim; // offset 0x0, size 0x4
    long entries; // offset 0x4, size 0x4
    long used_entries; // offset 0x8, size 0x4
    const struct static_codebook * c; // offset 0xC, size 0x4
    float * valuelist; // offset 0x10, size 0x4
    unsigned int * codelist; // offset 0x14, size 0x4
    int * dec_index; // offset 0x18, size 0x4
    char * dec_codelengths; // offset 0x1C, size 0x4
    unsigned int * dec_firsttable; // offset 0x20, size 0x4
    int dec_firsttablen; // offset 0x24, size 0x4
    int dec_maxlength; // offset 0x28, size 0x4
};
struct vorbis_info_psy {
    // total size: 0x210
    int blockflag; // offset 0x0, size 0x4
    float ath_adjatt; // offset 0x4, size 0x4
    float ath_maxatt; // offset 0x8, size 0x4
    float tone_masteratt[3]; // offset 0xC, size 0xC
    float tone_centerboost; // offset 0x18, size 0x4
    float tone_decay; // offset 0x1C, size 0x4
    float tone_abs_limit; // offset 0x20, size 0x4
    float toneatt[17]; // offset 0x24, size 0x44
    int noisemaskp; // offset 0x68, size 0x4
    float noisemaxsupp; // offset 0x6C, size 0x4
    float noisewindowlo; // offset 0x70, size 0x4
    float noisewindowhi; // offset 0x74, size 0x4
    int noisewindowlomin; // offset 0x78, size 0x4
    int noisewindowhimin; // offset 0x7C, size 0x4
    int noisewindowfixed; // offset 0x80, size 0x4
    float noiseoff[3][17]; // offset 0x84, size 0xCC
    float noisecompand[40]; // offset 0x150, size 0xA0
    float max_curve_dB; // offset 0x1F0, size 0x4
    int normal_channel_p; // offset 0x1F4, size 0x4
    int normal_point_p; // offset 0x1F8, size 0x4
    int normal_start; // offset 0x1FC, size 0x4
    int normal_partition; // offset 0x200, size 0x4
    double normal_thresh; // offset 0x208, size 0x8
};
struct bitrate_manager_info {
    // total size: 0x48
    double queue_avg_time; // offset 0x0, size 0x8
    double queue_avg_center; // offset 0x8, size 0x8
    double queue_minmax_time; // offset 0x10, size 0x8
    double queue_hardmin; // offset 0x18, size 0x8
    double queue_hardmax; // offset 0x20, size 0x8
    double queue_avgmin; // offset 0x28, size 0x8
    double queue_avgmax; // offset 0x30, size 0x8
    double avgfloat_downslew_max; // offset 0x38, size 0x8
    double avgfloat_upslew_max; // offset 0x40, size 0x8
};
struct highlevel_byblocktype {
    // total size: 0x20
    double tone_mask_setting; // offset 0x0, size 0x8
    double tone_peaklimit_setting; // offset 0x8, size 0x8
    double noise_bias_setting; // offset 0x10, size 0x8
    double noise_compand_setting; // offset 0x18, size 0x8
};
struct highlevel_encode_setup {
    // total size: 0x110
    void * setup; // offset 0x0, size 0x4
    int set_in_stone; // offset 0x4, size 0x4
    double base_setting; // offset 0x8, size 0x8
    double long_setting; // offset 0x10, size 0x8
    double short_setting; // offset 0x18, size 0x8
    double impulse_noisetune; // offset 0x20, size 0x8
    int managed; // offset 0x28, size 0x4
    long bitrate_min; // offset 0x2C, size 0x4
    long bitrate_av_lo; // offset 0x30, size 0x4
    long bitrate_av_hi; // offset 0x34, size 0x4
    long bitrate_max; // offset 0x38, size 0x4
    double bitrate_limit_window; // offset 0x40, size 0x8
    double bitrate_av_window; // offset 0x48, size 0x8
    double bitrate_av_window_center; // offset 0x50, size 0x8
    int impulse_block_p; // offset 0x58, size 0x4
    int noise_normalize_p; // offset 0x5C, size 0x4
    double stereo_point_setting; // offset 0x60, size 0x8
    double lowpass_kHz; // offset 0x68, size 0x8
    double ath_floating_dB; // offset 0x70, size 0x8
    double ath_absolute_dB; // offset 0x78, size 0x8
    double amplitude_track_dBpersec; // offset 0x80, size 0x8
    double trigger_setting; // offset 0x88, size 0x8
    struct highlevel_byblocktype block[4]; // offset 0x90, size 0x80
};
struct codec_setup_info {
    // total size: 0xE80
    long blocksizes[2]; // offset 0x0, size 0x8
    int modes; // offset 0x8, size 0x4
    int maps; // offset 0xC, size 0x4
    int floors; // offset 0x10, size 0x4
    int residues; // offset 0x14, size 0x4
    int books; // offset 0x18, size 0x4
    int psys; // offset 0x1C, size 0x4
    struct {
        // total size: 0x10
        int blockflag; // offset 0x0, size 0x4
        int windowtype; // offset 0x4, size 0x4
        int transformtype; // offset 0x8, size 0x4
        int mapping; // offset 0xC, size 0x4
    } * mode_param[64]; // offset 0x20, size 0x100
    int map_type[64]; // offset 0x120, size 0x100
    void * map_param[64]; // offset 0x220, size 0x100
    int floor_type[64]; // offset 0x320, size 0x100
    void * floor_param[64]; // offset 0x420, size 0x100
    int residue_type[64]; // offset 0x520, size 0x100
    void * residue_param[64]; // offset 0x620, size 0x100
    struct static_codebook * book_param[256]; // offset 0x720, size 0x400
    struct codebook * fullbooks; // offset 0xB20, size 0x4
    struct vorbis_info_psy * psy_param[4]; // offset 0xB24, size 0x10
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
    } psy_g_param; // offset 0xB34, size 0x1EC
    struct bitrate_manager_info bi; // offset 0xD20, size 0x48
    struct highlevel_encode_setup hi; // offset 0xD68, size 0x110
    int halfrate_flag; // offset 0xE78, size 0x4
};
// Range: 0x8053DE84 -> 0x8053DF8C
void vorbis_bitrate_clear(struct bitrate_manager_state * bm /* r30 */) {
    // Local variables
    int i; // r31
}

// Range: 0x8053DF8C -> 0x8053DFA8
int vorbis_bitrate_managed() {}

struct vorbis_block_internal {
    // total size: 0x48
    float * * pcmdelay; // offset 0x0, size 0x4
    float ampmax; // offset 0x4, size 0x4
    int blocktype; // offset 0x8, size 0x4
    unsigned int packetblob_markers[15]; // offset 0xC, size 0x3C
};

