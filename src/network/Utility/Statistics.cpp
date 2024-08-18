#include "Statistics.h"

namespace Quazal {
    Statistics::Statistics() : m_oSmoothedAverage(0.1) {
        m_uiNbEntries = 0;

        m_dTotal = 0;
        m_dMaximumValue = 0;
        m_dMinimumValue = 0;

        // fake it 'til you make it
        m_oSmoothedAverage.m_dAverage = 0;
        m_oSmoothedAverage.m_dTotalWeightOfEntries = 0;
    }

    Statistics::~Statistics() {} 
}
