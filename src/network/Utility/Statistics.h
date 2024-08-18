#pragma once
#include "Platform/RootObject.h"
#include "Platform/SmoothedAverage.h"
#include "types.h"

namespace Quazal {
    class Statistics : public RootObject {
        public:
        Statistics();
        ~Statistics();

        u32 m_uiNbEntries; // 0x0
        float m_dTotal; // 0x4
        float m_dMaximumValue; // 0x8
        float m_dMinimumValue; // 0xC
        SmoothedAverage<float> m_oSmoothedAverage; // 0x10
    };
}
