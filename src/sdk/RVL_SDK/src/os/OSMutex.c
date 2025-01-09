#include <revolution/OS.h>

void OSInitMutex(OSMutex* mutex) {
    OSInitThreadQueue(&mutex->queue);
    mutex->thread = NULL;
    mutex->count = 0;
}

void OSLockMutex(OSMutex* mutex) {
    BOOL enabled = OSDisableInterrupts();
    OSThread* currThread = OSGetCurrentThread();

    while (TRUE) {
        if (mutex->thread == NULL) {
            OSMutex* tail;

            mutex->thread = currThread;
            mutex->count++;

            tail = currThread->queueMutex.tail;
            if (tail == NULL) {
                currThread->queueMutex.head = mutex;
            } else {
                tail->link.next = mutex;
            }

            mutex->link.prev = tail;
            mutex->link.next = NULL;
            currThread->queueMutex.tail = mutex;
            break;
        } else if (mutex->thread == currThread) {
            mutex->count++;
            break;
        } else {
            currThread->mutex = mutex;
            __OSPromoteThread(mutex->thread, currThread->priority);
            OSSleepThread(&mutex->queue);
            currThread->mutex = NULL;
        }
    }

    OSRestoreInterrupts(enabled);
}

void OSUnlockMutex(OSMutex* mutex) {
    BOOL enabled = OSDisableInterrupts();
    OSThread* currThread = OSGetCurrentThread();

    if (mutex->thread == currThread) {
        mutex->count--;

        if (mutex->count == 0) {
            OSMutex* next = mutex->link.next;
            OSMutex* prev = mutex->link.prev;

            if (next == NULL) {
                currThread->queueMutex.tail = prev;
            } else {
                next->link.prev = prev;
            }

            if (prev == NULL) {
                currThread->queueMutex.head = next;
            } else {
                prev->link.next = next;
            }

            mutex->thread = NULL;
            if (currThread->priority < currThread->base) {
                currThread->priority = __OSGetEffectivePriority(currThread);
            }

            OSWakeupThread(&mutex->queue);
        }
    }

    OSRestoreInterrupts(enabled);
}

void __OSUnlockAllMutex(OSThread* thread) {
    OSMutex* mutex;
    while ((mutex = thread->queueMutex.head) != NULL) {
        OSMutex* next = mutex->link.next;
        if (next == NULL) {
            thread->queueMutex.tail = NULL;
        } else {
            next->link.prev = NULL;
        }

        thread->queueMutex.head = next;
        mutex->count = 0;
        mutex->thread = NULL;
        OSWakeupThread(&mutex->queue);
    }
};

//unused
BOOL OSTryLockMutex(OSMutex* mutex) {
    BOOL enabled = OSDisableInterrupts();
    OSThread* currThread = OSGetCurrentThread();
    BOOL lock = FALSE;

    if (mutex->thread == NULL) {
        OSMutex* tail;

        mutex->thread = currThread;
        mutex->count++;

        tail = currThread->queueMutex.tail;
        if (tail == NULL) {
            currThread->queueMutex.head = mutex;
        } else {
            tail->link.next = mutex;
        }

        mutex->link.prev = tail;
        mutex->link.next = NULL;

        currThread->queueMutex.tail = mutex;
        lock = TRUE;
    } else if (mutex->thread == currThread) {
        mutex->count++;
        lock = TRUE;
    } else {
        lock = FALSE;
    }

    OSRestoreInterrupts(enabled);
    return lock;
}

//unused
void OSInitCond(OSCond*){
}

//unused
void OSWaitCond(OSCond* cond, OSMutex* mutex){
}

//unused
void OSSignalCond(OSCond* cond){
}

//unused
void __OSCheckMutex(){
}

//unused
void __OSCheckDeadLock(){
}

//unused
void __OSCheckMutexes(){
}

