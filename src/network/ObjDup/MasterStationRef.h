#pragma once
#include "DORef.h"

namespace Quazal {
    class MasterStationRef : public DORef {
    public:
        MasterStationRef();

        bool unk9; // should be LogicalClockTmpl<uchar>
    };
}