#include "utl/TextStream.h"
#include "os/Debug.h"
#include <stdio.h>

TextStream::TextStream() {

}

TextStream &TextStream::operator<<(char c) {
    char stack[1024];
    int res = snprintf(stack, 0x400, "%c", c);
    if(res < 0) KASSERTSTR_FAIL(0x20, "SNPRINTF(buf, sizeof(buf), \"%c\", i) >= 0");
    Print(stack);
    return *this;
}

TextStream &TextStream::operator<<(short sh) {
    char stack[1024];
    int res = snprintf(stack, 0x400, "%hd", sh);
    if(res < 0) KASSERTSTR_FAIL(0x25, "SNPRINTF(buf, sizeof(buf), \"%hd\", i) >= 0");
    Print(stack);
    return *this;
}

TextStream &TextStream::operator<<(int i) {
    char stack[1024];
    int res = snprintf(stack, 0x400, "%d", i);
    if(res < 0) KASSERTSTR_FAIL(0x2A, "SNPRINTF(buf, sizeof(buf), \"%d\", i) >= 0");
    Print(stack);
    return *this;
}

TextStream &TextStream::operator<<(long l) {
    char stack[1024];
    int res = snprintf(stack, 0x400, "%ld", l);
    if(res < 0) KASSERTSTR_FAIL(0x2F, "SNPRINTF(buf, sizeof(buf), \"%ld\", i) >= 0");
    Print(stack);
    return *this;
}

TextStream &TextStream::operator<<(unsigned char uc) {
    char stack[1024];
    int res = snprintf(stack, 0x400, "%u", uc);
    if(res < 0) KASSERTSTR_FAIL(0x34, "SNPRINTF(buf, sizeof(buf), \"%u\", i) >= 0");
    Print(stack);
    return *this;
}

TextStream &TextStream::operator<<(unsigned short us) {
    char stack[1024];
    int res = snprintf(stack, 0x400, "%hu", us);
    if(res < 0) KASSERTSTR_FAIL(0x39, "SNPRINTF(buf, sizeof(buf), \"%hu\", i) >= 0");
    Print(stack);
    return *this;
}

TextStream &TextStream::operator<<(unsigned int ui) {
    char stack[1024];
    int res = snprintf(stack, 0x400, "%u", ui);
    if(res < 0) KASSERTSTR_FAIL(0x3E, "SNPRINTF(buf, sizeof(buf), \"%u\", i) >= 0");
    Print(stack);
    return *this;
}

TextStream &TextStream::operator<<(unsigned long ul) {
    char stack[1024];
    int res = snprintf(stack, 0x400, "%lu", ul);
    if(res < 0) KASSERTSTR_FAIL(0x43, "SNPRINTF(buf, sizeof(buf), \"%lu\", i) >= 0");
    Print(stack);
    return *this;
}

TextStream &TextStream::operator<<(float f) {
    char stack[1024];
    int res = snprintf(stack, 0x400, "%.2f", f);
    if(res < 0) KASSERTSTR_FAIL(0x48, "SNPRINTF(buf, sizeof(buf), \"%.2f\", i) >= 0");
    Print(stack);
    return *this;
}

TextStream &TextStream::operator<<(double d) {
    char stack[1024];
    int res = snprintf(stack, 0x400, "%.4f", d);
    if(res < 0) KASSERTSTR_FAIL(0x48, "SNPRINTF(buf, sizeof(buf), \"%.4f\", i) >= 0");
    Print(stack);
    return *this;
}

TextStream &TextStream::operator<<(const char *c) {
    if(c == 0) KASSERTSTR_FAIL(0x52, "c");
    Print(c);
    return *this;
}

TextStream &TextStream::operator<<(Symbol s) {
    Print(s.mStr);
    return *this;
}

TextStream &TextStream::operator<<(bool b) {
    const char *str = b ? "true" : "false";
    Print(str);
    return *this;
}

void TextStream::Space(int i) {
    while (i != 0) {
        Print(" ");
        i--;
    }
}
