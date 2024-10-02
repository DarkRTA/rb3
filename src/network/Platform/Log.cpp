#include "Log.h"
#include "Platform/LogDeviceDebugOutput.h"
#include "Platform/OutputFormat.h"
#include "Platform/String.h"
#include <sdk/PowerPC_EABI_Support/MSL/MSL_C/string.h>
#include <cstdarg>

namespace Quazal {
    Log::Log() : m_oLogDevice(new (__FILE__, 34) LogDeviceDebugOutput), m_oOutputFormat(new (__FILE__, 38) OutputFormat), unk_0xC(NULL) {}
    // i'm pretty sure those are asserts...     

    Log::~Log() {
        delete m_oOutputFormat;
        if (m_oLogDevice) delete m_oLogDevice;
        if (unk_0xC) delete unk_0xC;
    }

    void Log::Output(const char* cc, ...) {
        va_list list;
        va_start(list, cc);
        OutputImpl(cc, list, NULL);
    }

    void Log::OutputString(const char* cc, ...) {
        va_list list;
        va_start(list, cc);
        OutputImpl(cc, list, NULL);
    }
    
    void Log::OutputImpl(const char* cc, va_list l, void* v) {
        char buf[0x1000];
        if (m_oLogDevice == NULL) return;
        if (unk_0xC != NULL && !unk_0xC->AcquireRef()) return;
        if (m_oOutputFormat == NULL) return;

        memset(buf, 0, 0x1000);
        m_oOutputFormat->StartString(buf, 4094);
        m_oOutputFormat->StartPrefixes(buf, 4094);
        AddCustomPrefix(buf, 4094, v);
        m_oOutputFormat->AddPrefixes(buf, 4094);
        m_oOutputFormat->EndPrefixes(buf, 4094);
        m_oOutputFormat->AddIndent(buf, 4094);
        m_oOutputFormat->AddMessage(buf, 4094, cc, l);
        m_oOutputFormat->EndString(buf, 4094);
        m_oLogDevice->Output(buf); // >:(
    }

    void Log::AddCustomPrefix(char*, int, void*) { }

    OutputFormat* Log::GetOutputFormat() { return m_oOutputFormat; }
}
