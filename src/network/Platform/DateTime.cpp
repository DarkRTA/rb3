#include "Platform/DateTime.h"

namespace Quazal {
    const DateTime& DateTime::Never = DateTime(); // yeah sure

    DateTime::DateTime() : m_ui64Value(0) {

    }

    DateTime::DateTime(const DateTime& dt) : m_ui64Value(dt.m_ui64Value) {

    }

    DateTime& DateTime::operator=(const DateTime& dt){
        m_ui64Value = dt.m_ui64Value;
    }

    DateTime::operator unsigned long long() const {
        return m_ui64Value;
    }

    bool DateTime::operator>(const DateTime& dt) const {
        return m_ui64Value > dt.m_ui64Value;
    }

    unsigned int DateTime::GetYear() const {
        return (m_ui64Value & 0xFFFC000000) >> 26; // years: bits 26-39
    }

    unsigned int DateTime::GetMonth() const {
        return (m_ui64Value & 0x3C00000) >> 22; // months: bits 22-25
    }

    unsigned int DateTime::GetDay() const {
        return (m_ui64Value & 0x3E0000) >> 17; // days: bits 17-21
    }

    unsigned int DateTime::GetHour() const {
        return (m_ui64Value & 0x1F000) >> 12; // hours: bits 12-17
    }

    unsigned int DateTime::GetMinute() const {
        return (m_ui64Value & 0xFC0) >> 6; // minutes: bits 6-11
    }

    unsigned int DateTime::GetSecond() const {
        return m_ui64Value & 0x3F; // seconds: bits 0-5
    }

    void DateTime::GetSystemTime(DateTime&) {
        
    }
}
