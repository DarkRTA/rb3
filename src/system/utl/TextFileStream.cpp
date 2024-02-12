#include "utl/TextFileStream.h"

#include <stdio.h>

#include "utl/FileStream.h"
#include "unknown.hpp"

// fn_8037A58C - TextFileStream ctor
TextFileStream::TextFileStream(const char *file, bool append)
    : mFile(file, append ? FileStream::kAppend : FileStream::kWrite, true) {
}

static const char kCRLF[2] = { '\r', '\n' };

// fn_8037A5F8
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
