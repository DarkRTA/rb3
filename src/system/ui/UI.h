#ifndef UI_UI_H
#define UI_UI_H

#include "obj/Object.h"
#include "utl/Symbol.h"
#include "ui/UIComponent.h"
#include "ui/UIScreen.h"
#include "ui/UIPanel.h"

class UIManager : public virtual Hmx::Object {
public:
    UIManager();

    virtual DataNode Handle(DataArray*, bool);
    virtual ~UIManager();

    virtual void Init();
    virtual void Terminate();

    virtual void Poll();
    virtual void Draw();

    virtual void GotoScreen(const char*, bool, bool);
    virtual void GotoScreen(UIScreen*, bool, bool);
    virtual void PushScreen(UIScreen*);
    virtual void PopScreen(UIScreen*);
    virtual void ResetScreen(UIScreen*);

    virtual bool InComponentSelect();
    virtual bool IsBlockingTransition(){ return false; }
    virtual bool IsTimelineResetAllowed() const { return true; }

    virtual void SendTransitionComplete(UIScreen*, UIScreen*);

    void CancelTransition();
    void GotoScreenImpl(UIScreen*, bool, bool);

    class UIPanel* FocusPanel();
    UIComponent* FocusComponent();

    void Resource(const UIComponent*);
    void InitResources(Symbol);
    void FindResource(const DataArray*);
    void OnIsResource(DataArray*);

    void UseJoypad(bool, bool);
    void OverloadHorizontalNav(JoypadAction, JoypadButton, Symbol) const;

    void RequireFixedText() const;
    void SetRequireFixedText(bool);

    void BottomScreen();
    void PushDepth() const;
    void ScreenAtDepth(int);

    void ToggleLoadTimes();

    bool InTransition();
    void BlockHandlerDuringTransition(Symbol, DataArray*);

    void EnableInputPerformanceMode(bool);
    void PrintLoadedDirs(const char*);
    void ShowNetError();

    void WentBack() const;
    void OnGotoScreen(const DataArray*);
    void OnGoBackScreen(const DataArray*);
    void ForeachScreen(const DataArray*);

    int unkc;
    // more members here
};

extern UIManager* TheUI;

#endif
