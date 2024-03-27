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
protected:
    static int sMaxScreenId;
    static UIScreen *sUnloadingScreen;

    std::vector<PanelRef> mPanelList;
    class UIPanel *mFocusPanel;
    DataArray *mBack;
    bool mClearVram;
    bool mShowing;
    int mScreenId;

public:
    UIScreen();
    virtual ~UIScreen();

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
    int AddPanel(class UIPanel *, bool);

    DataNode ForeachPanel(const DataArray *);
    DataNode OnMsg(const ButtonDownMsg &);
};

#endif
