#ifndef UTL_SUPERFORMATSTRING_H
#define UTL_SUPERFORMATSTRING_H
#include "utl/MakeString.h"
#include "obj/Data.h"

class SuperFormatString : public FormatString {
public:
    SuperFormatString(const char*, const DataArray*, bool);
    const char* RawFmt() const;
};

#endif
