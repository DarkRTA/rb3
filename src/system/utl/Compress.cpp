#include "Compress.h"
#include "zlib/zlib.h"
#include "os/Debug.h"

extern void* _MemAllocTemp(int, int);
extern void _MemFree(void*);

char* why = "%s/gen/%s.%s_%s.z\0%s_%s.z";

void* ZAlloc(void* i, unsigned int len, unsigned int ct) {return _MemAllocTemp(len*ct, 0);}
void ZFree(void* a, void*b) {_MemFree(b);}

void DecompressMem(const void* in, int in_len, void* out, int& out_len, bool b, const char* filename) {
    z_stream s;
    unsigned int windowBits = -15;

    s.next_in = (unsigned char*)in;
    s.avail_in = in_len;
    s.next_out = (unsigned char*)out;
    s.avail_out = out_len;
    s.zalloc = ZAlloc;
    s.zfree = ZFree;
    if (b) windowBits = 15;

    ASSERT(inflateInit2(&s, windowBits) == Z_OK, 106);

    int ret = inflate(&s, 4);
    if (ret != 1) FAIL("Inflate error: %d in %s", ret, filename);

    ASSERT(s.avail_in == 0, 109);
    ASSERT(inflateEnd(&s) == Z_OK, 110);

    out_len = s.total_out;
}

void CompressMem(const void* in, int in_len, void* out, int& out_len, const char* filename) {
    z_stream s;
    s.avail_out = out_len;
    s.next_in = (unsigned char*)in;
    s.avail_in = in_len;
    s.next_out = (unsigned char*)out;
    s.zalloc = ZAlloc;
    s.zfree = ZFree;

    ASSERT(deflateInit2(&s, Z_DEFAULT_COMPRESSION, Z_DEFLATED, -MAX_WBITS, MAX_MEM_LEVEL, Z_DEFAULT_STRATEGY) == Z_OK, 142);

    ASSERT(deflate(&s, Z_FINISH) == Z_STREAM_END, 144);
    ASSERT(deflateEnd(&s) == Z_OK, 145);

    out_len = s.total_out;
}
