#pragma once
#include "game/BandUser.h"
#include "game/Defines.h"
#include "net_band/DataResults.h"
#include "obj/Object.h"
#include "os/Debug.h"
#include "os/OnlineID.h"
#include "ui/UIColor.h"
#include "ui/UIListProvider.h"

enum IDType {
    kInvalid = 0,
    kPlayerID = 1
};

class EntityID {
public:
    EntityID() : mType(kInvalid) {}
    EntityID(const EntityID& id){
        *this = id;
    }

    EntityID& operator=(const EntityID& id){
        mType = id.mType;
        mPlayerID = id.mPlayerID;
        mOnlineID = id.mOnlineID;
        return *this;
    }

    unsigned int GetPlayerID() const {
        MILO_ASSERT(kPlayerID == mType, 0x59);
        return mPlayerID;
    }

    IDType mType; // 0x0
    unsigned int mPlayerID; // 0x4
    OnlineID mOnlineID; // 0x8
};

class LeaderboardRow {
public:
    LeaderboardRow();

    String unk0; // 0x0
    bool unkc; // 0xc
    int unk10; // 0x10
    int unk14; // 0x14
    bool unk18; // 0x18
    bool unk19; // 0x19
    bool unk1a; // 0x1a
    int unk1c; // 0x1c
    int unk20; // 0x20
    int unk24; // 0x24
    short unk28; // 0x28
    OnlineID unk2c; // 0x2c
};

enum EnumState {
    kEnumInactive = 0,
    kEnumWaiting = 1,
    kEnumFailure = 2,
    kEnumSuccess = 3,
    kEnumDone = 4
};

enum LeaderboardMode {
    kPercentile = 0,
    kFriends = 1,
    kRank = 2
};

class LeaderboardShortcutProvider;

class Leaderboard : public UIListProvider, public Hmx::Object {
public:
    class Callback {
    public:
        Callback(){}
        virtual ~Callback(){}
        virtual void EnumerationStarted(){}
        virtual void ResultSuccess(bool, bool, bool){}
        virtual void ResultFailure(){}
    };

    Leaderboard(EntityID, Callback*);
    virtual ~Leaderboard();
    virtual void Text(int, int, UIListLabel*, UILabel*) const;
    virtual RndMat* Mat(int, int, UIListMesh*) const;
    virtual void Custom(int, int, class UIListCustom*, Hmx::Object*) const;
    virtual int NumData() const;
    virtual void InitData(RndDir*);
    virtual UIColor* SlotColorOverride(int, int, class UIListWidget*, UIColor* c) const;
    virtual DataNode Handle(DataArray*, bool);
    virtual bool IsEnumComplete() const;
    virtual void StartEnumerate();
    virtual void CancelEnumerate();
    virtual void Poll();
    virtual void OnEnumComplete();
    virtual void EnumerateFromID() = 0;
    virtual void EnumerateRankRange(int, int) = 0;
    virtual void GetStats() = 0;
    virtual Symbol OnSelectRow(int, BandUser*) = 0;
    virtual bool CanRowsBeSelected() const = 0;
    virtual bool IsRowFriend(int) const = 0;
    virtual bool IsRowSelf(int) const = 0;
    virtual bool ShowsDifficultyAndPct() const;

    int GetSelfRow() const;
    void ShowData();
    bool EnumerateHigherRankRange();
    bool EnumerateLowerRankRange();
    int GetStartingRow() const;

    DataResultList mDataResultList; // 0x20
    std::vector<LeaderboardRow> mLeaderboardRows; // 0x38
    int unk40; // 0x40
    bool mHasStats; // 0x44
    int unk48; // 0x48
    EntityID mEntityID; // 0x4c
    HxGuid mNetBandGuid; // 0x5c
    Callback* mCallback; // 0x6c
    LeaderboardShortcutProvider* mShortcutProvider; // 0x70
    EnumState mEnumState; // 0x74
    UIColor* mSelfColor; // 0x78
    UIColor* mFriendColor; // 0x7c
    int unk80; // 0x80
};

class LeaderboardShortcutProvider : public UIListProvider, public Hmx::Object {
public:
    LeaderboardShortcutProvider(const Leaderboard*);
    virtual ~LeaderboardShortcutProvider(){}
    virtual void Text(int, int, UIListLabel*, UILabel*) const;
    virtual int NumData() const;
    virtual DataNode Handle(DataArray*, bool);

    void UpdateIndices();

    int unk20; // 0x20
    std::vector<int> unk24; // 0x24
};