#pragma once
#include "game/BandUser.h"
#include "net_band/DataResults.h"
#include "obj/Object.h"
#include "os/OnlineID.h"
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
    }

    IDType mType; // 0x0
    unsigned int mPlayerID; // 0x4
    OnlineID mOnlineID; // 0x8
};

class LeaderboardRow {
public:
    String unk0;
    bool unkc;
    int unk10;
    int unk14;
    bool unk18;
    bool unk19;
    bool unk1a;
    int unk1c;
    int unk20;
    int unk24;
    int unk28;
    OnlineID unk2c;
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

    DataResultList mDataResultList; // 0x20
    std::vector<int> unk38; // 0x38
    int unk40; // 0x40
    bool unk44; // 0x44
    int unk48; // 0x48
    EntityID mEntityID; // 0x4c
    HxGuid mNetBandGuid; // 0x5c
    Callback* mCallback; // 0x6c
    LeaderboardShortcutProvider* mShortcutProvider; // 0x70
    int unk74; // 0x74
    int unk78; // 0x78
    int unk7c; // 0x7c
    int unk80; // 0x80
};

class LeaderboardShortcutProvider : public UIListProvider, public Hmx::Object {
public:
    LeaderboardShortcutProvider(const Leaderboard*);
    virtual ~LeaderboardShortcutProvider(){}
    virtual void Text(int, int, UIListLabel*, UILabel*) const;
    virtual int NumData() const;
    virtual DataNode Handle(DataArray*, bool);
};