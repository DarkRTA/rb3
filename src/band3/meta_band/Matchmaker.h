#pragma once
#include "obj/MsgSource.h"

enum MatchmakerFindType {
    kMatchmaker_Qp = 0,
    kMatchmaker_Tour = 1
};

enum SlotRating {
    kRed = 0,
    kYellow = 1,
    kGreen = 2,
    kNumRatings = 3
};

class MatchmakerPoolStats {
public:
    MatchmakerPoolStats();
    void ClearStats();

    int mRatingThresholds[3]; // 0x0, 0x4, 0x8
    SlotRating mSlotRatings[4]; // 0xc, 0x10, 0x14, 0x18
    bool mHasCurrentStats; // 0x1c
};

class MatchmakerMode {
public:
    MatchmakerMode(){}
    virtual ~MatchmakerMode(){}
    virtual bool ShouldSearch() const = 0;
    virtual bool ShouldHost() const = 0;
    virtual int GetNextQueryType() = 0; // might need to change ret type?
};

class QuickFinding : public MatchmakerMode {
public:
    QuickFinding() : mFindType(kMatchmaker_Qp), mAlwaysHost(0), mJoinInProgress(0) {
        mQueryTypes.reserve(3);
    }
    virtual ~QuickFinding(){}
    virtual bool ShouldSearch() const;
    virtual bool ShouldHost() const;
    virtual int GetNextQueryType();

    MatchmakerFindType mFindType; // 0x4
    bool mAlwaysHost; // 0x8
    bool mJoinInProgress; // 0x9
    std::vector<int> mQueryTypes; // 0xc
};

class BandFinding : public MatchmakerMode {
public:
    BandFinding(){}
    virtual ~BandFinding(){}
    virtual bool ShouldSearch() const;
    virtual bool ShouldHost() const;
    virtual int GetNextQueryType();
};

class Matchmaker : public MsgSource {
public:
    Matchmaker();
    virtual DataNode Handle(DataArray*, bool);
    virtual ~Matchmaker();
    virtual void Poll(){}
    virtual bool IsFinding() const = 0;
    virtual void UpdateMatchmakingSettings(){}
    virtual void FindPlayersImpl() = 0;
    virtual void CancelFindImpl() = 0;

    int unk1c;
    int unk20;
    MatchmakerPoolStats* mPoolStats; // 0x24
    QuickFinding* mQuickFindingMode; // 0x28
    BandFinding* mBandFindingMode; // 0x2c
};