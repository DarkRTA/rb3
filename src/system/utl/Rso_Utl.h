#ifndef UTL_RSOUTL_H
#define UTL_RSOUTL_H

#include "os/File.h"

typedef bool (*RsoInitFunc)(struct RSOObjectHeader *);
typedef void (*RsoDeinitFunc)(void);

void *RsoMemAlloc2Fake(int size);
void *DefaultRSOMemAlloc2(int size);
void RsoAddIniter(RsoInitFunc, RsoDeinitFunc);
void *LoadRsoFile(const char *, unsigned int &, void *(*)(int));

#endif // UTL_RSOUTL_H