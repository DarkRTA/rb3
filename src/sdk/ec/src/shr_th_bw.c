#include <ec/internal/shr.h>

int _SHR_mutex_init(_SHRMutex* mutex, _SHRBool a, int b, _SHRBool lock) {
    OSThread* thread;

    OSInitMutex(&mutex->osMutex);
    mutex->_18 = a;
    mutex->thread = lock ? OSGetCurrentThread() : NULL;
    mutex->lockCount = !!lock;

    if (lock) {
        OSLockMutex(&mutex->osMutex);
    }

    return 0;
}

int _SHR_mutex_lock(_SHRMutex* mutex) {
    int result = 0;
    OSThread* thread = OSGetCurrentThread();

    if (mutex->thread == thread && mutex->_18 != TRUE) {
        result = -35;
    } else {
        OSLockMutex(&mutex->osMutex);
        mutex->thread = thread;
        mutex->lockCount++;
    }

    return result;
}

int _SHR_mutex_unlock(_SHRMutex* mutex) {
    int result = 0;
    OSThread* thread = OSGetCurrentThread();

    if (mutex->thread != thread) {
        printf("Attempt to unlock mutex not locked by current thread");
        result = -1;
    } else {
        if (--mutex->lockCount == 0) {
            mutex->thread = NULL;
        }
        OSUnlockMutex(&mutex->osMutex);
    }

    return result;
}

int _SHR_mutex_destroy(_SHRMutex* mutex) {
    return 0;
}


int _SHR_message_queue_init(_SHRMessageQueue* queue, OSMessage* buffer, s32 capacity) {
    OSInitMessageQueue(&queue->osQueue, buffer, capacity);
    return 0;
}

int _SHR_message_send(_SHRMessageQueue* queue, OSMessage message, u32 flags) {
    int result = 0;

    if (!OSSendMessage(&queue->osQueue, message, flags)) {
        result = -255;
    }

    return result;
}

int _SHR_message_receive(_SHRMessageQueue* queue, OSMessage* message, u32 flags) {
    int result = 0;

    if (!OSReceiveMessage(&queue->osQueue, message, flags)) {
        result = -255;
    }

    return result;
}


int _SHR_thread_create(_SHRThread* thread, _SHRThreadAttr* attr, OSThreadFunc func, void* context) {
    int result = 0;
    void* stack;

    if (attr != NULL) {
        stack = (unsigned char*)attr->stack + attr->stackSize;
    } else {
        printf("_SHR_thread_create attr->stack required\n");
        result = -255;
        goto end;
    }

    OSCreateThread(&thread->osThread, func, context, stack, attr->stackSize, attr->priority, 0);
    if (attr->start) {
        OSResumeThread(&thread->osThread);
    }

end:
    return result;
}

int _SHR_thread_join(_SHRThread* thread, void* context) {
    OSJoinThread(&thread->osThread, context);
    return 0;
}

int _SHR_thread_sleep(u32 ms) {
    OSSleepTicks(OSMillisecondsToTicks((s64)ms));
    return 0;
}

