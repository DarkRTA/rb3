#pragma once
#include "obj/Msg.h"
#include "os/Timer.h"
#include <algorithm>

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
    SlotRating GetSlotRating(int) const;
    bool HasCurrentStats() const { return mHasCurrentStats; }

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
    virtual bool ShouldSearch() const { return !mAlwaysHost; }
    virtual bool ShouldHost() const { return true; }
    virtual int GetNextQueryType();

    void Init(MatchmakerFindType ty){
        mQueryTypes.clear();
        mFindType = ty;
        switch(ty){
            case 0:
                mQueryTypes.push_back(2);
                break;
            case 1:
                mQueryTypes.push_back(3);
                break;
            default:
                MILO_FAIL("Unknown MatcmakerFindType");
                break;
        }
        std::random_shuffle(mQueryTypes.begin(), mQueryTypes.end());
    }

    MatchmakerFindType mFindType; // 0x4
    bool mAlwaysHost; // 0x8
    bool mJoinInProgress; // 0x9
    std::vector<int> mQueryTypes; // 0xc
};

class BandFinding : public MatchmakerMode {
public:
    BandFinding(){}
    virtual ~BandFinding(){}
    virtual bool ShouldSearch() const { return true; }
    virtual bool ShouldHost() const { return false; }
    virtual int GetNextQueryType() { return 0; }
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

    void CancelFind();
    void SetQuickFindingMode(MatchmakerFindType);
    void FindPlayers(MatchmakerFindType);
    bool IsHostingQp() const;
    bool IsHostingTour() const;

    MatchmakerMode* mMode; // 0x1c
    int unk20;
    MatchmakerPoolStats* mPoolStats; // 0x24
    QuickFinding* mQuickFindingMode; // 0x28
    BandFinding* mBandFindingMode; // 0x2c
};

class BandMatchmaker : public Matchmaker {
public:
    BandMatchmaker();
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual ~BandMatchmaker();
    virtual void Poll();
    virtual bool IsFinding() const;
    virtual void UpdateMatchmakingSettings();
    virtual void FindPlayersImpl();
    virtual void CancelFindImpl();

    bool mSearching; // 0x30
    bool unk31; // 0x31
    bool unk32; // 0x32
    Timer mTime; // 0x38
    float mSearchingInterval; // 0x68
    float unk6c; // 0x6c
    int mDevChannel; // 0x70
};

class MatchmakerChangedMsg : public Message {
public:
    MatchmakerChangedMsg() : Message(Type()) {}
    MatchmakerChangedMsg(DataArray *da) : Message(da) {}
    virtual ~MatchmakerChangedMsg() {}
    static Symbol Type() {
        static Symbol t("matchmaker_changed");
        return t;
    }
};