#ifndef RVL_SDK_OS_ASSERT_H
#define RVL_SDK_OS_ASSERT_H

#include <revolution/os/OSError.h>

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(NDEBUG)
    #define OSAssertMessage_FileLine(file_, line_, exp_, ...) \
        (void)((exp_) || (OSPanic(file_, line_, __VA_ARGS__), 0))
#else
    #define OSAssertMessage_FileLine(file_, line_, exp_, ...) \
        ((void)0)
#endif

#define OSAssertMessage_Line(line_, exp_, ...) \
    OSAssertMessage_FileLine(__FILE__, line_, exp_, __VA_ARGS__)

#define OSAssert_Line(line_, exp_) \
    OSAssertMessage_FileLine(__FILE__, line_, exp_, "Failed assertion " #exp_)

#define OSAssertMessage(exp_, ...) \
    OSAssertMessage_Line(__LINE__, exp_, __VA_ARGS__)

#define OSAssert(exp_) \
    OSAssert_Line(__LINE__, exp_)

#ifdef __cplusplus
}
#endif

#endif
