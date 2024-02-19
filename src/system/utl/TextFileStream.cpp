#include "utl/TextFileStream.h"
#include "utl/FileStream.h"
#include <stdio.h>

namespace {
    static const char kCRLF[2] = { '\r', '\n' };
}

TextFileStream::TextFileStream(const char *file, bool append)
    : mFile(file, append ? FileStream::kAppend : FileStream::kWrite, true) {
}

void TextFileStream::Print(const char *c) {
    char *p = (char *)c;
    while (*p != '\0') {
        if (*p == '\n' && p[1] != '\r')
            mFile.Write(kCRLF, sizeof(kCRLF));
        else
            mFile.Write(p, 1);
        p++;
    }
}
