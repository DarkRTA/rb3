#pragma once

#include "types.h"
namespace Quazal {
    class ErrorDescriptionTable {
    public:
        ErrorDescriptionTable(char **, unsigned int);
        ~ErrorDescriptionTable();

        u32 unk_0x0;
        char **unk_0x4;
    };

    class SystemError {
    public:
        static void SignalError(char *, unsigned int, unsigned int, unsigned int);
    };
}
