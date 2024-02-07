/*
    Compile unit: C:\rockband2\system\src\oggvorbis\info.c
    Producer: MW EABI PPC C-Compiler
    Language: C89
    Code range: 0x80543374 -> 0x80543E10
*/
// Range: 0x80543374 -> 0x805433D8
static void _v_readstring(struct {
    // total size: 0x14
    long endbyte; // offset 0x0, size 0x4
    int endbit; // offset 0x4, size 0x4
    unsigned char * buffer; // offset 0x8, size 0x4
    unsigned char * ptr; // offset 0xC, size 0x4
    long storage; // offset 0x10, size 0x4
} * o /* r29 */, char * buf /* r30 */, int bytes /* r31 */) {}

// Range: 0x805433D8 -> 0x805433E4
void vorbis_comment_init() {}

struct vorbis_comment {
    // total size: 0x10
    char * * user_comments; // offset 0x0, size 0x4
    int * comment_lengths; // offset 0x4, size 0x4
    int comments; // offset 0x8, size 0x4
    char * vendor; // offset 0xC, size 0x4
};
// Range: 0x805433E4 -> 0x8054348C
void vorbis_comment_clear(struct vorbis_comment * vc /* r30 */) {
    // Local variables
    long i; // r31
}

// Range: 0x8054348C -> 0x805434D0
void vorbis_info_init(struct vorbis_info * vi /* r31 */) {}

// Range: 0x805434D0 -> 0x805436A8
void vorbis_info_clear(struct vorbis_info * vi /* r29 */) {
    // Local variables
    struct codec_setup_info * ci; // r31
    int i; // r30

    // References
    // -> struct [anonymous] * _residue_P[3];
    // -> struct [anonymous] * _floor_P[2];
    // -> struct [anonymous] * _mapping_P[1];
}

// Range: 0x805436A8 -> 0x805437F4
static int _vorbis_unpack_info(struct vorbis_info * vi /* r28 */, struct {
    // total size: 0x14
    long endbyte; // offset 0x0, size 0x4
    int endbit; // offset 0x4, size 0x4
    unsigned char * buffer; // offset 0x8, size 0x4
    unsigned char * ptr; // offset 0xC, size 0x4
    long storage; // offset 0x10, size 0x4
} * opb /* r29 */) {
    // Local variables
    struct codec_setup_info * ci; // r30
}

// Range: 0x805437F4 -> 0x80543928
static int _vorbis_unpack_comment(struct vorbis_comment * vc /* r27 */, struct {
    // total size: 0x14
    long endbyte; // offset 0x0, size 0x4
    int endbit; // offset 0x4, size 0x4
    unsigned char * buffer; // offset 0x8, size 0x4
    unsigned char * ptr; // offset 0xC, size 0x4
    long storage; // offset 0x10, size 0x4
} * opb /* r28 */) {
    // Local variables
    int i; // r30
    int vendorlen; // r30
    int len; // r29
}

// Range: 0x80543928 -> 0x80543CA0
static int _vorbis_unpack_books(struct vorbis_info * vi /* r28 */, struct {
    // total size: 0x14
    long endbyte; // offset 0x0, size 0x4
    int endbit; // offset 0x4, size 0x4
    unsigned char * buffer; // offset 0x8, size 0x4
    unsigned char * ptr; // offset 0xC, size 0x4
    long storage; // offset 0x10, size 0x4
} * opb /* r29 */) {
    // Local variables
    struct codec_setup_info * ci; // r31
    int i; // r30
    int times; // r27
    int test; // r0

    // References
    // -> struct [anonymous] * _mapping_P[1];
    // -> struct [anonymous] * _residue_P[3];
    // -> struct [anonymous] * _floor_P[2];
}

// Range: 0x80543CA0 -> 0x80543E10
int vorbis_synthesis_headerin(struct vorbis_info * vi /* r28 */, struct vorbis_comment * vc /* r29 */, struct {
    // total size: 0x20
    unsigned char * packet; // offset 0x0, size 0x4
    long bytes; // offset 0x4, size 0x4
    long b_o_s; // offset 0x8, size 0x4
    long e_o_s; // offset 0xC, size 0x4
    long long granulepos; // offset 0x10, size 0x8
    long long packetno; // offset 0x18, size 0x8
} * op /* r30 */) {
    // Local variables
    struct {
        // total size: 0x14
        long endbyte; // offset 0x0, size 0x4
        int endbit; // offset 0x4, size 0x4
        unsigned char * buffer; // offset 0x8, size 0x4
        unsigned char * ptr; // offset 0xC, size 0x4
        long storage; // offset 0x10, size 0x4
    } opb; // r1+0x10
    char buffer[6]; // r1+0x8
    int packtype; // r0
}


