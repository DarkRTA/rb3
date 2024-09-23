#pragma once

#include "obj/ObjMacros.h"
#include "obj/Object.h"
#include "ui/UIComponent.h"
#include "utl/BinStream.h"

class MiniLeaderboardDisplay : public UIComponent {
    MiniLeaderboardDisplay();
    virtual ~MiniLeaderboardDisplay();
    OBJ_CLASSNAME(MiniLeaderboardDisplay)
    OBJ_SET_TYPE(MiniLeaderboardDisplay)
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, CopyType);
    virtual void Load(BinStream&);
    virtual void PreLoad(BinStream&);
    virtual void PostLoad(BinStream&);
    virtual void DrawShowing();

    bool mAllowSoloScores;

    NEW_OBJ(MiniLeaderboardDisplay)
    static void Init();
    static void Register(){
        REGISTER_OBJ_FACTORY(MiniLeaderboardDisplay)
    }

    DECLARE_REVS
};