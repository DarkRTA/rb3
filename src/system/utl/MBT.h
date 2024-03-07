#ifndef UTL_MBT_H
#define UTL_MBT_H
#include "utl/MeasureMap.h"

void ParseMBT(const char*, int&, int&, int&);
const char* TickFormat(int, const MeasureMap&);
const char* FormatTimeMSH(float);

#endif
