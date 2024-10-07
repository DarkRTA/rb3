#pragma once
#include "ui/UIListProvider.h"
#include "rndobj/Mat.h"
#include "game/BandUser.h"

class SessionUsersProvider : public UIListProvider, public Hmx::Object {
public:
    SessionUsersProvider(bool, bool, bool);
    virtual ~SessionUsersProvider(){}
    virtual void Text(int, int, UIListLabel*, UILabel*) const;
    virtual RndMat* Mat(int, int, UIListMesh*) const;
    virtual int NumData() const;
    virtual void InitData(RndDir*);
    virtual DataNode Handle(DataArray*, bool);

    BandUser* GetUser(int);
    void KickPlayer(BandUser*);
    void ToggleMuteStatus(int);
    void RefreshUserList(const BandUser*, const BandUserMgr*);

    std::vector<int> mUsers; // 0x20
    bool unk28;
    bool unk29;
    bool unk2a;
    RndMat* unk2c;
    RndMat* unk30;
};