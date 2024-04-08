#ifndef PLATFORM_STRINGSTREAM_H
#define PLATFORM_STRINGSTREAM_H
#include "Platform/RootObject.h"

namespace Quazal {
    class StringStream : public RootObject {
    public:
        StringStream();
        ~StringStream();
        void TestFreeRoom(unsigned int);

        const char* m_szBuffer;
        unsigned int m_uiSize;
        const char* m_szCurrentPosition;
        char m_szInitialBuffer[256];
        bool m_bHex;
        bool m_bShowBase;
        bool m_bBoolAlpha;
    };

    
    static void hex(StringStream&);
    static void dec(StringStream&);
}

#endif
