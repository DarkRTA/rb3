#include "Debug.h"

// Temp strings needed for string pooling to match
const char* s0 = "%s";
const char* s1 = "no_try";
const char* s2 = "log";
const char* s3 = "no_modal";
const char* s4 = "no_notify";
const char* s5 = "Debug.cpp";
const char* s6 = "MainThread()";
const char* s7 = "TRY conditional not exited %d";
const char* s8 = "\n\n-- Program ended --\n";
const char* s9 = "%s\n";
const char* s10 = "THREAD-NOTIFY not called in MainThread: %s\n";
const char* s11 = "NOTIFY: %s\n";
const char* s12 = "main";
const char* s13 = "THREAD-FAIL: %s\n";
const char* s14 = "FAIL-MSG: %s\n";
const char* s15 = "APP FAILED\n";
const char* s16 = "n/a";
const char* s17 = "version";
const char* s18 = "<unknown>";
const char* s19 = "\n\nConsoleName: %s   %s   Plat: %s   ";
const char* s20 = "\nLang: %s   SystemConfig: %s";
const char* s21 = "true";
const char* s22 = "false";
const char* s23 = "\nUptime: %.2f hrs   UsingCD: %s   SDK: %s";
const char* s24 = "debug/fail";
const char* s25 = "msg";
const char* s26 = "callstack";
const char* s27 = "dataCallstack";
const char* s28 = "cheatsMsg";
const char* s29 = "FAIL: %s\n";
const char* s30 = "APP EXITED, EXIT CODE %d\n";
const char* s31 = "Debug::Print";
const char* s32 = "Couldn't open log %s";

// Declared in stlport/_vector.h since it's not relevant anywhere else
void std_vec_range_assert(size_t value, size_t max, const char *func) {
    if (value > (max / 4)) {
        MILO_FAIL("std::vector::%s: index range exceeded (0x%08x > 0x%08x)\n", func, value, (max / 4));
    }
}
