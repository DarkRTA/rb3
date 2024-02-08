#ifndef HMX_OBJUTIL_HPP
#define HMX_OBJUTIL_HPP
#include "hmx/object.hpp"
#include "Symbol.h"

void InitObject(Hmx::Object*);
char* PathName(const Hmx::Object*);
const char* SafeName(Hmx::Object*);

bool RecurseSuperClassesSearch(Symbol, Symbol);
bool IsASubclass(Symbol, Symbol);

#endif
