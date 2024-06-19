#ifndef UI_UI_H
#define UI_UI_H
#include "obj/Object.h"
#include "utl/Symbol.h"
#include "os/Joypad.h"
#include "os/Timer.h"
#include <vector>

class JoypadClient;
class UIComponent;
class UIScreen;
class UIPanel;
class UIResource;
class RndOverlay;
class RndCam;

enum TransitionState {
    kTransitionNone = 0,
    kTransitionTo = 1,
    kTransitionFrom = 2,
    kTransitionPop = 3,
};

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
    UIResource* Resource(const UIComponent*);
    void InitResources(Symbol);
    void FindResource(const DataArray*);
    void UseJoypad(bool, bool);
    void OverloadHorizontalNav(JoypadAction, JoypadButton, Symbol) const;
    bool RequireFixedText() const;
    void SetRequireFixedText(bool);
    void PushDepth() const;
    void ScreenAtDepth(int);
    void ToggleLoadTimes();
    bool InTransition();
    bool BlockHandlerDuringTransition(Symbol, DataArray*);
    void EnableInputPerformanceMode(bool);
    void PrintLoadedDirs(const char*);
    void ShowNetError();
    bool WentBack() const { return mWentBack; }
    UIScreen* CurrentScreen();
    UIScreen* TransitionScreen() const;
    UIScreen* BottomScreen();
    DataNode OnGotoScreen(const DataArray*);
    DataNode OnGoBackScreen(const DataArray*);
    DataNode OnIsResource(DataArray*);
    DataNode ForeachScreen(const DataArray*);

    TransitionState mTransitionState; // 0x8
    bool mWentBack; // 0xc
    std::vector<UIScreen*> mPushedScreens; // 0x10
    int mMaxPushDepth; // 0x18
    JoypadClient* mJoyClient; // 0x1c
    UIScreen* mCurrentScreen; // 0x20
    UIScreen* mTransitionScreen; // 0x24
    std::vector<UIResource*> mResources; // 0x28
    Hmx::Object* mSink; // 0x30
    RndCam* unk34; // 0x34
    RndEnviron* unk38; // 0x38
    int unk3c; // 0x3c
    Timer mTimer; // 0x40
    bool unk70; // 0x70
    bool unk71; // 0x71
    bool unk72; // 0x72
    int unk74; // 0x74
    Timer mLoadTimer; // 0x78
    RndOverlay* mOverlay; // 0xa8
    bool mRequireFixedText; // 0xac
    Hmx::Object* unkb0; // 0xb0 - should be class Automator*?
    bool unkb4; // 0xb4
    bool unkb5; // 0xb5
};

extern UIManager* TheUI;

#endif
