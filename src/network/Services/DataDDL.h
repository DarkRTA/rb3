#pragma once

#include "Platform/RootObject.h"
#include "Platform/String.h"
namespace Quazal {
    class _DDL_Data : public RootObject {
    public:
        _DDL_Data() {}
        virtual ~_DDL_Data() {}
        virtual class Data *Clone() const;
        virtual String GetDataType() const;
        virtual bool IsA(const String &) const;
        virtual bool IsAKindOf(const String &) const;
        virtual void StreamIn(class Message *) const;
        virtual void StreamOut(class Message *);

        _DDL_Data &operator=(const Quazal::_DDL_Data &);
        void Extract(class Message *, class _DDL_Data *);
        void Add(Message *, const _DDL_Data &);
    };
}
