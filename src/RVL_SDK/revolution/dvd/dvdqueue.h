#ifndef RVL_SDK_DVDQUEUE_H
#define RVL_SDK_DVDQUEUE_H
#include "types.h"
#include "revolution/dvd/dvd.h"
#ifdef __cplusplus
extern "C" {
#endif

DVDCommandBlock* __DVDPopWaitingQueue();
bool32 __DVDCheckWaitingQueue();
DVDCommandBlock* __DVDGetNextWaitingQueue();
bool32 __DVDDequeueWaitingQueue(DVDCommandBlock* block);

#ifdef __cplusplus
}
#endif
#endif