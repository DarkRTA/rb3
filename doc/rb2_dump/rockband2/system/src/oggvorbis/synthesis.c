/*
    Compile unit: C:\rockband2\system\src\oggvorbis\synthesis.c
    Producer: MW EABI PPC C-Compiler
    Language: C89
    Code range: 0x8054CC68 -> 0x8054CE1C
*/
// Range: 0x8054CC68 -> 0x8054CE1C
int vorbis_synthesis(struct vorbis_block * vb /* r28 */, struct {
    // total size: 0x20
    unsigned char * packet; // offset 0x0, size 0x4
    long bytes; // offset 0x4, size 0x4
    long b_o_s; // offset 0x8, size 0x4
    long e_o_s; // offset 0xC, size 0x4
    long long granulepos; // offset 0x10, size 0x8
    long long packetno; // offset 0x18, size 0x8
} * op /* r26 */) {
    // Local variables
    struct vorbis_dsp_state * vd; // r4
    struct private_state * b; // r31
    struct vorbis_info * vi; // r30
    struct codec_setup_info * ci; // r29
    struct {
        // total size: 0x14
        long endbyte; // offset 0x0, size 0x4
        int endbit; // offset 0x4, size 0x4
        unsigned char * buffer; // offset 0x8, size 0x4
        unsigned char * ptr; // offset 0xC, size 0x4
        long storage; // offset 0x10, size 0x4
    } * opb; // r27
    int mode; // r0
    int i; // r27

    // References
    // -> struct [anonymous] * _mapping_P[1];
}


