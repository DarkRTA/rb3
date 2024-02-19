#include "utl/TextStream.h"
#include "os/Debug.h"
#include <stdio.h>
#define SNPRINTF snprintf

TextStream::TextStream() {

}

TextStream &TextStream::operator<<(char i) {
    char buf[1024];
    ASSERT(SNPRINTF(buf, sizeof(buf), "%c", i) >= 0, 0x20);
    Print(buf);
    return *this;
}

TextStream &TextStream::operator<<(short i) {
    char buf[1024];
    ASSERT(SNPRINTF(buf, sizeof(buf), "%hd", i) >= 0, 0x25);
    Print(buf);
    return *this;
}

TextStream &TextStream::operator<<(int i) {
    char buf[1024];
    ASSERT(SNPRINTF(buf, sizeof(buf), "%d", i) >= 0, 0x2A);
    Print(buf);
    return *this;
}

TextStream &TextStream::operator<<(long i) {
    char buf[1024];
    ASSERT(SNPRINTF(buf, sizeof(buf), "%ld", i) >= 0, 0x2F);
    Print(buf);
    return *this;
}

TextStream &TextStream::operator<<(unsigned char i) {
    char buf[1024];
    ASSERT(SNPRINTF(buf, sizeof(buf), "%u", i) >= 0, 0x34);
    Print(buf);
    return *this;
}

TextStream &TextStream::operator<<(unsigned short i) {
    char buf[1024];
    ASSERT(SNPRINTF(buf, sizeof(buf), "%hu", i) >= 0, 0x39);
    Print(buf);
    return *this;
}

TextStream &TextStream::operator<<(unsigned int i) {
    char buf[1024];
    ASSERT(SNPRINTF(buf, sizeof(buf), "%u", i) >= 0, 0x3E);
    Print(buf);
    return *this;
}

TextStream &TextStream::operator<<(unsigned long i) {
    char buf[1024];
    ASSERT(SNPRINTF(buf, sizeof(buf), "%lu", i) >= 0, 0x43);
    Print(buf);
    return *this;
}

TextStream &TextStream::operator<<(float i) {
    char buf[1024];
    ASSERT(SNPRINTF(buf, sizeof(buf), "%.2f", i) >= 0, 0x48);
    Print(buf);
    return *this;
}

TextStream &TextStream::operator<<(double i) {
    char buf[1024];
    ASSERT(SNPRINTF(buf, sizeof(buf), "%.4f", i) >= 0, 0x4D);
    Print(buf);
    return *this;
}

TextStream &TextStream::operator<<(const char *c) {
    ASSERT(c, 0x52);
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
