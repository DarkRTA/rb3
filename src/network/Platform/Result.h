#ifndef PLATFORM_RESULT_H
#define PLATFORM_RESULT_H
// #include "Platform/RootObject.h"

namespace Quazal {
    class qResult {
    public:
        qResult();
        qResult(const int&);
        bool Equals(const int&) const;
        bool Equals(const bool&) const;

        operator bool() const;
        qResult& operator=(const int&);
        qResult& operator=(const qResult&);
        
        void Trace(unsigned int) const;

        int m_iReturnCode;
        const char* m_cszFilename;
        int m_iLineNumber;    
    };
}

#endif
