#pragma once
#include "bandtrack/Tail.h"
#include "beatmatch/GameGem.h"
#include "track/TrackWidget.h"
#include "bandtrack/GemRepTemplate.h"
#include "system/utl/TimeConversion.h"
#include "types.h"
#include <functional>

class GemManager;

class Gem {
public:
    Gem(const GameGem &, unsigned int, float, float, bool, int, int, bool);
    ~Gem();
    Gem &operator=(const Gem &);
    bool OnScreen(float);
    void Poll(float, float, float, float, float);
    void AddRep(GemRepTemplate &, RndGroup *, Symbol, const TrackConfig &, bool);
    bool UseRGChordStyle() const;
    void RemoveRep();
    void AddInstance(Symbol, int);
    void AddChordInstance(Symbol);
    void AddStrumInstance(Symbol, Symbol);
    void AddWidgetInstanceImpl(TrackWidget *, int);
    void AddHopoTails(Symbol);
    void RemoveAllInstances();
    void SetType(Symbol);
    void UpdateTailPositions();
    void CreateWidgetInstances(Symbol);
    void Miss();
    void Hit();
    void PartialHit(unsigned int);
    void Release();
    void ApplyDuration(float, float, float);
    void ReleaseSlot(int);
    void KillDuration();
    void Reset();
    float GetStart() const;
    void InitChordInfo(int, bool);
    void SetFretPos(int);
    void GetChordFretLabelInfo(String &, int &) const;

    bool CompareBounds() { return mStart < mEnd ? true : false; }
    bool Check66B0() const { return unk_0x66_7; }
    const GameGem &GetGameGem() const { return mGameGem; }

    GemManager *mGemManager; // 0x0
    const GameGem &mGameGem; // 0x4
    std::set<TrackWidget *> mWidgets; // 0x8
    float mStart; // 0x20
    float mEnd; // 0x24
    float mTailStart; // 0x28
    int mSlots; // 0x2c
    std::vector<Tail *> mTails; // 0x30
    int mBeardTick; // 0x38
    float unk_0x3C; // 0x3c
    float unk_0x40; // 0x40
    unsigned int unk_0x44; // 0x44 - some RG chord shape
    unsigned int unk_0x48; // 0x48 - some other RG chord shape
    class String mChordLabel; // 0x4c
    bool unk_0x58; // 0x58
    int mFirstFret; // 0x5c
    int mFirstFretString; // 0x60
    char mFretPos; // 0x64
    char unk_0x65; // 0x65
    bool mHit : 1;
    bool mMissed : 1;
    bool mReleased : 1;
    bool mHopo : 1;
    bool mInvisible : 1;
    bool mBeard : 1;
    bool unk_0x66_6 : 1;
    bool unk_0x66_7 : 1; // cymbal?
    bool unk_0x67_0 : 1, unk_0x67_1 : 1, unk_0x67_2 : 1, unk_0x67_3 : 1, unk_0x67_4 : 1,
        unk_0x67_5 : 1, unk_0x67_6 : 1, unk_0x67_7 : 1;
};
