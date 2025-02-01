#pragma once
#include "utl/Symbol.h"

const char *AlphaKeySkip(const char *, bool);
void CalculateAlphaKey(char *, const char *, bool);
int AlphaKeyStrCmp(const char *, const char *, bool);
Symbol FirstSortChar(const char *, bool);
