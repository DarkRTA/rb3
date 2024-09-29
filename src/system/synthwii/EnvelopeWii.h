#ifndef SYNTHWII_ENVELOPEWII_H
#define SYNTHWII_ENVELOPEWII_H

#include "system/os/Debug.h"
#include "system/os/Timer.h"

class EnvelopeWii {
public:
    EnvelopeWii();
    ~EnvelopeWii() {}
    float GetValueAtOffset(float);
    bool IsDone();
    void Pause();
    void Resume();
    void StartAttack();
    void StartRelease();

    class Timer mTimer; // 0x0
    float mAttackDuration; // 0x30
    float mReleaseDuration; // 0x34

    bool mInRelease; // 0x38
    bool mIsPaused; // 0x39

    float mReleaseStart; // 0x3C
};

#endif // SYNTHWII_ENVELOPEWII_H