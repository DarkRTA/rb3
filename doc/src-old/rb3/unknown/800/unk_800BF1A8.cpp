#include <string.h>

#include "utl/FileStream.h"
#include "utl/Str.h"

#include "unknown.hpp"

// fn_800C20FC
// probably inlined
const char *FileStream::Name() const {
    return fname.c_str();
}
