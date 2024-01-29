#include "intpacker.hpp"
#include "string.h"

IntPacker::IntPacker(void* v, unsigned int ui){
    unk0 = v;
    pos = 0;
    unk8 = ui;
    memset(v, 0, ui);
}