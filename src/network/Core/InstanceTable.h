#pragma once

namespace Quazal {
    class InstanceControl;

    class InstanceTable {
    public:
        bool AddInstance(InstanceControl *, unsigned int, unsigned int);

        static InstanceTable *s_oInstanceTable;
    };
}