#include "Platform/OutputFormat.h"
#include "Platform/Time.h"
#include <string.h>

namespace Quazal {
    OutputFormat::OutputFormat() : m_uiIndent(0), m_uiNumberTrace(0), m_bShowThreadID(false), m_bShowProcessID(false), m_bShowLocalTime(false), 
        m_bShowDateTime(false), m_bShowSessionTime(false), m_bShowSystemThreadName(false), m_bShowLocalStationHandle(false), 
        m_bShowCurrentContext(false), m_bShowCID(false), m_bShowPID(false) {
        Time time;
        time.GetTime();
        m_uiInitTime = (unsigned long long)time;
        m_szPrefix = 0;
    }

    void OutputFormat::StartString(char* str, unsigned int ui){
        *str = '\0';
    }

    void OutputFormat::StartPrefixes(char* str, unsigned int ui){
        
    }
}
