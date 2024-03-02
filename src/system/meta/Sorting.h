#ifndef META_SORTING_H
#define META_SORTING_H
#include "utl/Symbol.h"

const char* AlphaKeySkip(const char*, bool);
void CalculateAlphaKey(char*, const char*, bool);
int AlphaKeyStrCmp(const char*, const char*, bool);
Symbol FirstSortChar(const char*, bool);

#endif
