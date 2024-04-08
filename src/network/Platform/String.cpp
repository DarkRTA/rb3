#include "Platform/String.h"
#include "Platform/MemoryManager.h"
#include <string.h>

namespace Quazal {

    String::String(){
        unsigned int size = strlen("");
        void* v = QUAZAL_DEFAULT_ALLOC(size + 5, 0x2F, _InstType9);
    }

}
