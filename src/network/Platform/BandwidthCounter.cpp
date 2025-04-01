#include "network/Platform/BandwidthCounter.h"
#include "Platform/CriticalSection.h"
#include "Platform/ScopedCS.h"
#include "Platform/String.h"

namespace Quazal {

    qChain<BandwidthCounter *> BandwidthCounter::s_lstBWCounters;
    CriticalSection BandwidthCounter::s_cs(0x40000000);

    BandwidthCounter::BandwidthCounter(const String &str)
        : unk0(0), unk4(0), mName(str), mMin(-1), mMax(0), mTotal(0), mOccurences(0) {
        ScopedCS scs(s_cs);
        s_lstBWCounters.push_back(this);
    }

    void BandwidthCounter::operator+=(unsigned int ui) {
        mTotal += ui;
        mOccurences++;
        if (ui < mMin) {
            mMin = ui;
        }
        if (ui > mMax) {
            mMax = ui;
        }
    }

    BandwidthCounterMap::BandwidthCounterMap(const String &str) : mName(str) {}

    Quazal::BandwidthCounterMap::~BandwidthCounterMap() {}

    BandwidthCounterMap::IOBandwidthCounter::IOBandwidthCounter(const String &str)
        : mIncoming(str + "/Incoming"), mOutgoing(str + "/Outgoing") {}

    BandwidthCounterMap::IOBandwidthCounter *
    BandwidthCounterMap::operator[](unsigned int key) {
        qMap<unsigned int, IOBandwidthCounter *>::iterator it = mMap.find(key);
        if (it != mMap.end())
            return it->second;
        else {
            String str;
            str.Format("%s %d", mName.m_szContent, key);
            IOBandwidthCounter *iobc = new IOBandwidthCounter(str);
            mMap[key] = iobc;
            return iobc;
        }
    }

}