#include "string.hpp"
#include "textstream.hpp"
#include "binstream.hpp"
#include "unknown.hpp"
#include "std/string.h"
#include "symbol.hpp"
#include "bufstream.hpp"
#include "bufstreamnand.hpp"
#include "idatachunk.hpp"
#include "cacheid.hpp"
#include "cacheidwii.hpp"

// fn_803431F4
BufStream::BufStream(void *v, int i, bool b) : BinStream(b), unk1c(0), unk20(0) {
    unkc = v;
    unk10 = (v == 0);
    fpos = 0;
    size = i;
}

// fn_80343270
BufStream::~BufStream() {
    DeleteChecksum();
}

// fn_803435E4
void BufStream::WriteImpl(const void *v, int a) {
    if (fpos + a > size) {
        a = size - fpos;
        unk10 = true;
    }
    memcpy((char *)unkc + fpos, v, a);
    fpos += a;
}

// fn_80343658
void BufStream::SeekImpl(int i, SeekType s) {
    int newPos;
    switch (s) {
    case SeekMode0:
        newPos = i;
        break;
    case SeekMode1:
        newPos = fpos + i;
        break;
    case SeekMode2:
        newPos = size + i;
        break;
    default:
        return;
    }

    if ((newPos < 0) || (newPos > size)) {
        unk10 = true;
        return;
    }
    fpos = newPos;
}

// fn_803436BC
const char *BufStream::Name() const {
    if (!name.empty()) {
        return name.c_str();
    }
    return BinStream::Name();
}

// fn_80343708
void BufStream::SetName(const char *c) {
    name = c;
}

// fn_80343710
bool BufStream::Eof() {
    return (size - fpos == 0);
}

// fn_803437A8
BufStreamNAND::~BufStreamNAND() {
}

// fn_8034A03C

#pragma dont_inline on
// fn_80344350
CacheID::CacheID() {
}
#pragma dont_inline reset

// fn_803442FC
CacheIDWii::CacheIDWii() {
}