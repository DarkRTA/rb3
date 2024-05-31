#include "Compress.h"
#include "zlib/zlib.h"
#undef SEEK_SET
#undef SEEK_CUR
#undef SEEK_END
#include "os/Debug.h"

#include "decomp.h"

extern void* _MemAllocTemp(int, int);
extern void _MemFree(void*);

DECOMP_FORCEACTIVE(Compress, "%s/gen/%s.%s_%s.z\0%s_%s.z")

void* ZAlloc(void* i, unsigned int len, unsigned int ct) {return _MemAllocTemp(len*ct, 0);}
void ZFree(void* a, void*b) {_MemFree(b);}

void DecompressMem(const void* in, int in_len, void* out, int& out_len, bool bits, const char* filename) {
    z_stream s;

    s.next_in = (unsigned char*)in;
    s.avail_in = in_len;
    s.next_out = (unsigned char*)out;
    s.avail_out = out_len;
    s.zalloc = ZAlloc;
    s.zfree = ZFree;
    int windowBits = bits ? 15 : -15;

    MILO_ASSERT(inflateInit2(&s, windowBits) == Z_OK, 106);

    int ret = inflate(&s, 4);
    if (ret != 1) MILO_FAIL("Inflate error: %d in %s", ret, filename);

    MILO_ASSERT(s.avail_in == 0, 109);
    MILO_ASSERT(inflateEnd(&s) == Z_OK, 110);

    out_len = s.total_out;
}

void CompressMem(const void* in, int in_len, void* out, int& out_len, const char* filename) {
    z_stream s;
    s.next_in = (unsigned char*)in;
    s.avail_in = in_len;
    s.next_out = (unsigned char*)out;
    s.avail_out = out_len;
    s.zalloc = ZAlloc;
    s.zfree = ZFree;

    MILO_ASSERT(deflateInit2(&s, Z_DEFAULT_COMPRESSION, Z_DEFLATED, -MAX_WBITS, MAX_MEM_LEVEL, Z_DEFAULT_STRATEGY) == Z_OK, 142);

    MILO_ASSERT(deflate(&s, Z_FINISH) == Z_STREAM_END, 144);
    MILO_ASSERT(deflateEnd(&s) == Z_OK, 145);

    out_len = s.total_out;
}
