#pragma once
#include "ui/UIListProvider.h"
#include "obj/Object.h"

class BandUserMgr;

enum WiiProfileActResult {
    kWiiProfileActResult_Done = 0,
    kWiiProfileActResult_NeedConfirm = 1,
    kWiiProfileActResult_NewProfile = 2,
    kWiiProfileActResult_EditLogo = 3,
    kWiiProfileActResult_Failed = 4,
    kWiiProfileActResult_SwapProfile = 5
};

class OvershellProfileProvider : public UIListProvider, public Hmx::Object {
public:
    enum WiiProfileListMode {

    };

    OvershellProfileProvider(BandUserMgr*);
    virtual ~OvershellProfileProvider();
    virtual void Text(int, int, UIListLabel*, UILabel*) const;
    virtual RndMat* Mat(int, int, UIListMesh*) const;
    virtual int NumData() const;
    virtual DataNode Handle(DataArray*, bool);

    WiiProfileActResult ActOnProfile(int, LocalBandUser*, bool);
    WiiProfileActResult ActOnProfileConfirmed(LocalBandUser*);
    void SetWiiProfileListMode(WiiProfileListMode, bool);
    WiiProfileListMode GetWiiProfileListMode();
    int GetWiiProfileCount(LocalBandUser*) const;
    void Reload(LocalBandUser*);

    int unk20;
    int unk24;
    int unk28;
    BandUserMgr* unk2c;
    std::vector<int> unk30;
    std::vector<int> unk38;
};