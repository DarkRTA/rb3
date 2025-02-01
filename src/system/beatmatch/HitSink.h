#ifndef BEATMATCH_HITSINK_H
#define BEATMATCH_HITSINK_H

enum HitType {
    kHitGreenPad = 0,
    kHitRedPad = 1,
    kHitYellowPad = 2,
    kHitBluePad = 3,
    kHitGreenFret = 4,
    kHitRedFret = 5,
    kHitYellowFret = 6,
    kHitBlueFret = 7,
    kHitOrangeFret = 8,
    kHitHighGreenFret = 9,
    kHitHighRedFret = 10,
    kHitHighYellowFret = 11,
    kHitHighBlueFret = 12,
    kHitHighOrangeFret = 13,
    kHitKick = 14,
    kHitYellowCymbal = 15,
    kHitBlueCymbal = 16,
    kHitGreenCymbal = 17,
    kHitUpstrum = 18,
    kHitDownstrum = 19,
    kHitStart = 20,
    kHitSelect = 21,
    kNumHitTypes = 22
};

class HitSink {
public:
    HitSink() {}
    virtual ~HitSink() {}
    virtual void Hit(HitType) = 0;
    virtual void Key(int) = 0;
    virtual void RGFret(int, int) = 0;
    virtual void RGStrum(int) = 0;
};

#endif
