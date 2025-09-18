#pragma once
#include <types.h>

#ifdef __cplusplus
extern "C" {
#endif

int NHTTPGetError();

void NHTTPStartup(void *, void *, int);

void NHTTPCleanupAsync(void *);
int NHTTPCancelConnection(void *);

#ifdef __cplusplus
}
#endif