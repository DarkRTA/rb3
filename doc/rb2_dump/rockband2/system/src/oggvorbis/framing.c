/*
    Compile unit: C:\rockband2\system\src\oggvorbis\framing.c
    Producer: MW EABI PPC C-Compiler
    Language: C89
    Code range: 0x805426A8 -> 0x80543374
*/
// Range: 0x805426A8 -> 0x805426B4
int ogg_page_version() {}

// Range: 0x805426B4 -> 0x805426C4
int ogg_page_continued() {}

// Range: 0x805426C4 -> 0x805426D4
int ogg_page_bos() {}

// Range: 0x805426D4 -> 0x805426E4
int ogg_page_eos() {}

// Range: 0x805426E4 -> 0x805427B0
long long ogg_page_granulepos() {
    // Local variables
    unsigned char * page; // r6
    long long granulepos; // r0
}

// Range: 0x805427B0 -> 0x805427D4
int ogg_page_serialno() {}

// Range: 0x805427D4 -> 0x805427F8
long ogg_page_pageno() {}

static unsigned int crc_lookup[256]; // size: 0x400, address: 0x80908BB0
// Range: 0x805427F8 -> 0x80542884
int ogg_stream_init(struct {
    // total size: 0x168
    unsigned char * body_data; // offset 0x0, size 0x4
    long body_storage; // offset 0x4, size 0x4
    long body_fill; // offset 0x8, size 0x4
    long body_returned; // offset 0xC, size 0x4
    int * lacing_vals; // offset 0x10, size 0x4
    long long * granule_vals; // offset 0x14, size 0x4
    long lacing_storage; // offset 0x18, size 0x4
    long lacing_fill; // offset 0x1C, size 0x4
    long lacing_packet; // offset 0x20, size 0x4
    long lacing_returned; // offset 0x24, size 0x4
    unsigned char header[282]; // offset 0x28, size 0x11A
    int header_fill; // offset 0x144, size 0x4
    int e_o_s; // offset 0x148, size 0x4
    int b_o_s; // offset 0x14C, size 0x4
    long serialno; // offset 0x150, size 0x4
    long pageno; // offset 0x154, size 0x4
    long long packetno; // offset 0x158, size 0x8
    long long granulepos; // offset 0x160, size 0x8
} * os /* r30 */, int serialno /* r31 */) {}

// Range: 0x80542884 -> 0x805428F8
int ogg_stream_clear(struct {
    // total size: 0x168
    unsigned char * body_data; // offset 0x0, size 0x4
    long body_storage; // offset 0x4, size 0x4
    long body_fill; // offset 0x8, size 0x4
    long body_returned; // offset 0xC, size 0x4
    int * lacing_vals; // offset 0x10, size 0x4
    long long * granule_vals; // offset 0x14, size 0x4
    long lacing_storage; // offset 0x18, size 0x4
    long lacing_fill; // offset 0x1C, size 0x4
    long lacing_packet; // offset 0x20, size 0x4
    long lacing_returned; // offset 0x24, size 0x4
    unsigned char header[282]; // offset 0x28, size 0x11A
    int header_fill; // offset 0x144, size 0x4
    int e_o_s; // offset 0x148, size 0x4
    int b_o_s; // offset 0x14C, size 0x4
    long serialno; // offset 0x150, size 0x4
    long pageno; // offset 0x154, size 0x4
    long long packetno; // offset 0x158, size 0x8
    long long granulepos; // offset 0x160, size 0x8
} * os /* r31 */) {}

// Range: 0x805428F8 -> 0x8054294C
static void _os_body_expand(struct {
    // total size: 0x168
    unsigned char * body_data; // offset 0x0, size 0x4
    long body_storage; // offset 0x4, size 0x4
    long body_fill; // offset 0x8, size 0x4
    long body_returned; // offset 0xC, size 0x4
    int * lacing_vals; // offset 0x10, size 0x4
    long long * granule_vals; // offset 0x14, size 0x4
    long lacing_storage; // offset 0x18, size 0x4
    long lacing_fill; // offset 0x1C, size 0x4
    long lacing_packet; // offset 0x20, size 0x4
    long lacing_returned; // offset 0x24, size 0x4
    unsigned char header[282]; // offset 0x28, size 0x11A
    int header_fill; // offset 0x144, size 0x4
    int e_o_s; // offset 0x148, size 0x4
    int b_o_s; // offset 0x14C, size 0x4
    long serialno; // offset 0x150, size 0x4
    long pageno; // offset 0x154, size 0x4
    long long packetno; // offset 0x158, size 0x8
    long long granulepos; // offset 0x160, size 0x8
} * os /* r31 */) {}

// Range: 0x8054294C -> 0x805429B8
static void _os_lacing_expand(struct {
    // total size: 0x168
    unsigned char * body_data; // offset 0x0, size 0x4
    long body_storage; // offset 0x4, size 0x4
    long body_fill; // offset 0x8, size 0x4
    long body_returned; // offset 0xC, size 0x4
    int * lacing_vals; // offset 0x10, size 0x4
    long long * granule_vals; // offset 0x14, size 0x4
    long lacing_storage; // offset 0x18, size 0x4
    long lacing_fill; // offset 0x1C, size 0x4
    long lacing_packet; // offset 0x20, size 0x4
    long lacing_returned; // offset 0x24, size 0x4
    unsigned char header[282]; // offset 0x28, size 0x11A
    int header_fill; // offset 0x144, size 0x4
    int e_o_s; // offset 0x148, size 0x4
    int b_o_s; // offset 0x14C, size 0x4
    long serialno; // offset 0x150, size 0x4
    long pageno; // offset 0x154, size 0x4
    long long packetno; // offset 0x158, size 0x8
    long long granulepos; // offset 0x160, size 0x8
} * os /* r31 */) {}

// Range: 0x805429B8 -> 0x80542A94
void ogg_page_checksum_set() {
    // Local variables
    unsigned int crc_reg; // r5
    int i; // r7

    // References
    // -> static unsigned int crc_lookup[256];
}

// Range: 0x80542A94 -> 0x80542AC8
int ogg_sync_init() {}

// Range: 0x80542AC8 -> 0x80542B14
int ogg_sync_clear(struct {
    // total size: 0x1C
    unsigned char * data; // offset 0x0, size 0x4
    int storage; // offset 0x4, size 0x4
    int fill; // offset 0x8, size 0x4
    int returned; // offset 0xC, size 0x4
    int unsynced; // offset 0x10, size 0x4
    int headerbytes; // offset 0x14, size 0x4
    int bodybytes; // offset 0x18, size 0x4
} * oy /* r31 */) {}

// Range: 0x80542B14 -> 0x80542BCC
char * ogg_sync_buffer(struct {
    // total size: 0x1C
    unsigned char * data; // offset 0x0, size 0x4
    int storage; // offset 0x4, size 0x4
    int fill; // offset 0x8, size 0x4
    int returned; // offset 0xC, size 0x4
    int unsynced; // offset 0x10, size 0x4
    int headerbytes; // offset 0x14, size 0x4
    int bodybytes; // offset 0x18, size 0x4
} * oy /* r30 */, long size /* r31 */) {
    // Local variables
    long newsize; // r31
}

// Range: 0x80542BCC -> 0x80542BF4
int ogg_sync_wrote() {}

// Range: 0x80542BF4 -> 0x80542E00
long ogg_sync_pageseek(struct {
    // total size: 0x1C
    unsigned char * data; // offset 0x0, size 0x4
    int storage; // offset 0x4, size 0x4
    int fill; // offset 0x8, size 0x4
    int returned; // offset 0xC, size 0x4
    int unsynced; // offset 0x10, size 0x4
    int headerbytes; // offset 0x14, size 0x4
    int bodybytes; // offset 0x18, size 0x4
} * oy /* r28 */, struct {
    // total size: 0x10
    unsigned char * header; // offset 0x0, size 0x4
    long header_len; // offset 0x4, size 0x4
    unsigned char * body; // offset 0x8, size 0x4
    long body_len; // offset 0xC, size 0x4
} * og /* r29 */) {
    // Local variables
    unsigned char * page; // r31
    unsigned char * next; // r3
    long bytes; // r30
    int headerbytes; // r5
    int i; // r6
    char chksum[4]; // r1+0x8
    struct {
        // total size: 0x10
        unsigned char * header; // offset 0x0, size 0x4
        long header_len; // offset 0x4, size 0x4
        unsigned char * body; // offset 0x8, size 0x4
        long body_len; // offset 0xC, size 0x4
    } log; // r1+0x10
    unsigned char * page; // r3
    long bytes; // r3
}

// Range: 0x80542E00 -> 0x80542E74
int ogg_sync_pageout(struct {
    // total size: 0x1C
    unsigned char * data; // offset 0x0, size 0x4
    int storage; // offset 0x4, size 0x4
    int fill; // offset 0x8, size 0x4
    int returned; // offset 0xC, size 0x4
    int unsynced; // offset 0x10, size 0x4
    int headerbytes; // offset 0x14, size 0x4
    int bodybytes; // offset 0x18, size 0x4
} * oy /* r30 */, struct {
    // total size: 0x10
    unsigned char * header; // offset 0x0, size 0x4
    long header_len; // offset 0x4, size 0x4
    unsigned char * body; // offset 0x8, size 0x4
    long body_len; // offset 0xC, size 0x4
} * og /* r31 */) {
    // Local variables
    long ret; // r0
}

// Range: 0x80542E74 -> 0x805431B4
int ogg_stream_pagein(struct {
    // total size: 0x168
    unsigned char * body_data; // offset 0x0, size 0x4
    long body_storage; // offset 0x4, size 0x4
    long body_fill; // offset 0x8, size 0x4
    long body_returned; // offset 0xC, size 0x4
    int * lacing_vals; // offset 0x10, size 0x4
    long long * granule_vals; // offset 0x14, size 0x4
    long lacing_storage; // offset 0x18, size 0x4
    long lacing_fill; // offset 0x1C, size 0x4
    long lacing_packet; // offset 0x20, size 0x4
    long lacing_returned; // offset 0x24, size 0x4
    unsigned char header[282]; // offset 0x28, size 0x11A
    int header_fill; // offset 0x144, size 0x4
    int e_o_s; // offset 0x148, size 0x4
    int b_o_s; // offset 0x14C, size 0x4
    long serialno; // offset 0x150, size 0x4
    long pageno; // offset 0x154, size 0x4
    long long packetno; // offset 0x158, size 0x8
    long long granulepos; // offset 0x160, size 0x8
} * os /* r17 */, struct {
    // total size: 0x10
    unsigned char * header; // offset 0x0, size 0x4
    long header_len; // offset 0x4, size 0x4
    unsigned char * body; // offset 0x8, size 0x4
    long body_len; // offset 0xC, size 0x4
} * og /* r18 */) {
    // Local variables
    unsigned char * header; // r24
    unsigned char * body; // r23
    long bodysize; // r22
    int segptr; // r21
    int version; // r0
    int continued; // r0
    int bos; // r20
    int eos; // r0
    long long granulepos; // r0
    int serialno; // r0
    long pageno; // r0
    int segments; // r19
    long lr; // r18
    long br; // r4
    int i; // r4
    int val; // r0
    int saved; // r5
    int val; // r6
}

// Range: 0x805431B4 -> 0x805431D4
int ogg_sync_reset() {}

// Range: 0x805431D4 -> 0x80543218
int ogg_stream_reset() {}

// Range: 0x80543218 -> 0x80543364
static int _packetout() {
    // Local variables
    int ptr; // r8
    int size; // r7
    int bytes; // r9
    int eos; // r10
    int bos; // r11
    int val; // r0
}

// Range: 0x80543364 -> 0x8054336C
int ogg_stream_packetout() {}

// Range: 0x8054336C -> 0x80543374
int ogg_stream_packetpeek() {}


