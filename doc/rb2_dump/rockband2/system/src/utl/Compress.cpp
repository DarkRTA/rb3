/*
    Compile unit: C:\rockband2\system\src\utl\Compress.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80608014 -> 0x806083B8
*/
int (* inflateInit2RSO)(struct z_stream_s *, int); // size: 0x4, address: 0x80A55400
int (* inflateRSO)(struct z_stream_s *, int); // size: 0x4, address: 0x80A55404
int (* inflateEndRSO)(struct z_stream_s *); // size: 0x4, address: 0x80A55408
int (* deflateInit2RSO)(struct z_stream_s *, int, int, int, int, int); // size: 0x4, address: 0x80A5540C
int (* deflateRSO)(struct z_stream_s *, int); // size: 0x4, address: 0x80A55410
int (* deflateEndRSO)(struct z_stream_s *); // size: 0x4, address: 0x80A55414
static struct RSOExportFuncTable exp_tbl_zlibModule[6]; // size: 0x30, address: 0x8092BEA0
struct RSOObjectHeader * zlibModule; // size: 0x4, address: 0x80A55418
// Range: 0x80608014 -> 0x806080B4
unsigned char ZLibRsoInit() {
    // References
    // -> struct RSOObjectHeader * zlibModule;
}

// Range: 0x806080B4 -> 0x806080FC
void ZLibRsoTerminate() {
    // References
    // -> struct RSOObjectHeader * zlibModule;
}

// Range: 0x806080FC -> 0x80608110
static void * ZAlloc() {}

// Range: 0x80608110 -> 0x80608118
static void ZFree() {}

struct internal_state {
    // total size: 0x0
};
struct z_stream_s {
    // total size: 0x38
    unsigned char * next_in; // offset 0x0, size 0x4
    unsigned int avail_in; // offset 0x4, size 0x4
    unsigned long total_in; // offset 0x8, size 0x4
    unsigned char * next_out; // offset 0xC, size 0x4
    unsigned int avail_out; // offset 0x10, size 0x4
    unsigned long total_out; // offset 0x14, size 0x4
    char * msg; // offset 0x18, size 0x4
    struct internal_state * state; // offset 0x1C, size 0x4
    void * (* zalloc)(void *, unsigned int, unsigned int); // offset 0x20, size 0x4
    void (* zfree)(void *, void *); // offset 0x24, size 0x4
    void * opaque; // offset 0x28, size 0x4
    int data_type; // offset 0x2C, size 0x4
    unsigned long adler; // offset 0x30, size 0x4
    unsigned long reserved; // offset 0x34, size 0x4
};
// Range: 0x80608118 -> 0x80608280
void DecompressMem(int & dstLen /* r30 */) {
    // Local variables
    struct z_stream_s s; // r1+0x8
    int ret; // r4

    // References
    // -> int (* inflateEndRSO)(struct z_stream_s *);
    // -> int (* inflateRSO)(struct z_stream_s *, int);
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> int (* inflateInit2RSO)(struct z_stream_s *, int);
}

// Range: 0x80608280 -> 0x806083B8
void CompressMem(int & dstLen /* r30 */) {
    // Local variables
    struct z_stream_s s; // r1+0x8

    // References
    // -> int (* deflateEndRSO)(struct z_stream_s *);
    // -> int (* deflateRSO)(struct z_stream_s *, int);
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> int (* deflateInit2RSO)(struct z_stream_s *, int, int, int, int, int);
}


