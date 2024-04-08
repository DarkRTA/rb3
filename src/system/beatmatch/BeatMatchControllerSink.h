#ifndef BEATMATCH_BEATMATCHCONTROLLERSINK_H
#define BEATMATCH_BEATMATCHCONTROLLERSINK_H

enum GemHitFlags {
    kGemHitFlagNone = 0x0,
    kGemHitFlagHopo = 0x1,
    kGemHitFlagSolo = 0x2,
    kGemHitFlagCymbal = 0x4,
    kGemHitFlagUpstrum = 0x8,
    kGemHitFlagNoPenalize = 0x10,
    kGemHitFlagAutoplay = 0x20
};

class BeatMatchControllerSink {
public:
    BeatMatchControllerSink(){}
    virtual ~BeatMatchControllerSink(){}
    virtual int Swing(int, bool, bool, bool, bool, GemHitFlags){ return 0; }
    virtual void ReleaseSwing(){}
    virtual void NonStrumSwing(int, bool, bool){}
    virtual float MercurySwitch(float f){ return f; }
    virtual void ForceMercurySwitch(bool){}
    virtual void FretButtonDown(int, int){}
    virtual void FretButtonUp(int){}
    virtual void RGFretButtonDown(int){}
    virtual void SetController(class BeatMatchController*){}
    virtual void Sweep(unsigned char){}
    virtual void NoteOn(int){}
    virtual void NoteOff(int){}
    virtual void PlayNote(int){}
    virtual void OutOfRangeSwing(){}
};

#endif
