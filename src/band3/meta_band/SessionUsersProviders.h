#pragma once
#include "ui/UIListProvider.h"
#include "rndobj/Mat.h"
#include "game/BandUser.h"
#include "game/BandUserMgr.h"

class SessionUsersProvider : public UIListProvider, public Hmx::Object {
public:
    SessionUsersProvider(bool, bool, bool);
    virtual ~SessionUsersProvider() {}
    virtual void Text(int, int, UIListLabel *, UILabel *) const;
    virtual RndMat *Mat(int, int, UIListMesh *) const;
    virtual int NumData() const;
    virtual void InitData(RndDir *);
    virtual DataNode Handle(DataArray *, bool);

    BandUser *GetUser(int);
    void KickPlayer(int);
    void KickPlayer(BandUser *);
    void ToggleMuteStatus(int);
    void RefreshUserList(const BandUser *, const BandUserMgr *);
    bool IsMuted(int) const;

    std::vector<BandUser *> mUsers; // 0x20
    bool unk28;
    bool unk29;
    bool unk2a;
    RndMat *mCheckedMat; // 0x2c
    RndMat *mUncheckedMat; // 0x30
};