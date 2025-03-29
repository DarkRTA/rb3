#pragma once
#include "Platform/RootObject.h"

namespace Quazal {
    class _DDL_ResultRange : public RootObject {
    public:
        _DDL_ResultRange() {}
        virtual ~_DDL_ResultRange() {}

        unsigned int mOffset; // 0x4
        unsigned int mSize; // 0x8
    };

    class ResultRange : public _DDL_ResultRange {
    public:
        ResultRange(unsigned int o, unsigned int s) {
            mOffset = o;
            mSize = s;
        }
        virtual ~ResultRange() {}
        virtual unsigned int GetOffset() const { return mOffset; }
        virtual unsigned int GetSize() const { return mSize; }
    };
}