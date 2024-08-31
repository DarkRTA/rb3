#pragma once

#include "Platform/Log.h"

namespace Quazal {
    class LogDeviceDebugOutput : public LogDevice {
        public:
        LogDeviceDebugOutput() { }
        virtual ~LogDeviceDebugOutput() { }
        virtual void Output(const LogEntry&);
    };
}
