#pragma once
#include "ui/UIListProvider.h"
#include "obj/Object.h"

class BandUserMgr;

class OvershellProfileProvider : public UIListProvider, public Hmx::Object {
public:
    OvershellProfileProvider(BandUserMgr*);
    virtual ~OvershellProfileProvider();
    virtual void Text(int, int, UIListLabel*, UILabel*) const;
    virtual RndMat* Mat(int, int, UIListMesh*) const;
    virtual int NumData() const;
    virtual DataNode Handle(DataArray*, bool);

    int unk20;
    int unk24;
    int unk28;
    BandUserMgr* unk2c;
    std::vector<int> unk30;
    std::vector<int> unk38;
};