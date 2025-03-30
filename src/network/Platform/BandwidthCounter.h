#pragma once
#include "Platform/CriticalSection.h"
#include "Platform/RootObject.h"
#include "Platform/String.h"
#include "Platform/qStd.h"

namespace Quazal {
    class BandwidthCounter {
    public:
        BandwidthCounter(const String &);
        void operator+=(unsigned int);
        static qChain<BandwidthCounter *> s_lstBWCounters;
        static CriticalSection s_cs;

        void *unk0; // 0x0 - Links*?
        void *unk4; // 0x4
        String mName; // 0x8
        unsigned int mMin; // 0xc
        unsigned int mMax; // 0x10
        unsigned int mTotal; // 0x14
        unsigned int mOccurences; // 0x18
    };

    class BandwidthCounterMap : public RootObject {
    public:
        class IOBandwidthCounter {
        public:
            IOBandwidthCounter(const String &str);

            BandwidthCounter mIncoming; // 0x0
            BandwidthCounter mOutgoing; // 0x1c
        };
        BandwidthCounterMap(const String &);
        ~BandwidthCounterMap();
        IOBandwidthCounter *operator[](unsigned int);

        String mName; // 0x0
        qMap<unsigned int, IOBandwidthCounter *> mMap; // 0x4
    };
}