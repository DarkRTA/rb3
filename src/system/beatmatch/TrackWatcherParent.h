#ifndef BEATMATCH_TRACKWATCHERPARENT_H
#define BEATMATCH_TRACKWATCHERPARENT_H

class TrackWatcherParent {
public:
    TrackWatcherParent(){}
    virtual ~TrackWatcherParent(){}
    virtual float GetNow() const = 0;
    virtual int GetTick() const = 0;
    virtual float GetWhammyBar() const = 0;
    virtual int GetMaxSlots() const = 0;
    virtual void SetPitchBend(int, float, bool) = 0;
    virtual void ResetPitchBend(int) = 0;
    virtual bool InFillNow() = 0;
    virtual bool InFill(int, bool) = 0;
    virtual bool FillsEnabled(int) = 0;
    virtual int GetFillLogic() const = 0;
    virtual bool InSolo(int) = 0;
    virtual bool InCoda(int) = 0;
    virtual bool InCodaFreestyle(int, bool) = 0;
    virtual void SetButtonMashingMode(bool) = 0;
    virtual int GetVelocityBucket(int) = 0;
    virtual int GetVirtualSlot(int) = 0;
    virtual void PlayDrum(int, bool, float) = 0;
};

#endif
