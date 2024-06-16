#ifndef BANDTRACK_GEM_H
#define BANDTRACK_GEM_H

#include "bandtrack/GemManager.h"
#include "bandtrack/Tail.h"
#include "beatmatch/GameGem.h"
#include "track/TrackWidget.h"
#include "types.h"
#include <functional>

class Gem {
    public:
    Gem(const GameGem&, unsigned int, float, float, bool, int, int, bool);
    ~Gem();
    Gem& operator=(const Gem&);
    bool OnScreen(float);
    void Poll(float, float, float, float, float);
    // void AddRep(GemRepTemplate&, RndGroup*, Symbol, const TrackConfig&, bool);
    bool UseRGChordStyle() const;
    void RemoveRep();
    void AddInstance(Symbol, int);
    void AddChordInstance(Symbol);
    void AddStrumInstance(Symbol, Symbol);
    void AddWidgetInstanceImpl(TrackWidget*, int);
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
    void GetChordFretLabelInfo(String&, int&) const;

    GemManager* mGemManager;
    const GameGem* mGameGem;
    std::set<TrackWidget*> mWidgets;
    float mStart, mEnd, mTailStart;
    int mSlots;
    std::vector<Tail*> mTails;
    int mBeardTick;
    float unk_0x3C, unk_0x40;
    int unk_0x44, unk_0x48;
    class String unk_0x4C;
    u8 unk_0x58;
    int mFirstFret, mFirstFretString;
    u8 mFretPos, unk_0x65;
    bool mHit : 1;
    bool mMissed : 1;
    bool mReleased : 1;
    bool mHopo : 1;
    bool mInvisible : 1;
    bool mBeard : 1;
    bool unk_0x66_6 : 1, unk_0x66_7 : 1;
    bool unk_0x67_0 : 1, unk_0x67_1 : 1, unk_0x67_2 : 1, unk_0x67_3 : 1, unk_0x67_4 : 1, unk_0x67_5 : 1, unk_0x67_6 : 1, unk_0x67_7 : 1;
};

#endif // BANDTRACK_GEM_H
