#ifndef UTL_UTF8_H
#define UTL_UTF8_H
#include "utl/Str.h"

unsigned int DecodeUTF8(unsigned short&, const char*);
unsigned int EncodeUTF8(String&, unsigned int);

#endif
