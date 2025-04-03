#pragma once
#include "Platform/RootObject.h"
#include "Platform/String.h"
#include "Plugins/Message.h"

namespace Quazal {
    class Gathering;

    class _DDL_Gathering : public RootObject {
    public:
        _DDL_Gathering();
        virtual ~_DDL_Gathering() {}
        virtual Gathering *Clone() const;
        virtual String GetGatheringType() const;
        virtual bool IsA(const String &) const;
        virtual bool IsAKindOf(const String &) const;
        virtual void StreamIn(Message *) const;
        virtual void StreamOut(Message *);

        int unk4;
        int unk8;
        int unkc;
        short unk10;
        short unk12;
        int unk14;
        int unk18;
        int unk1c;
        int unk20;
        String unk24;
    };
}