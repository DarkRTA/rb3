#ifndef BEATMATCH_BEATMATCHSINK_H
#define BEATMATCH_BEATMATCHSINK_H
#include "beatmatch/BeatMatchControllerSink.h"
#include "beatmatch/Phrase.h"
#include "utl/HxGuid.h"

class BeatMatchSink {
public:
    BeatMatchSink(){}
    virtual ~BeatMatchSink(){}
    virtual void SeeGem(int, float, int) = 0;
    virtual void Swing(int, int, float, bool, bool) = 0;
    virtual void Hit(int, float, int, unsigned int, GemHitFlags) = 0;
    virtual void Miss(int, int, float, int, int, GemHitFlags) = 0;
    virtual void SpuriousMiss(int, int, float, int) = 0;
    virtual void Pass(int, float, int, bool) = 0;
    virtual void Ignore(int, float, int, const UserGuid&) = 0;
    virtual void ImplicitGem(int, float, int, const UserGuid&) = 0;
    virtual void SetTrack(const UserGuid&, int) = 0;
    virtual void FretButtonDown(int, float) = 0;
    virtual void FretButtonUp(int, float) = 0;
    virtual void MercurySwitch(bool, float) = 0;
    virtual void FilteredWhammyBar(float) = 0;
    virtual void SwingAtHopo(int, float, int) = 0;
    virtual void Hopo(int, float, int) = 0;
    virtual void ReleaseGem(int, float, int, float) = 0;
    virtual void SetCurrentPhrase(int, const PhraseInfo&) = 0;
    virtual void NoCurrentPhrase(int) = 0;
    virtual void FillSwing(int, int, int, int, bool) = 0;
    virtual void FillReset() = 0;
    virtual void FillComplete(int, int) = 0;
    virtual void OutOfRangeSwing(){}
    virtual void NoteOn(int){}
    virtual void NoteOff(int){}
    virtual void PlayNote(int){}
};

#endif