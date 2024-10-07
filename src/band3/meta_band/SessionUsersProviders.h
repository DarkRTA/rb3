#pragma once
#include "ui/UIListProvider.h"
#include "rndobj/Mat.h"

class SessionUsersProvider : public UIListProvider, public Hmx::Object {
public:
    SessionUsersProvider(bool, bool, bool);
    virtual ~SessionUsersProvider(){}
    virtual void Text(int, int, UIListLabel*, UILabel*) const;
    virtual RndMat* Mat(int, int, UIListMesh*) const;
    virtual int NumData() const;
    virtual void InitData(RndDir*);
    virtual DataNode Handle(DataArray*, bool);

    std::vector<int> mUsers; // 0x20
    bool unk28;
    bool unk29;
    bool unk2a;
    RndMat* unk2c;
    RndMat* unk30;
};