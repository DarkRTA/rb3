#pragma once
#include "Platform/RootObject.h"
#include "Platform/String.h"
#include "Platform/Time.h"
#include "qStd.h"

namespace Quazal {
    class ProfilingUnit : public RootObject {
    public:
        ProfilingUnit(const char *, unsigned int);
        ~ProfilingUnit();

        void Reset(const Time &time) {
            unk30 = 0;
            unk0 = 0;
            unk8 = 0;
            unk10 = -1;
            unk18 = 0;
            unk20 = 0;
            unk28 = time;
        }

        static qProtectedList<ProfilingUnit *> s_lstProfilingUnits;
        static unsigned int s_uiNextFreeID;

        unsigned long long unk0;
        unsigned long long unk8;
        unsigned long long unk10;
        unsigned long long unk18;
        unsigned long long unk20;
        Time unk28;
        int unk30;
        unsigned int unk34;
        String unk38;
        bool unk3c;
        bool unk3d;
        short unk3e;
        unsigned int unk40;
    };
}