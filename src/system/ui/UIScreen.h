#pragma once
#include "obj/ObjMacros.h"
#include <list>
#include "obj/Data.h"
#include "obj/Object.h"
#include "os/JoypadMsgs.h"
#include "ui/UIPanel.h"
#include "utl/Symbol.h"

class PanelRef {
public:
    class UIPanel *mPanel; // 0x0
    bool mActive; // 0x4
    bool mAlwaysLoad; // 0x5
    bool mLoaded; // 0x6

    friend class UIScreen;

    PanelRef() : mLoaded(false) {}

    bool Active() const { return mActive && mLoaded; }
};

class UIScreen : public Hmx::Object {
public:
    UIScreen();
    virtual ~UIScreen() {}

    OBJ_CLASSNAME(UIScreen);
    OBJ_SET_TYPE(UIScreen);
    virtual DataNode Handle(DataArray *, bool);
    virtual void SetTypeDef(DataArray *);

    virtual void LoadPanels();
    virtual void UnloadPanels();
    virtual bool CheckIsLoaded();
    virtual bool IsLoaded() const;

    virtual void Poll();
    virtual void Draw();

    virtual bool InComponentSelect() const;

    virtual void Enter(UIScreen *);
    virtual bool Entering() const;
    virtual void Exit(UIScreen *);
    virtual bool Exiting() const;

    virtual void Print(TextStream &);

    virtual bool Unloading() const;

    void SetFocusPanel(class UIPanel *);

    bool SharesPanels(UIScreen *);
    bool AllPanelsDown();

    void ReenterScreen();
    void SetPanelActive(class UIPanel *, bool);
    void SetShowing(bool);
    bool HasPanel(class UIPanel *);
    bool AddPanel(class UIPanel *, bool);

    DataNode ForeachPanel(const DataArray *);
    DataNode OnMsg(const ButtonDownMsg &);
    UIPanel *FocusPanel() const { return mFocusPanel; }
    const std::vector<PanelRef> &GetPanelRefs() const { return mPanelList; }

    static int sMaxScreenId;
    static UIScreen *sUnloadingScreen;
    NEW_OBJ(UIScreen);
    static void Init() { REGISTER_OBJ_FACTORY(UIScreen); }

    std::vector<PanelRef> mPanelList;
    class UIPanel *mFocusPanel;
    DataArray *mBack;
    bool mClearVram;
    bool mShowing;
    int mScreenId;
};

#include "obj/Msg.h"

DECLARE_MESSAGE(UITransitionCompleteMsg, "transition_complete");
UITransitionCompleteMsg(UIScreen *s1, UIScreen *s2) : Message(Type(), s1, s2) {}
UIScreen *GetNewScreen() const { return mData->Obj<UIScreen>(2); }
UIScreen *GetOldScreen() const { return mData->Obj<UIScreen>(3); }
END_MESSAGE

DECLARE_MESSAGE(UIScreenChangeMsg, "screen_change");
UIScreenChangeMsg(UIScreen *s1, UIScreen *s2, bool b) : Message(Type(), s1, s2, b) {}
UIScreen *GetNewScreen() const { return mData->Obj<UIScreen>(2); }
UIScreen *GetOldScreen() const { return mData->Obj<UIScreen>(3); }
bool GetBack() const { return mData->Int(4); }
END_MESSAGE

DECLARE_MESSAGE(UIChangedMsg, "ui_changed")
END_MESSAGE