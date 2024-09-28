#ifndef SYNTHWII_ENVELOPEWII_H
#define SYNTHWII_ENVELOPEWII_H

#include "system/os/Timer.h"

class EnvelopeWii {
public:
    EnvelopeWii();
    virtual ~EnvelopeWii() {}
    class Timer mTimer;

    float mAttackDuration;
    float mReleaseDuration;
    bool mInRelease;
    bool mIsPaused;

    float mReleaseStart;
};

#endif // SYNTHWII_ENVELOPEWII_H