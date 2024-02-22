#ifndef UTL_COMPRESS_H
#define UTL_COMPRESS_H


void* ZAlloc(void*, unsigned int, unsigned int);
void ZFree(void*, void*);
void DecompressMem(const void*, int, void*, int&, bool, const char*);
void CompressMem(const void*, int, void*, int&, const char*);

#endif // UTL_COMPRESS_H
