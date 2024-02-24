#ifndef OBJ_UTL_H
#define OBJ_UTL_H
#include "utl/Symbol.h"

// forward declaration
namespace Hmx {
    class Object;
}

void InitObject(Hmx::Object*);
const char* PathName(const Hmx::Object*);
const char* SafeName(Hmx::Object*);

bool RecurseSuperClassesSearch(Symbol, Symbol);
bool IsASubclass(Symbol, Symbol);

// mergefilter classes go here

#endif
