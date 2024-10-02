#include "TraceLog.h"
#include "network/Platform/OutputFormat.h"

namespace Quazal {
TraceLog TraceLog::s_Instance;

TraceLog::~TraceLog() {}

TraceLog* TraceLog::GetInstance() { return &s_Instance; }

TraceLog::ScopedIndent::ScopedIndent(unsigned int indent_level) {
    mIndentLevel = indent_level;
    OutputFormat* fmt = TraceLog::s_Instance.GetOutputFormat();
    if (fmt != NULL) {
        fmt->IncreaseIndent(mIndentLevel);
    }
}

TraceLog::ScopedIndent::~ScopedIndent() {
    OutputFormat* fmt = TraceLog::s_Instance.GetOutputFormat();
    if (fmt != NULL) {
        fmt->DecreaseIndent(mIndentLevel);
    }
}
}
