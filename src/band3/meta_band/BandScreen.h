#pragma once
#include "ui/UIScreen.h"

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
};

#include "obj/Msg.h"

DECLARE_MESSAGE(CurrentScreenChangedMsg, "current_screen_changed");
CurrentScreenChangedMsg(Symbol);
Symbol GetScreen() const;
END_MESSAGE