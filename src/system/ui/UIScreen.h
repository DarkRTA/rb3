#ifndef UI_UISCREEN_H
#define UI_UISCREEN_H

#include <list>
#include "obj/Data.h"
#include "obj/Object.h"
#include "os/JoypadMsgs.h"
#include "ui/UIPanel.h"
#include "utl/Symbol.h"

class PanelRef {
private:
    class UIPanel *mPanel;
    bool mActive;
    bool mAlwaysLoad;
    bool mLoaded;

    friend class UIScreen;

public:
    PanelRef() : mLoaded(false) {}

    bool Active() const { return mActive && mLoaded; }
};

class UIScreen : public Hmx::Object {
public:
    UIScreen();
    virtual ~UIScreen(){}

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
    UIPanel* FocusPanel() const { return mFocusPanel; }

    static int sMaxScreenId;
    static UIScreen *sUnloadingScreen;

    std::vector<PanelRef> mPanelList;
    class UIPanel *mFocusPanel;
    DataArray *mBack;
    bool mClearVram;
    bool mShowing;
    int mScreenId;
};

#include "obj/Msg.h"

BEGIN_MESSAGE(UITransitionCompleteMsg, transition_complete, UIScreen*, UIScreen*);
    MESSAGE_ARRAY_CTOR(UITransitionCompleteMsg)
    UIScreen* GetScreen1() const { return mData->Obj<UIScreen>(2); }
END_MESSAGE;

BEGIN_MESSAGE(UIScreenChangeMsg, screen_change, UIScreen*, UIScreen*, bool);
    MESSAGE_ARRAY_CTOR(UIScreenChangeMsg)
    UIScreen* GetFromScreen() const { return mData->Obj<UIScreen>(3); }
END_MESSAGE;

inline UITransitionCompleteMsg::UITransitionCompleteMsg(UIScreen* s1, UIScreen* s2) :
    Message(Type(), DataNode(s1), DataNode(s2)){}

inline UIScreenChangeMsg::UIScreenChangeMsg(UIScreen* s1, UIScreen* s2, bool b) :
    Message(Type(), DataNode(s1), DataNode(s2), DataNode(b)){}

class EventDialogStartMsg : public Message {
public:
    EventDialogStartMsg(DataArray* a) : Message(a) {}
    EventDialogStartMsg(DataArray* a1, DataArray* a2) :
        Message(Type(), DataNode(a1, kDataArray), DataNode(a2, kDataArray)) {}
    virtual ~EventDialogStartMsg(){}
    static Symbol Type() {
        static Symbol t("event_dialog_start");
        return t;
    }
};

class EventDialogDismissMsg : public Message {
public:
    EventDialogDismissMsg() : Message(Type()) {}
    virtual ~EventDialogDismissMsg(){}
    static Symbol Type() {
        static Symbol t("event_dialog_dismiss");
        return t;
    }
};

#endif
