#ifndef PLATFORM_STRING_H
#define PLATFORM_STRING_H
#include "Platform/RootObject.h"
#include "Platform/StringStream.h"
#include "types.h"

namespace Quazal {
    class DebugString {
    public:
    };

    class String : public RootObject {
    public:
        String();
        String(const char *);
        String(const String &);
        ~String();
        Quazal::String &operator=(const char *);
        Quazal::String &operator=(const Quazal::String &);
        bool operator<(const Quazal::String &) const;
        void Reserve(int);
        uint GetLength() const;
        void CreateCopy(char **) const;
        void Format(const char *, ...);

        char *m_szContent;

        static bool IsEqual(const char *, const char *);
        static void ReleaseCopy(char *);
        static uint s_uiDefaultStringEncoding;
    };

    String &operator+(const Quazal::String &, const Quazal::String &);
    String &operator+(const Quazal::String &, const char *);
    StringStream &operator<<(Quazal::StringStream &, const Quazal::String &);
}

#endif
