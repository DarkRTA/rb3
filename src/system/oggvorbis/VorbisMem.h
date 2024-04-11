#ifndef OGGVORBIS_VORBISMEM_H
#define OGGVORBIS_VORBISMEM_H

#ifdef __cplusplus
extern "C" {
#endif // ifdef __cplusplus

void* OggMalloc(int);
void* OggCalloc(int, int);
void* OggRealloc(void*, int);
void OggFree(void*);

#ifdef __cplusplus
};
#endif // ifdef __cplusplus

#endif
