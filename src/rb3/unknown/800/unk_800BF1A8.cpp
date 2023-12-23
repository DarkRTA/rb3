#include "string.hpp"
#include "filestream.hpp"
#include "unknown.hpp"
#include "std/string.h"

// fn_800C20FC
// probably inlined
const char *FileStream::Name() const {
    return fname.c_str();
}