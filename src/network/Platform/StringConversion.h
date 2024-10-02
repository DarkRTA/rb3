#pragma once

namespace Quazal {
namespace StringConversion {
    void Char8_2T(const char* in, char* out, unsigned int len);
    void T2Char8(const char* in, char* out, unsigned int len);
    void Utf8ToT(const char* in, char* out, unsigned int len);
    void TToUtf8(const char* in, char* out, unsigned int len);
    int GetTToUtf8BufferSize(const char* str);
}
}
