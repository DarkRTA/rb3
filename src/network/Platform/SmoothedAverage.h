#pragma once

#include "network/Platform/RootObject.h"

namespace Quazal {
    template <typename T>
    class SmoothedAverage : public RootObject {
        public:
        SmoothedAverage(T t) : m_dAverage(0), m_dWeight(0), m_dTotalWeightOfEntries(0) { m_dWeight = t; }
        T m_dAverage; // 0x0    
        T m_dWeight; // 0x4
        T m_dTotalWeightOfEntries; // 0x8
    };
}