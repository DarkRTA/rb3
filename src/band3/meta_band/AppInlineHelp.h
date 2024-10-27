#pragma once
#include "bandobj/InlineHelp.h"
#include "game/BandUser.h"
#include "game/GameMessages.h"
#include "meta_band/MetaMessages.h"

class AppInlineHelp : public InlineHelp {
public:
    AppInlineHelp();
    OBJ_CLASSNAME(AppInlineHelp)
    OBJ_SET_TYPE(AppInlineHelp)
    virtual DataNode Handle(DataArray*, bool);
    virtual ~AppInlineHelp(){}
    virtual void Enter();
    virtual void Exit();
    virtual void UpdateIconTypes(bool);

    void SetOverrideUser(LocalBandUser*);

    DataNode OnMsg(const InputStatusChangedMsg&);
    DataNode OnMsg(const LocalUserLeftMsg&);
    DataNode OnMsg(const AddLocalUserResultMsg&);

    LocalBandUser* mOverrideUser; // 0x13c
};