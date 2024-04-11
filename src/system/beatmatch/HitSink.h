#ifndef BEATMATCH_HITSINK_H
#define BEATMATCH_HITSINK_H

enum HitType {
    kPoor = 0,
    kGood = 1,
    kPerfect = 2,
    kNumHitTypes = 3
};

class HitSink {
public:
    HitSink(){}
    virtual ~HitSink(){}
    virtual void Hit(HitType) = 0;
    virtual void Key(int) = 0;
    virtual void RGFret(int, int) = 0;
    virtual void RGStrum(int) = 0;
};

#endif
