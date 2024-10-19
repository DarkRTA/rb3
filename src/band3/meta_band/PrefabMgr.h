#pragma once
#include "obj/Object.h"

class PrefabMgr : public Hmx::Object {
public:
    PrefabMgr();
    virtual ~PrefabMgr();
    virtual DataNode Handle(DataArray*, bool);

    static PrefabMgr* GetPrefabMgr();
};