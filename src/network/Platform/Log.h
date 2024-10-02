#pragma once

#include "Platform/OutputFormat.h"
#include "Platform/RefCountedObject.h"
#include "Platform/String.h"
#include <stdarg.h>
#include <types.h>

namespace Quazal {
    class LogEntry : public Quazal::String { public:
        LogEntry(const char* s) : String(s) {}
    };

    class LogDevice : public RootObject {
        public:
        virtual ~LogDevice() {}
        virtual void Output(const LogEntry&) = 0;
    };

    class Log : public RootObject {
        public:
        Log();
        virtual ~Log(); 
        virtual void Output(const char*, ...);
        virtual void OutputString(const char*, ...);
        virtual void AddCustomPrefix(char*, int, void*);
        void OutputImpl(const char*, va_list, void*);
        OutputFormat* GetOutputFormat();

        LogDevice* m_oLogDevice; // 0x4
        OutputFormat* m_oOutputFormat; // 0x8
        RefCountedObject* unk_0xC; // this guy has a virtual dtor and its 2nd virtual function is nonvoid and that's all the context i get
    };
}