#include "Platform/String.h"
#include "Platform/MemoryManager.h"
#include "types.h"
#include <cstdio>
#include <cstring>

inline void CopyString(char **dst, const char *src) {
    if (!src) {
        *dst = 0;
    } else {
        unsigned int size = strlen(src) + 1;
        char *v = (char *)QUAZAL_DEFAULT_ALLOC(size + 4, 0x2F, _InstType9);
        *(u32 *)v = size;
        *dst = v + 4;
        strcpy(v + 4, src);
    }
}

inline void YeetString(char *str) {
    if (str) {
        QUAZAL_DEFAULT_FREE(str - 4, _InstType9)
    }
}

namespace Quazal {
    uint String::s_uiDefaultStringEncoding = 1;

    String::String() { CopyString(&m_szContent, ""); }
    String::String(const char *s) { CopyString(&m_szContent, s); }
    String::String(const String &s) { CopyString(&m_szContent, s.m_szContent); }
    String::~String() { YeetString(m_szContent); }
    String &String::operator=(const char *rhs) {
        if (m_szContent == rhs)
            return *this;
        else {
            YeetString(m_szContent);
            CopyString(&m_szContent, rhs);
            return *this;
        }
    }
    String &String::operator=(const String &rhs) {
        if (m_szContent != rhs.m_szContent) {
            YeetString(m_szContent);
            CopyString(&m_szContent, rhs.m_szContent);
        }
        return *this;
    }

    bool String::IsEqual(const char *, const char *) {}

    bool String::operator<(const Quazal::String &) const {}

    void String::Reserve(int size) {
        YeetString(m_szContent);
        u32 *str = (u32 *)QUAZAL_DEFAULT_ALLOC(size + 4, 203, _InstType9);
        *str = size;
        m_szContent = (char *)&str[1];
        *m_szContent = 0;
    }

    uint String::GetLength() const {
        if (m_szContent == nullptr)
            return 0;
        return strlen(m_szContent);
    }

    void String::CreateCopy(char **nu) const { CopyString(nu, m_szContent); }

    void String::ReleaseCopy(char *copy) { YeetString(copy); }

    void String::Format(const char *fmt, ...) {
        char buf[0x1010];
        va_list list;
        va_start(list, fmt);
        vsprintf(buf, fmt, list);
        if (m_szContent == buf)
            return;
        YeetString(m_szContent);
        CopyString(&m_szContent, buf);
    }

    namespace {
        String _Copy(const char *c1, unsigned int s1, const char *c2, unsigned int s2) {
            String s = "";
            YeetString(s.m_szContent);
            int size = s1 + s2;
            u32 *str = (u32 *)QUAZAL_DEFAULT_ALLOC(size + 4, 203, _InstType9);
            *str = size;
            s.m_szContent = (char *)&str[1];
            *s.m_szContent = 0;
            char *s3 = s.m_szContent;
            strcpy(s3, c1);
            strcpy(s3 + s1, c2);

            return s;
        }
    }

    String &operator+(const Quazal::String &, const Quazal::String &) {}
    String &operator+(const Quazal::String &lhs, const char *rhs) {
        String s(lhs);
        return s;
    }
    StringStream &operator<<(Quazal::StringStream &ss, const Quazal::String &str) {
        return ss << str.m_szContent;
    }

}
