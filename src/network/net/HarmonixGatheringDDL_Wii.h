#pragma once

#include "Plugins/Buffer.h"
#include "Services/Gathering.h"
namespace Quazal {
    class _DDL_HarmonixGathering : public Gathering {
    public:
        _DDL_HarmonixGathering() {}
        virtual ~_DDL_HarmonixGathering() {}
        virtual Gathering *Clone() const;
        virtual String GetGatheringType() const;
        virtual bool IsA(const String &) const;
        virtual bool IsAKindOf(const String &) const;
        virtual void StreamIn(Message *) const;
        virtual void StreamOut(Message *);

        bool unk28;
        int unk2c;
        int unk30;
        int unk34;
        int unk38;
        int unk3c;
        int unk40;
        int unk44;
        int unk48;
        int unk4c;
        int unk50;
        int unk54;
        Buffer unk58; // 0x58
    };

    class HarmonixGathering : public _DDL_HarmonixGathering {
    public:
        HarmonixGathering() {}
        virtual ~HarmonixGathering() {}
    };
}