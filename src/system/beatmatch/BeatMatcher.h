#ifndef BEATMATCH_BEATMATCHER_H
#define BEATMATCH_BEATMATCHER_H
#include "beatmatch/BeatMatchControllerSink.h"
#include "beatmatch/TrackWatcherParent.h"
#include "utl/HxGuid.h"
#include "utl/Symbol.h"
#include "utl/SongInfoCopy.h"

// forward decs
class SongData;
class DataArray;
class BeatMaster;

class BeatMatcher : public TrackWatcherParent, public BeatMatchControllerSink {
public:
    BeatMatcher(const UserGuid&, int, int, Symbol, SongData*, SongInfo&, DataArray*, BeatMaster*);
    virtual ~BeatMatcher();
    virtual float GetNow() const;
    virtual int GetTick() const;
    virtual float GetWhammyBar() const;
    virtual int GetMaxSlots() const;
    virtual void SetPitchBend(int, float, bool);
    virtual void ResetPitchBend(int);
    virtual bool InFillNow();
    virtual bool InFill(int, bool);
    virtual bool FillsEnabled(int);
    virtual int GetFillLogic() const;
    virtual bool InSolo(int);
    virtual bool InCoda(int);
    virtual bool InCodaFreestyle(int, bool);
    virtual void SetButtonMashingMode(bool);
    virtual int GetVelocityBucket(int);
    virtual int GetVirtualSlot(int);
    virtual void PlayDrum(int, bool, float);

    virtual void FretButtonDown(int, int);
    virtual void FretButtonUp(int);
    virtual void RGFretButtonDown(int);
    virtual int Swing(int, bool, bool, bool, bool, GemHitFlags);
    virtual void ReleaseSwing();
    virtual void NonStrumSwing(int, bool, bool);
    virtual float MercurySwitch(float);
    virtual void ForceMercurySwitch(bool);
    virtual void SetController(class BeatMatchController*);
    virtual void NoteOn(int);
    virtual void NoteOff(int);
    virtual void PlayNote(int);
    virtual void OutOfRangeSwing();

    virtual void SetTrack(int);
    virtual float GetCapStrip() const;

    int dummy;
};

#endif