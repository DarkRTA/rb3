#pragma once
#include "utl/Symbol.h"

struct WeightedEntry {
    WeightedEntry(int i, Symbol s, const char *c) : unk0(i), unk4(s), unk8(c) {}
    int unk0;
    Symbol unk4;
    const char *unk8;
};

void ContextCheckerInit();