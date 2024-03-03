#ifndef UTL_SUPERFORMATSTRING_H
#define UTL_SUPERFORMATSTRING_H
#include "utl/MakeString.h"
#include "obj/Data.h"

class SuperFormatString {
public:
    SuperFormatString(const char*, const DataArray*, bool);
    const FormatString& RawFmt() const;
    FormatString super_FormatString;
};

#endif
