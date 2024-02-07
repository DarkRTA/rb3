/*
    Compile unit: C:\rockband2\system\src\oggvorbis\analysis.c
    Producer: MW EABI PPC C-Compiler
    Language: C89
    Code range: 0x8053DE84 -> 0x8053DE84
*/
struct vorbis_info {
    // total size: 0x20
    int version; // offset 0x0, size 0x4
    int channels; // offset 0x4, size 0x4
    long rate; // offset 0x8, size 0x4
    long bitrate_upper; // offset 0xC, size 0x4
    long bitrate_nominal; // offset 0x10, size 0x4
    long bitrate_lower; // offset 0x14, size 0x4
    long bitrate_window; // offset 0x18, size 0x4
    void * codec_setup; // offset 0x1C, size 0x4
};
struct vorbis_dsp_state {
    // total size: 0x70
    int analysisp; // offset 0x0, size 0x4
    struct vorbis_info * vi; // offset 0x4, size 0x4
    float * * pcm; // offset 0x8, size 0x4
    float * * pcmret; // offset 0xC, size 0x4
    int pcm_storage; // offset 0x10, size 0x4
    int pcm_current; // offset 0x14, size 0x4
    int pcm_returned; // offset 0x18, size 0x4
    int preextrapolate; // offset 0x1C, size 0x4
    int eofflag; // offset 0x20, size 0x4
    long lW; // offset 0x24, size 0x4
    long W; // offset 0x28, size 0x4
    long nW; // offset 0x2C, size 0x4
    long centerW; // offset 0x30, size 0x4
    long long granulepos; // offset 0x38, size 0x8
    long long sequence; // offset 0x40, size 0x8
    long long glue_bits; // offset 0x48, size 0x8
    long long time_bits; // offset 0x50, size 0x8
    long long floor_bits; // offset 0x58, size 0x8
    long long res_bits; // offset 0x60, size 0x8
    void * backend_state; // offset 0x68, size 0x4
};
struct alloc_chain {
    // total size: 0x8
    void * ptr; // offset 0x0, size 0x4
    struct alloc_chain * next; // offset 0x4, size 0x4
};
enum /* @enum$588analysis_c */ {
    vss_init = 0,
    vss_decode = 1,
    vss_mdct = 2,
};
struct vorbis_block {
    // total size: 0x70
    float * * pcm; // offset 0x0, size 0x4
    struct {
        // total size: 0x14
        long endbyte; // offset 0x0, size 0x4
        int endbit; // offset 0x4, size 0x4
        unsigned char * buffer; // offset 0x8, size 0x4
        unsigned char * ptr; // offset 0xC, size 0x4
        long storage; // offset 0x10, size 0x4
    } opb; // offset 0x4, size 0x14
    long lW; // offset 0x18, size 0x4
    long W; // offset 0x1C, size 0x4
    long nW; // offset 0x20, size 0x4
    int pcmend; // offset 0x24, size 0x4
    int mode; // offset 0x28, size 0x4
    int eofflag; // offset 0x2C, size 0x4
    long long granulepos; // offset 0x30, size 0x8
    long long sequence; // offset 0x38, size 0x8
    struct vorbis_dsp_state * vd; // offset 0x40, size 0x4
    void * localstore; // offset 0x44, size 0x4
    long localtop; // offset 0x48, size 0x4
    long localalloc; // offset 0x4C, size 0x4
    long totaluse; // offset 0x50, size 0x4
    struct alloc_chain * reap; // offset 0x54, size 0x4
    long glue_bits; // offset 0x58, size 0x4
    long time_bits; // offset 0x5C, size 0x4
    long floor_bits; // offset 0x60, size 0x4
    long res_bits; // offset 0x64, size 0x4
    void * internal; // offset 0x68, size 0x4
    enum /* @enum$588analysis_c */ {
        vss_init = 0,
        vss_decode = 1,
        vss_mdct = 2,
    } synthesis_state; // offset 0x6C, size 0x4
};
struct _FILE {
    // total size: 0x50
    unsigned long handle; // offset 0x0, size 0x4
    struct {
        // total size: 0x4
        unsigned int open_mode : 2; // offset 0x0, size 0x4
        unsigned int io_mode : 3; // offset 0x0, size 0x4
        unsigned int buffer_mode : 2; // offset 0x0, size 0x4
        unsigned int file_kind : 3; // offset 0x0, size 0x4
        unsigned int file_orientation : 2; // offset 0x0, size 0x4
        unsigned int binary_io : 1; // offset 0x0, size 0x4
    } mode; // offset 0x4, size 0x4
    struct {
        // total size: 0x4
        unsigned int io_state : 3; // offset 0x0, size 0x4
        unsigned int free_buffer : 1; // offset 0x0, size 0x4
        unsigned char eof; // offset 0x1, size 0x1
        unsigned char error; // offset 0x2, size 0x1
    } state; // offset 0x8, size 0x4
    unsigned char is_dynamically_allocated; // offset 0xC, size 0x1
    unsigned char char_buffer; // offset 0xD, size 0x1
    unsigned char char_buffer_overflow; // offset 0xE, size 0x1
    unsigned char ungetc_buffer[2]; // offset 0xF, size 0x2
    unsigned short ungetwc_buffer[2]; // offset 0x12, size 0x4
    unsigned long position; // offset 0x18, size 0x4
    unsigned char * buffer; // offset 0x1C, size 0x4
    unsigned long buffer_size; // offset 0x20, size 0x4
    unsigned char * buffer_ptr; // offset 0x24, size 0x4
    unsigned long buffer_len; // offset 0x28, size 0x4
    unsigned long buffer_alignment; // offset 0x2C, size 0x4
    unsigned long saved_buffer_len; // offset 0x30, size 0x4
    unsigned long buffer_pos; // offset 0x34, size 0x4
    int (* position_proc)(unsigned long, unsigned long *, int, void *); // offset 0x38, size 0x4
    int (* read_proc)(unsigned long, unsigned char *, unsigned long *, void *); // offset 0x3C, size 0x4
    int (* write_proc)(unsigned long, unsigned char *, unsigned long *, void *); // offset 0x40, size 0x4
    int (* close_proc)(unsigned long); // offset 0x44, size 0x4
    void * ref_con; // offset 0x48, size 0x4
    struct _FILE * next_file_struct; // offset 0x4C, size 0x4
};

