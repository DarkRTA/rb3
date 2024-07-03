#include "revolution/OS.h"

void SSL_InitMutex(OSMutex* mutex) {
    OSInitMutex(mutex);
}
void SSL_LockMutex(OSMutex* mutex) {
    OSLockMutex(mutex);
}
void SSL_UnlockMutex(OSMutex* mutex) {
    OSUnlockMutex(mutex);
}
