#pragma once
#include "Platform/Result.h"
#include "Platform/RootObject.h"
#include "Platform/String.h"
#include "Plugins/StreamBundling.h"

namespace Quazal {
    class StreamSettings : public RootObject {
    public:
        StreamSettings();
        ~StreamSettings();

        void SetKey(const String &);
        unsigned int GetWindowSize() const;
        unsigned int GetMaxRetransmission() const;
        qResult SetKeepAliveTimeout(unsigned int);
        unsigned int GetKeepAliveTimeout() const;
        qResult SetMaxSilenceTime(unsigned int);
        unsigned int GetMaxSilenceTime() const;
        float GetRetransmitTimeoutMultiplier();
        float GetExtraRetransmitTimeoutMultiplier();
        unsigned int GetExtraRetransmitTimeoutTrigger();
        unsigned int GetInitialRTT();
        unsigned int GetRTTRetransmit();
        bool FaultDetectionIsActive();

        unsigned char unk0; // 0x0
        int unk4; // 0x4
        int unk8; // 0x8
        StreamBundling mBundling; // 0x10
        unsigned int mMaxRetransmission; // 0x28
        unsigned int mKeepAliveTimeout; // 0x2c
        unsigned int mMaxSilenceTime; // 0x30
        unsigned int mWindowSize; // 0x34
        float mRetransmitTimeoutMultiplier; // 0x38
        float mExtraRetransmitTimeoutMultiplier; // 0x3c
        unsigned int mExtraRetransmitTimeoutTrigger; // 0x40
        unsigned int mInitialRTT; // 0x44
        unsigned int mRTTRetransmit; // 0x48
        bool unk4c;
        bool mActiveFaultDetection; // 0x4d
        bool unk4e;
    };
}