#include "DataDDL.h"
#include "Data.h"

namespace Quazal {
    _DDL_Data &_DDL_Data::operator=(const _DDL_Data &) { return *this; }

    void _DDL_Data::Add(Message *, const _DDL_Data &) {}
    void _DDL_Data::Extract(Message *, _DDL_Data *) {}
    Data *_DDL_Data::Clone() const { return new (__FILE__, 25) Data; }

    String _DDL_Data::GetDataType() const { return String("Data"); }
    bool _DDL_Data::IsA(const Quazal::String &s) const {
        return String::IsEqual(s.m_szContent, "Data");
    }
    bool _DDL_Data::IsAKindOf(const Quazal::String &s) const {
        return String::IsEqual(s.m_szContent, "Data");
    }

    void _DDL_Data::StreamIn(class Message *) const {}
    void _DDL_Data::StreamOut(class Message *) {}
}
