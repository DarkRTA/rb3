#include "network/Plugins/StreamSettings.h"
#include "Platform/Result.h"

namespace Quazal {
    StreamSettings::StreamSettings() {
        unk0 = 0;
        unk4 = 0;
        unk8 = 0;
        mMaxRetransmission = 20;
        mMaxSilenceTime = 5000;
        mKeepAliveTimeout = 1000;
        mRetransmitTimeoutMultiplier = 1.25f;
        mExtraRetransmitTimeoutMultiplier = 1;
        mExtraRetransmitTimeoutTrigger = 50;
        mWindowSize = 8;
        mInitialRTT = 250;
        mRTTRetransmit = 50;
        mActiveFaultDetection = true;
        unk4e = false;
    }

    StreamSettings::~StreamSettings() {}

    unsigned int StreamSettings::GetWindowSize() const { return mWindowSize; }
    unsigned int StreamSettings::GetMaxRetransmission() const {
        return mMaxRetransmission;
    }

    qResult StreamSettings::SetKeepAliveTimeout(unsigned int ui) {
        mKeepAliveTimeout = ui;
        return 0x10001;
    }

    unsigned int StreamSettings::GetKeepAliveTimeout() const { return mKeepAliveTimeout; }

    qResult StreamSettings::SetMaxSilenceTime(unsigned int ui) {
        mMaxSilenceTime = ui;
        return 0x10001;
    }

    unsigned int StreamSettings::GetMaxSilenceTime() const { return mMaxSilenceTime; }
    float StreamSettings::GetRetransmitTimeoutMultiplier() {
        return mRetransmitTimeoutMultiplier;
    }

    float StreamSettings::GetExtraRetransmitTimeoutMultiplier() {
        return mExtraRetransmitTimeoutMultiplier;
    }

    unsigned int StreamSettings::GetExtraRetransmitTimeoutTrigger() {
        return mExtraRetransmitTimeoutTrigger;
    }

    unsigned int StreamSettings::GetInitialRTT() { return mInitialRTT; }
    unsigned int StreamSettings::GetRTTRetransmit() { return mRTTRetransmit; }
    bool StreamSettings::FaultDetectionIsActive() { return mActiveFaultDetection; }
}