#pragma once

#include "network/Platform/Log.h"
#include "types.h"

namespace Quazal {
class TraceLog : public Log {
    public:

    class ScopedIndent {
        public:
        ScopedIndent(uint);
        ~ScopedIndent();
        u32 mIndentLevel; // 0x0
    };

    TraceLog() { unk_0x10 = 1; }
    virtual ~TraceLog();

    u32 unk_0x10;

    static TraceLog* GetInstance();

    static TraceLog s_Instance;
};
}
