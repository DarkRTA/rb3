#pragma once
#include "ui/UIPanel.h"
#include "ui/UIScreen.h"
#include "utl/MemMgr.h"

class BandScreen : public UIScreen {
public:
    BandScreen() {}
    virtual ~BandScreen() {}
    OBJ_CLASSNAME(BandScreen);
    OBJ_SET_TYPE(BandScreen);
    virtual DataNode Handle(DataArray *, bool);
    virtual void LoadPanels();
    virtual bool CheckIsLoaded();
    virtual bool IsLoaded() const;
    virtual void Enter(UIScreen *);
    virtual bool Entering() const;
    virtual void Exit(UIScreen *);
    virtual bool Exiting() const;

    void LoadInterstitials();
    void UnloadInterstitials();

    NEW_OVERLOAD;
    DELETE_OVERLOAD;

    std::vector<UIPanel *> mExtraPanels; // 0x34
};

#include "obj/Msg.h"

DECLARE_MESSAGE(CurrentScreenChangedMsg, "current_screen_changed");
CurrentScreenChangedMsg(Symbol);
Symbol GetScreen() const;
END_MESSAGE