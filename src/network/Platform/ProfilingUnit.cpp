#include "network/Platform/ProfilingUnit.h"
#include "Platform/ScopedCS.h"

namespace Quazal {
    qProtectedList<ProfilingUnit *> ProfilingUnit::s_lstProfilingUnits;
    unsigned int ProfilingUnit::s_uiNextFreeID;

    ProfilingUnit::ProfilingUnit(const char *cc, unsigned int ui) : unk38(cc) {
        Reset(Time::GetTime());
        unk3c = 0;
        unk34 = ui;
        unk3e = 0;
        ScopedCS cs(s_lstProfilingUnits.mCSList);
        {
            ScopedCS cs2(s_lstProfilingUnits.mCSList);
            s_lstProfilingUnits.mOList.push_back(this);
        }
        unk40 = s_uiNextFreeID;
        s_uiNextFreeID++;
    }

    ProfilingUnit::~ProfilingUnit() {}
}