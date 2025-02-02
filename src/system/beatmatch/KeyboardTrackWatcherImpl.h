#pragma once
#include "beatmatch/BeatMatchControllerSink.h"
#include "beatmatch/JoypadTrackWatcherImpl.h"

class KeyboardTrackWatcherImpl : public JoypadTrackWatcherImpl {
public:
    class FatFingerData {
    public:
        int unk0; // gem id?
        bool unk4; // gem played?
        float unk8;
        int unkc;
        unsigned int unk10;
        GemHitFlags unk14;
    };
    KeyboardTrackWatcherImpl(int, const UserGuid &, int, SongData *, GameGemList *, TrackWatcherParent *, DataArray *);
    virtual ~KeyboardTrackWatcherImpl();
    virtual void Jump(float);
    virtual void Poll(float);
    virtual void FretButtonDown(int);
    virtual void FretButtonUp(int);
    virtual void OutOfRangeSwing();
    virtual void OnHit(float, int, int, unsigned int, GemHitFlags);
    virtual void OnMiss(float, int, int, unsigned int, GemHitFlags);
    virtual void OnPass(float, int);
    virtual void CodaSwing(int, int);
    virtual int NextGemAfter(int, bool);
    virtual int ClosestUnplayedGem(float, int);
    virtual bool AllowAllInputInRolls() const { return true; }
    virtual void CheckForChordTimeout(float);

    void SwingForTrill(int);
    FatFingerData *FindFatFingerData(int);
    FatFingerData *FindFatFingerDataForSlot(int);
    FatFingerData *FindUnusedFatFingerData();
    int RelevantGem(int, int, int);
    bool CheckForFatFinger(float, int, unsigned int, GemHitFlags);
    bool TrackForgivesFatFingering() const;
    unsigned int MakeNeighboringSlotMask(int) const;
    int GetFatFingerGem(float);
    int GetNeighboringWhiteKeySlot(int, int) const;
    int GetNeighboringBlackKeySlot(int, int) const;
    int GetNeighboring5LaneSlot(int, int) const;

    int unkd4; // 0xd4
    unsigned int mHeldSlots; // 0xd8
    unsigned int unkdc; // 0xdc
    float mMissWindowMs; // 0xe0
    float unke4; // 0xe4
    float mFatFingerWindowMs; // 0xe8
    std::vector<FatFingerData> mFatFingerDatas; // 0xec
};
